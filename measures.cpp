#include <iostream>
#include "floyd_impl/standard.cpp"
#include "floyd_impl/parallel.cpp"
#include "floyd_impl/blocked_parallel.cpp"
#include "helpers.cpp"

using namespace std;

void measure_floyd_std(vector<vector<int>> matrix)
{
    double time = measure_time([&matrix]()
                               { floyd_warshall(matrix); });

    cout << "Time for standard FW: " << time << " seconds" << endl;
}

void measure_floyd_parallel(vector<vector<int>> matrix)
{
    double time = measure_time([&matrix]()
                               { floyd_warshall_parallel(matrix); });

    cout << "Time for parallel FW: " << time << " seconds" << endl;
}

void measure_floyd_blocked_parallel(vector<vector<int>> matrix, int n, int block_size)
{
    // auto blocked = to_blocked(matrix, block_size);

    double time = measure_time(
        [&matrix, n, block_size]()
        {
            auto blocked = to_blocked(matrix, block_size);
            floyd_warshall_blocked_parallel(blocked, n, block_size);
            matrix = to_matrix(blocked, block_size);
        }
    );

    cout << "Time for blocked parallel FW: " << time << " seconds" << endl;
}