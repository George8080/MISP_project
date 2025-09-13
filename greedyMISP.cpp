#include <bits/stdc++.h>
using namespace std;

vector<int> greedyMISP(vector<vector<int>> &adj)
{
    int n = adj.size();
    vector<int> degree(n);
    vector<bool> removed(n, false);
    vector<int> independentSet;

    for (int i = 0; i < n; i++)
        degree[i] = adj[i].size();

    for (int remaining = n; remaining > 0;)
    {
        int v = -1, bestDeg = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (!removed[i] && degree[i] < bestDeg)
            {
                bestDeg = degree[i];
                v = i;
            }
        }

        if (v == -1)
            break;

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

int main(int argc, char const *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-i") != 0)
    {
        cout << "Error, command format must be like this: '" << argv[0] << " -i <file direction>'." << endl;
        return 0;
    }

    // ifstream file("./dataset_grafos_no_dirigidos/new_1000_dataset/erdos_n1000_p0c0.1_1.graph");
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
        // cout << str << endl;
        int c1, c2;
        istringstream ss(str);
        ss >> c1;

        if (ss >> c2)
        {
            // cout << "Hay par: " << c1 << " " << c2 << endl;
            addEdge(c1, c2);
        }
        else
        {
            // cout << "N es igual a " << c1 << endl;
            adj.resize(c1);
        }
    }

    auto start_time = chrono::high_resolution_clock::now();
    vector<int> misp = greedyMISP(adj);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();

    bool verify = true;
    for (int v : misp)
    {
        for (int u : adj[v])
        {
            auto it = find(misp.begin(), misp.end(), u);
            if (it != misp.end())
            {
                verify = false;
                // cout << u << " and " << v << " are conected..." << endl;
                break;
            }
        }
        if (!verify)
            break;
    }

    if (verify)
    {
        // cout << "MISP is Correct!" << endl;
        // cout << "Greedy Independent Set: ";
        // for (int v : misp)
        //    cout << v << " ";
        // cout << "\n";
        // cout << "Build time: " << duration_time << " ns." << endl;

        // cout << endl;

        cout << misp.size() << ", " << duration_time << endl;
    }
    else
    {
        // cout << "Is not a MISP :c" << endl;
        cout << 0 << "," << duration_time << endl;
    }

    return 0;
}