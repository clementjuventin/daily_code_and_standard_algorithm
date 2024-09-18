#include <gtest/gtest.h>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

void scheduled_func(int number)
{
    cout << "Hello " << number << endl;
}

void schedule(void(func)(int), int delay, int number)
{
    this_thread::sleep_for(chrono::milliseconds(delay));
    func(number);
}

TEST(SCHEDULE, schedule)
{
    thread t(schedule, &scheduled_func, 20, 2);
    thread u(schedule, &scheduled_func, 10, 1);
    thread v(schedule, &scheduled_func, 100, 4);
    thread w(schedule, &scheduled_func, 50, 3);
    cout << "Scheduled" << endl;

    t.join();
    u.join();
    v.join();
    w.join();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
