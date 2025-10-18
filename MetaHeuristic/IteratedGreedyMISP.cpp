#include <bits/stdc++.h>
using namespace std;

vector<int> greedyRandomMISP_init(vector<vector<int>> &adj, int d_level, int alpha, int n, vector<int> &degree, vector<bool> &removed)
{
    vector<int> independentSet;

    for (int i = 0; i < n; i++)
        degree[i] = adj[i].size();

    int remaining = n;

    for (remaining; remaining > 0;)
    {
        int v = -1, bestDeg = INT_MAX;
        priority_queue<pair<int, int>> bestDegs;
        for (int i = 0; i < n; i++)
        {
            if (!removed[i])
            {
                if (degree[i] < bestDeg)
                {
                    bestDeg = degree[i];
                    v = i;
                }
                bestDegs.push({degree[i], i});
                if (bestDegs.size() > alpha)
                {
                    bestDegs.pop();
                }
            }
        }

        if (v == -1)
            break;

        int r = rand() % 100 + 1;

        if (r > d_level)
        {
            int del = rand() % bestDegs.size();
            for (int i = 0; i < del; i++)
            {
                bestDegs.pop();
            }
            v = bestDegs.top().second;
        }

        independentSet.push_back(v);

        removed[v] = true;
        remaining--;
        for (int u : adj[v])
        {
            if (!removed[u])
            {
                removed[u] = true;
                remaining--;
            }
        }
    }

    return independentSet;
}

bool is_int(char const *argv)
{
    istringstream in(argv);
    int i;
    if (in >> i && in.eof())
        return true;
    return false;
}

//// New in MetaHeuristic ////

int destroyMISP(vector<vector<int>> &adj, vector<int> &independentSet, vector<bool> &removed)
{
    int count = 0;
    int n = rand() % (independentSet.size() - independentSet.size() / 2) + independentSet.size() / 2 + 1;
    for (int i = 0; i < n; i++)
    {
        int del = rand() % independentSet.size();
        removed[independentSet[del]] = false;
        count++;
        for (int u : adj[independentSet[del]])
        {
            removed[u] = false;
            count++;
            for (int j : adj[u])
            {
                if (j == independentSet[del])
                    continue;
                if (find(independentSet.begin(), independentSet.end(), j) != independentSet.end())
                {
                    removed[u] = true;
                    count--;
                    break;
                }
            }
        }
        independentSet.erase(independentSet.begin() + del);
    }
    return count;
}

void recreateMISP(vector<vector<int>> &adj, vector<int> &degree, vector<int> &independentSet, vector<bool> &removed, int n, int d_level, int alpha)
{
    int remaining = n;

    for (remaining; remaining > 0;)
    {
        int v = -1, bestDeg = INT_MAX;
        priority_queue<pair<int, int>> bestDegs;
        for (int i = 0; i < n; i++)
        {
            if (!removed[i])
            {
                if (degree[i] < bestDeg)
                {
                    bestDeg = degree[i];
                    v = i;
                }
                bestDegs.push({degree[i], i});
                if (bestDegs.size() > alpha)
                {
                    bestDegs.pop();
                }
            }
        }

        if (v == -1)
            break;

        int r = rand() % 100 + 1;

        if (r > d_level)
        {
            int del = rand() % bestDegs.size();
            for (int i = 0; i < del; i++)
            {
                bestDegs.pop();
            }
            v = bestDegs.top().second;
        }

        independentSet.push_back(v);

        removed[v] = true;
        remaining--;
        for (int u : adj[v])
        {
            if (!removed[u])
            {
                removed[u] = true;
                remaining--;
            }
        }
    }
}

bool compareMISP(vector<int> &new_misp, vector<int> &misp, vector<bool> &new_removed, vector<bool> &removed)
{
    // cerr << "Comparing " << new_misp.size() << " with " << misp.size() << endl;
    if (new_misp.size() > misp.size())
    {
        removed = new_removed;
        misp = new_misp;
        return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    // cout << argc << endl;
    // for (int i = 0; i < argc; i++)
    //     cout << i << ": " << argv[i] << endl;
    srand(time(0));
    if (argc != 7 || (strcmp(argv[1], "-i") != 0 ||
                      strcmp(argv[3], "-t") != 0 ||
                      !(is_int(argv[4]) && atoi(argv[4]) >= 1) ||
                      !(is_int(argv[5]) && atoi(argv[5]) >= 0 && atoi(argv[5]) <= 100) ||
                      !(is_int(argv[6]) && atoi(argv[6]) >= 1)))
    {
        cout << "Error, command format must be like this: '" << argv[0] << " -i <file direction> -t <max time (seconds)> <determinism level (between 0 and 100)> <alpha value (positive integrer excluding 0)>'." << endl;
        return 0;
    }

    int d_level = atoi(argv[5]);
    int alpha = atoi(argv[6]);
    long long time = atoll(argv[4]);
    ifstream file(argv[2]);
    if (!file)
    {
        cout << "Error: The direction " << argv[2] << " was not found." << endl;
        return 0;
    }

    string str;
    vector<vector<int>> adj;
    auto addEdge = [&](int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    while (getline(file, str))
    {
        int c1, c2;
        istringstream ss(str);
        ss >> c1;

        if (ss >> c2)
        {
            addEdge(c1, c2);
        }
        else
        {
            adj.resize(c1);
        }
    }

    int n = adj.size();
    vector<int> degree(n);
    vector<bool> removed(n, false);

    vector<int> res;
    vector<long long> times;

    string file_dir = argv[2];
    size_t pos = file_dir.find("erdos_");
    string name = "./TimeQuality_Results/Time_Quality_table_";
    name = name + file_dir.substr(pos + 6);
    name = name + ".csv";
    ofstream outputFile(name);

    outputFile << "Time,Quality" << endl;

    auto start_time = chrono::high_resolution_clock::now();
    vector<int> misp = greedyRandomMISP_init(adj, d_level, alpha, n, degree, removed);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    outputFile << duration_time << "," << misp.size() << endl;
    cerr << duration_time << ", " << misp.size() << endl;

    auto last_time_update = duration_time;
    // times.push_back(duration_time);
    // res.push_back(misp.size());

    while (duration_time <= time * 1000000000)
    {
        times.push_back(duration_time);
        res.push_back(misp.size());
        // cerr << duration_time << ", " << misp.size() << endl;
        vector<int> last_misp = misp;

        start_time = chrono::high_resolution_clock::now();
        vector<int> new_misp = misp;
        vector<bool> new_removed = removed;
        int remaining = destroyMISP(adj, new_misp, new_removed);
        recreateMISP(adj, degree, new_misp, new_removed, remaining, d_level, alpha);
        bool change = compareMISP(new_misp, misp, new_removed, removed);
        end_time = chrono::high_resolution_clock::now();
        duration_time += chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
        if (change)
        {
            outputFile << duration_time << "," << misp.size() << endl;
            cerr << duration_time << "," << misp.size() << endl;
            last_time_update = duration_time;
        }
        if (duration_time > time * 1000000000)
        {
            cout << last_misp.size() << ',' << last_time_update << endl;
            cerr << last_misp.size() << ',' << last_time_update << endl;
            break;
        }
    }

    // cout << duration_time << "," << misp.size() << endl;

    /*
    bool verify = true;
    for (int v : misp)
    {
        for (int u : adj[v])
        {
            auto it = find(misp.begin(), misp.end(), u);
            if (it != misp.end())
            {
                verify = false;
                break;
            }
        }
        if (!verify)
        break;
    }

    if (verify)
    {
        cout << misp.size() << ", " << duration_time << endl;
    }
    else
    {
        cout << 0 << "," << duration_time << endl;
    }
    */

    return 0;
}