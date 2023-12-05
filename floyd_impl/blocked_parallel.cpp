#include <vector>
#include <omp.h>

using namespace std;

void _floyd_warshall_blocked(vector<vector<int>> &C, vector<vector<int>> &A, vector<vector<int>> &B, int block_size)
{
    for (int k = 0; k < block_size; ++k)
    {
        for (int i = 0; i < block_size; ++i)
        {
            for (int j = 0; j < block_size; ++j)
            {
                int t = A[i][k] + B[k][j];
                if (t < C[i][j])
                {
                    C[i][j] = t;
                }
            }
        }
    }
}

void floyd_warshall_blocked_parallel(vector<vector<vector<vector<int>>>> &W, int n, int block_size)
{
    int num_blocks = n / block_size;
    for (int k = 0; k < num_blocks; ++k)
    {
        _floyd_warshall_blocked(W[k][k], W[k][k], W[k][k], block_size);
#pragma omp parallel for
        for (int j = 0; j < num_blocks; ++j)
        {
            if (j != k)
            {
                _floyd_warshall_blocked(W[k][j], W[k][k], W[k][j], block_size);
            }
        }
#pragma omp parallel for
        for (int i = 0; i < num_blocks; ++i)
        {
            if (i != k)
            {
                _floyd_warshall_blocked(W[i][k], W[i][k], W[k][k], block_size);
                for (int j = 0; j < num_blocks; ++j)
                {
                    if (j != k)
                    {
                        _floyd_warshall_blocked(W[i][j], W[i][k], W[k][j], block_size);
                    }
                }
            }
        }
    }
}