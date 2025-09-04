#include <bits/stdc++.h>
using namespace std;

vector<int> greedyMIS(vector<vector<int>> &adj)
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
    ifstream file("./dataset_grafos_no_dirigidos/new_1000_dataset/erdos_n1000_p0c0.1_1.graph");
    string str;

    vector<vector<int>> adj;
    auto addEdge = [&](int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    if (!file)
    {
        cout << "Direccion no encontrada." << endl;
    }
    while (std::getline(file, str))
    {
        // cout << str << endl;
        int c1, c2;
        istringstream ss(str);
        ss >> c1;

        if (ss >> c2)
        {
            cout << "Hay par: " << c1 << " " << c2 << endl;
            addEdge(c1, c2);
        }
        else
        {
            cout << "N es igual a " << c1 << endl;
            adj.resize(c1);
        }
    }

    vector<int> mis = greedyMIS(adj);

    bool verify = true;
    for (int v : mis)
    {
        for (int u : adj[v])
        {
            auto it = find(mis.begin(), mis.end(), u);
            if (it != mis.end())
            {
                verify = false;
                cout << u << " y " << v << " están conectados..." << endl;
                break;
            }
        }
        if (!verify)
            break;
    }

    if (verify)
    {
        cout << "CORRECTO!!!!!!!" << endl;
        cout << "Greedy Independent Set: ";
        for (int v : mis)
            cout << v << " ";
        cout << "\n";
    }
    else
    {
        cout << "No es un MISP :c" << endl;
    }

    return 0;
}