template <typename T>
struct sqrt_decomposition
{
    int n, len;
    vector<T> arr, block;
    sqrt_decomposition(int size)
    {
        n = size;
        len = sqrt(n) + 1;
        arr.resize(n, 0);
        block.resize(len, 0);
    }
    sqrt_decomposition(vector<T> &a)
    {
        n = a.size();
        len = sqrt(n) + 1;
        arr = a;
        block.resize(len, 0);
        for (int i = 0; i < n; ++i)
        {
            block[i / len] += arr[i];
        }
    }
    void update(int idx, T val)
    {
        block[idx / len] -= arr[idx];
        arr[idx] = val;
        block[idx / len] += arr[idx];
    }
    T query(int r)
    {
        if (r < 0)
            return 0;
        T res = 0;
        for (int i = 0; i < r / len; ++i)
        {
            res += block[i];
        }
        for (int i = (r / len) * len; i <= r; ++i)
        {
            res += arr[i];
        }
        return res;
    }
    T query(int l, int r)
    {
        if (l > r)
            return 0;
        if(block[l / len] == block[r / len]) {
            T res = 0;
            for (int i = l; i <= r; ++i)
            {
                res += arr[i];
            }
            return res;
        }
        T res = 0;
        int start_block = l / len;
        int end_block = r / len;
        for (int i = start_block + 1; i < end_block; ++i)
        {
            res += block[i];
        }
        for (int i = l; i < (start_block + 1) * len; ++i)
        {
            res += arr[i];
        }
        for (int i = end_block * len; i <= r; ++i)
        {
            res += arr[i];
        }
        return res;
    }
};