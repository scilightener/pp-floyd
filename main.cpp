#include "measures.cpp"

using namespace std;

int main()
{
    const int n = 1024;
    const int b = 16;

    vector<vector<int>> matrix(n, vector<int>(n));
    seed_matrix(matrix);

    measure_floyd_std(matrix);
    measure_floyd_parallel(matrix);
    measure_floyd_blocked_parallel(matrix, n, b);

    // cout << "Correctness: " << (check_equal(matrix, n, b) ? "OK" : "ERROR") << endl;

    return 0;
}