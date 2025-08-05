# Mobius Function Implementation

```cpp
const int N = 5e5 + 9;

int mob[N];
void mobius()
{
    mob[1] = 1;
    for (int i = 2; i < N; i++)
    {
        mob[i]--;
        for (int j = i + i; j < N; j += i)
        {
            mob[j] -= mob[i];
        }
    }
}
```

## Notes

- F[n] = sigma (d | n) g(d);
- g[d] = sigma (d | n) mob[d] * F[n/d];
- g[d] = sigma (d | n) mob(n/d) * F[d];
- phi[n] = sigma (d | n) mob(d) * (n / d);
- phi[n] / n = sigma (d | n) (mob(d) / d);