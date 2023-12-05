#include <vector>
#include <cstdlib>
#include <functional>
#include <omp.h>

#define MAX_WEIGHT 100
#define INF INT_MAX-MAX_WEIGHT

using namespace std;

void seed_matrix(vector<vector<int>> &matrix)
{
    srand(time(0));
    int n = matrix.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                if (rand() % 4 == 0)
                {
                    matrix[i][j] = INF;
                }
                else
                {
                    matrix[i][j] = (rand() % MAX_WEIGHT + MAX_WEIGHT) % MAX_WEIGHT + 1;
                }
            }
        }
    }
}

vector<vector<vector<vector<int>>>> to_blocked(const vector<vector<int>> &matrix, int block_size)
{
    int n = matrix.size();
    int num_blocks = n / block_size;
    vector<vector<vector<vector<int>>>> blocked(num_blocks, vector<vector<vector<int>>>(num_blocks, vector<vector<int>>(block_size, vector<int>(block_size))));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            blocked[i / block_size][j / block_size][i % block_size][j % block_size] = matrix[i][j];
        }
    }

    return blocked;
}

vector<vector<int>> to_matrix(const vector<vector<vector<vector<int>>>> &blocked, int block_size)
{
    int n = blocked.size() * block_size;
    vector<vector<int>> matrix(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            matrix[i][j] = blocked[i / block_size][j / block_size][i % block_size][j % block_size];
        }
    }

    return matrix;
}

bool are_equal(const vector<vector<int>> &vec1, const vector<vector<int>> &vec2)
{
    if (vec1.size() != vec2.size())
    {
        return false;
    }

    for (size_t i = 0; i < vec1.size(); ++i)
    {
        if (vec1[i] != vec2[i])
        {
            return false;
        }
    }

    return true;
}

bool check_equal(vector<vector<int>> &matrix, int n, int b)
{
    auto copy1 = matrix;
    auto copy2 = matrix;
    auto copy3 = to_blocked(matrix, b);

    floyd_warshall(copy1);
    floyd_warshall_parallel(copy2);
    floyd_warshall_blocked_parallel(copy3, n, b);
    
    return are_equal(copy1, copy2) && are_equal(copy2, to_matrix(copy3, b));
}

double measure_time(function<void()> func)
{
    double start = omp_get_wtime();
    func();
    double end = omp_get_wtime();
    return end - start;
}