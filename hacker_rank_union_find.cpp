#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */

class UnionFind
{

public:
    unordered_map<int, int> rank;
    unordered_map<int, int> parents;
    uint group_count;
    int find(int e)
    {
        if (parents.find(e) == parents.end())
        {
            parents[e] = e;
            rank[e] = 1;
            group_count++;
        }
        if (parents[e] != e)
            parents[e] = find(parents[e]);
        return parents[e];
    }

    void uni(int a, int b)
    {
        int p_a = find(a);
        int p_b = find(b);
        if (p_a != -1 && p_a == p_b)
            return;

        int rank_a = rank[p_a];
        int rank_b = rank[p_b];

        if (rank_a > rank_b)
        {
            parents[p_b] = p_a;
            rank[p_a] = rank_a + rank_b;
        }
        else
        {
            parents[p_a] = p_b;
            rank[p_b] = rank_a + rank_b;
        }
        group_count--;
    }
};

int journeyToMoon(int count, vector<vector<int>> astronaut)
{
    UnionFind uf;
    for (int i = 0; i < count; i++)
    {
        uf.find(i);
    }
    for (auto &p : astronaut)
    {
        uf.uni(p.front(), p.back());
    }
    unordered_set<int> groups;
    for (int i = 0; i < count; i++)
    {
        groups.insert(uf.find(i));
    }
    vector<int> ranks;
    vector<int> sum;
    int pos = 0;
    int sum_v = 0;
    for (auto &v : groups)
        ranks.push_back(uf.rank[v]);
    for (auto it = ranks.rbegin(); it != ranks.rend(); ++it)
    {
        sum_v += *it;
        sum.push_back(sum_v);
    }
    reverse(sum.begin(), sum.end());
    for (size_t i = 0; i < ranks.size() - 1; i++)
    {
        pos += ranks[i] * sum[i + 1];
    }
    return pos;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int p = stoi(first_multiple_input[1]);

    vector<vector<int>> astronaut(p);

    for (int i = 0; i < p; i++)
    {
        astronaut[i].resize(2);

        string astronaut_row_temp_temp;
        getline(cin, astronaut_row_temp_temp);

        vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

        for (int j = 0; j < 2; j++)
        {
            int astronaut_row_item = stoi(astronaut_row_temp[j]);

            astronaut[i][j] = astronaut_row_item;
        }
    }

    int result = journeyToMoon(n, astronaut);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
