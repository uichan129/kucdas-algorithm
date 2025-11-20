#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> graph;
vector<int> disc, low;
vector<bool> inStack;
stack<int> st;

int V, E;
int cnt = 1;
vector<vector<int>> SCCs;

void tarjan(int u)
{
    disc[u] = low[u] = cnt++;
    st.push(u);
    inStack[u] = true;

    for (int v : graph[u])
    {
        if (disc[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inStack[v])
        {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (disc[u] == low[u])
    {
        vector<int> scc;
        while (true)
        {
            int t = st.top();
            st.pop();
            inStack[t] = false;
            scc.push_back(t);
            if (t == u)
                break;
        }
        sort(scc.begin(), scc.end());
        SCCs.push_back(scc);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> V >> E;

    graph.resize(V + 1);
    disc.resize(V + 1, 0);
    low.resize(V + 1, 0);
    inStack.resize(V + 1, false);

    for (int i = 0; i < E; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= V; i++)
    {
        if (disc[i] == 0)
            tarjan(i);
    }

    sort(SCCs.begin(), SCCs.end(), [](vector<int> &a, vector<int> &b)
         { return a[0] < b[0]; });

    cout << SCCs.size() << "\n";
    for (auto &scc : SCCs)
    {
        for (int x : scc)
            cout << x << " ";
        cout << -1 << "\n";
    }

    return 0;
}
