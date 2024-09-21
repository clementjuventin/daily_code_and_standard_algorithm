#include <gtest/gtest.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

enum class State
{
    Unknown,
    Queued,
    Running,
    Terminated,
};

class ThreadPool
{
private:
    vector<thread> threads;
    queue<pair<size_t, function<void()>>> tasks_queue;
    mutex task_queue_mutex;
    condition_variable task_queue_mutex_condition;
    condition_variable await_condition;
    size_t task_index{0};
    unordered_map<size_t, State> tasks_by_index;
    bool stop_pool = false;

    bool check_index(size_t index)
    {
        return this->tasks_by_index.find(index) != this->tasks_by_index.end();
    }

    void thread_loop()
    {
        while (true)
        {
            pair<size_t, function<void()>> task;
            unique_lock lock(this->task_queue_mutex);
            this->task_queue_mutex_condition.wait(lock, [this]
                                                  { return !this->tasks_queue.empty() || this->stop_pool; });
            if (this->stop_pool)
                return;
            task = this->tasks_queue.front();
            this->tasks_queue.pop();
            size_t index = get<0>(task);
            bool execute = this->check_index(index);
            if (execute)
                this->tasks_by_index[index] = State::Running;
            lock.unlock();
            if (execute)
            {
                get<1>(task)();
                unique_lock lock(this->task_queue_mutex);
                if (this->check_index(index))
                    this->tasks_by_index[index] = State::Terminated;
                lock.unlock();
                this->await_condition.notify_all();
            }
        }
    }

public:
    ThreadPool(const uint32_t threads_capacity)
    {
        const uint32_t max_threads_capacity = thread::hardware_concurrency();
        const uint32_t capacity = min(threads_capacity, max_threads_capacity);

        for (uint32_t i = 0; i < capacity; ++i)
            threads.push_back(thread(&ThreadPool::thread_loop, this));
    }
    size_t async(const function<void()> &task)
    {
        unique_lock lock(this->task_queue_mutex);
        const size_t index = this->task_index;
        this->task_index += 1;
        this->tasks_queue.push(pair(index, task));
        this->tasks_by_index.insert({index, State::Queued});
        lock.unlock();
        this->task_queue_mutex_condition.notify_one();
        return index;
    }
    void await(size_t index)
    {
        unique_lock lock(this->task_queue_mutex);
        this->await_condition.wait(lock, [this, index]
                                   { return !this->check_index(index) || this->tasks_by_index[index] == State::Terminated; });
        lock.unlock();
    }
    bool busy()
    {
        unique_lock lock(this->task_queue_mutex);
        const bool busy = !this->tasks_queue.empty();
        lock.unlock();
        return busy;
    }
    void stop()
    {
        unique_lock lock(this->task_queue_mutex);
        this->stop_pool = true;
        lock.unlock();
        this->task_queue_mutex_condition.notify_all();

        for (auto &t : this->threads)
            t.join();
        this->threads.clear();
    }
    State state(size_t index)
    {
        unique_lock lock(this->task_queue_mutex);
        if (!this->check_index(index))
            return State::Unknown;
        const State state = this->tasks_by_index[index];
        lock.unlock();
        return state;
    }
};

TEST(THREAD_POOL, thread_pool)
{
    ThreadPool pool(3);

    EXPECT_EQ(pool.busy(), false);
    size_t index1 = pool.async([]
                               { this_thread::sleep_for(chrono::milliseconds(100)); });
    size_t index2 = pool.async([]
                               { this_thread::sleep_for(chrono::milliseconds(150)); });
    size_t index3 = pool.async([]
                               { this_thread::sleep_for(chrono::milliseconds(200)); });
    size_t index4 = pool.async([]
                               { this_thread::sleep_for(chrono::milliseconds(100)); });

    this_thread::sleep_for(chrono::milliseconds(50));

    EXPECT_EQ(pool.busy(), true);
    EXPECT_EQ(pool.state(index1), State::Running);
    EXPECT_EQ(pool.state(index2), State::Running);
    EXPECT_EQ(pool.state(index3), State::Running);
    EXPECT_EQ(pool.state(index4), State::Queued);

    pool.await(index2);

    EXPECT_EQ(pool.state(index1), State::Terminated);
    EXPECT_EQ(pool.state(index2), State::Terminated);
    EXPECT_EQ(pool.state(index3), State::Running);
    EXPECT_EQ(pool.state(index4), State::Running);

    pool.await(index1);
    pool.await(index2);
    pool.await(index3);
    pool.await(index4);

    EXPECT_EQ(pool.busy(), false);
    EXPECT_EQ(pool.state(index1), State::Terminated);
    EXPECT_EQ(pool.state(index2), State::Terminated);
    EXPECT_EQ(pool.state(index3), State::Terminated);
    EXPECT_EQ(pool.state(index4), State::Terminated);

    pool.stop();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}