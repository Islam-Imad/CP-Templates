#include <bits/stdc++.h>
using namespace std;

struct Kosaraju
{
    int n;
    int ncc = -1;
    vector<vector<int>> adj, radj;
    vector<int> order, comp;
    vector<bool> vis;

    Kosaraju(int n) : n(n), adj(n), radj(n), comp(n), vis(n)
    {
        adj.shrink_to_fit();
        radj.shrink_to_fit();
        comp.shrink_to_fit();
        vis.shrink_to_fit();
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    void dfs1(int u)
    {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v])
                dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int color)
    {
        comp[u] = color;
        for (int v : radj[u])
            if (comp[v] == -1)
                dfs2(v, color);
    }

    int build()
    {
        vis.assign(n, false);
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);

        reverse(order.begin(), order.end());

        fill(comp.begin(), comp.end(), -1);
        int color = 0;
        for (int u : order)
            if (comp[u] == -1)
                dfs2(u, color++);
        return ncc = color;
    }
};

struct TwoSat
{
    int n;
    Kosaraju ks;
    vector<bool> ans;

    TwoSat(int n) : n(n), ks(2 * n), ans(n) {}

    void add_clause(int u, bool fu, int v, bool fv)
    {
        ks.add_edge(2 * u + !fu, 2 * v + fv);
        ks.add_edge(2 * v + !fv, 2 * u + fu);
    }

    bool satisfiable()
    {
        ks.build();
        for (int i = 0; i < n; ++i)
            if (ks.comp[2 * i] == ks.comp[2 * i + 1])
                return false;
        for (int i = 0; i < n; ++i)
            ans[i] = ks.comp[2 * i] < ks.comp[2 * i + 1];
        return true;
    }
};


/*
    v >= 3 then v >= 2
    i [l, r] then i -> (>= l) and not(>= r + 1)
    === BOOLEAN ALGEBRA CHEATSHEET ===

■ BASIC OPERATIONS & SYMBOLS
--------------------------------
- AND (Conjunction):    A ∧ B, A & B, A · B
- OR (Disjunction):     A ∨ B, A | B, A + B
- NOT (Negation):       ¬A, ~A, A'
- IMPLICATION:          A → B, A ⇒ B
- EQUIVALENCE:          A ↔ B, A ≡ B

■ TRUTH TABLES
--------------------------------
| A | B | A∧B | A∨B | A→B | ¬A |
|---|---|-----|-----|-----|----|
| 0 | 0 |  0  |  0  |  1  | 1  |
| 0 | 1 |  0  |  1  |  1  | 1  |
| 1 | 0 |  0  |  1  |  0  | 0  |
| 1 | 1 |  1  |  1  |  1  | 0  |

■ KEY LAWS & IDENTITIES
--------------------------------
→ Identity:
   A ∨ 0 = A      A ∧ 1 = A

→ Domination:
   A ∨ 1 = 1      A ∧ 0 = 0

→ Idempotent:
   A ∨ A = A      A ∧ A = A

→ Commutative:
   A ∨ B = B ∨ A  A ∧ B = B ∧ A

→ Associative:
   (A ∨ B) ∨ C = A ∨ (B ∨ C)
   (A ∧ B) ∧ C = A ∧ (B ∧ C)

→ Distributive:
   A ∧ (B ∨ C) = (A ∧ B) ∨ (A ∧ C)
   A ∨ (B ∧ C) = (A ∨ B) ∧ (A ∨ C)

→ De Morgan’s:
   ¬(A ∧ B) = ¬A ∨ ¬B
   ¬(A ∨ B) = ¬A ∧ ¬B

→ Implication:
   A → B ≡ ¬A ∨ B

→ Contrapositive:
   A → B ≡ ¬B → ¬A

■ QUICK EXAMPLES
--------------------------------
- A ∧ ¬A = 0       (Contradiction)
- A ∨ ¬A = 1       (Tautology)
- ¬¬A = A          (Double Negation)
- A → B ≡ ¬B → ¬A  (Contrapositive)
*/

int main()
{
}
