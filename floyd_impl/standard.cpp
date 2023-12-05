#include <vector>

using namespace std;

void floyd_warshall(vector<vector<int>> &graph)
{
    int V = graph.size();

    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                int t = graph[i][k] + graph[k][j];
                if (t < graph[i][j])
                {
                    graph[i][j] = t;
                }
            }
        }
    }
}