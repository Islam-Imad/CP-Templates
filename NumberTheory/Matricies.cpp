#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define matrix vector<vector<ll>>

template <class T>
vector<vector<T>> getMatrix(int n, int m)
{
    return vector<vector<T>>(n, vector<T>(m));
}

template <class T>
vector<vector<T>> getIdentityMatrix(int n)
{
    vector<vector<T>> I = getMatrix<T>(n, n);
    for (int i = 0; i < n; ++i)
    {
        I[i][i] = 1;
    }
    return I;
}

template <class T>
void printMatrix(vector<vector<T>> &mat)
{
    for (auto &row : mat)
    {
        for (auto &ele : row)
        {
            cout << ele << " ";
        }
        cout << endl;
    }
}

template <class T>
vector<vector<T>> matrix_addition(vector<vector<T>> &A, vector<vector<T>> &B)
{
    int n = A.size(), m = A[0].size();
    vector<vector<T>> C = getMatrix<T>(n, m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

template <class T>
vector<vector<T>> matrix_subtraction(vector<vector<T>> &A, vector<vector<T>> &B)
{
    int n = A.size(), m = A[0].size();
    vector<vector<T>> C = getMatrix<T>(n, m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

template <class T>
vector<vector<T>> matrix_multiplication(vector<vector<T>> &A, vector<vector<T>> &B)
{
    int n = A.size(), m = A[0].size(), p = B[0].size();
    assert(m == B.size());
    vector<vector<T>> C = getMatrix<T>(n, p);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            for (int k = 0; k < m; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

template <class T>
vector<vector<T>> matrix_transpose(vector<vector<T>> &A)
{
    int n = A.size(), m = A[0].size();
    vector<vector<T>> B = getMatrix<T>(m, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            B[j][i] = A[i][j];
        }
    }
    return B;
}

template <class T>
vector<vector<T>> matrix_power(vector<vector<T>> &A, ll p)
{
    int n = A.size();
    assert(n == A[0].size());
    vector<vector<T>> R = getIdentityMatrix<T>(n);
    while (p)
    {
        if (p & 1)
        {
            R = matrix_multiplication(R, A);
        }
        A = matrix_multiplication(A, A);
        p >>= 1;
    }
    return R;
}

template <class T>
T matrix_determinant(vector<vector<T>> &A)
{
    int n = A.size();
    assert(n == A[0].size());
    T det = 1;
    for (int i = 0; i < n; ++i)
    {
        int idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (abs(A[j][i]) > abs(A[idx][i]))
            {
                idx = j;
            }
        }
        if (idx != i)
        {
            det *= -1;
            swap(A[i], A[idx]);
        }
        if (A[i][i] == 0)
        {
            return 0;
        }
        det *= A[i][i];
        T inv = 1 / A[i][i];
        for (int j = i + 1; j < n; ++j)
        {
            T factor = A[j][i] * inv;
            for (int k = i; k < n; ++k)
            {
                A[j][k] -= factor * A[i][k];
            }
        }
    }
    return det;
}

template <class T>
vector<vector<T>> matrix_inverse(vector<vector<T>> &A)
{
    int n = A.size();
    assert(n == A[0].size());
    vector<vector<T>> B = getIdentityMatrix<T>(n);
    for (int i = 0; i < n; ++i)
    {
        int idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (abs(A[j][i]) > abs(A[idx][i]))
            {
                idx = j;
            }
        }
        if (idx != i)
        {
            swap(A[i], A[idx]);
            swap(B[i], B[idx]);
        }
        T inv = 1 / A[i][i];
        for (int j = 0; j < n; ++j)
        {
            A[i][j] *= inv;
            B[i][j] *= inv;
        }
        for (int j = 0; j < n; ++j)
        {
            if (j == i)
            {
                continue;
            }
            T factor = A[j][i];
            for (int k = 0; k < n; ++k)
            {
                A[j][k] -= factor * A[i][k];
                B[j][k] -= factor * B[i][k];
            }
        }
    }
    return B;
}

void solve()
{
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}