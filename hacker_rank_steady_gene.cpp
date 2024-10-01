#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */
bool compare(const vector<size_t> &a, const vector<size_t> &b)
{
    for (size_t i = 0, len = a.size(); i < len; i++)
        if (a[i] < b[i])
            return true;
    return false;
}

void sub(const vector<size_t> &a, const vector<size_t> &b, vector<size_t> &out)
{
    for (size_t i = 0, len = a.size(); i < len; i++)
        out[i] = a[i] - b[i];
}

int steadyGene(string gene) {
    if (gene.size() == 0)
        return 0UL;
    vector<vector<size_t>> states{vector<size_t>{0, 0, 0, 0}};
    for (auto &g : gene)
    {
        states.push_back(states.back());
        switch (g)
        {
        case 'A':
            states.back()[0]++;
            break;
        case 'C':
            states.back()[1]++;
            break;
        case 'T':
            states.back()[2]++;
            break;
        case 'G':
            states.back()[3]++;
            break;
        default:
            break;
        }
    }
    size_t occ_target = gene.size() / 4;
    vector<size_t> target{
        occ_target > states.back()[0] ? 0 : states.back()[0] - occ_target,
        occ_target > states.back()[1] ? 0 : states.back()[1] - occ_target,
        occ_target > states.back()[2] ? 0 : states.back()[2] - occ_target,
        occ_target > states.back()[3] ? 0 : states.back()[3] - occ_target,
    };
    vector<size_t> sum(4, 0);

    size_t start = 0, end = 0, size = gene.size(), mi = numeric_limits<size_t>::max();
    while (end <= size)
    {
        sub(states[end], states[start], sum);
        if (compare(sum, target))
            end++;
        else
        {
            mi = min(end - start, mi);
            start++;
            if (mi == 0)
                return 0;
        }
    }
    return mi;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
