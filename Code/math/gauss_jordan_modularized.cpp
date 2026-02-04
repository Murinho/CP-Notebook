
/*
Solves A x = b (mod MOD).
Input matrix 'a' is n x (m+1) augmented: a[i][0..m-1] are coefficients, a[i][m] is b[i].
Returns:
  0 -> no solution
  1 -> unique solution (ans filled)
  2 -> infinitely many solutions (ans is one solution with free vars = 0)
*/
static inline int gauss_mod(vector<vector<ll>> a, vector<ll> &ans){
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);

    for(int col = 0, row = 0; col < m && row < n; ++col){
        int sel = -1;
        for(int i = row; i < n; ++i){
            if (a[i][col] != 0){
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;

        swap(a[sel], a[row]);
        where[col] = row;

        // Scale pivot row so pivot becomes 1
        ll inv_pivot = modpow(a[row][col], MOD-2);
        for(int j = col; j <= m; ++j){
            a[row][j] = (a[row][j] * inv_pivot ) % MOD;
        }

        // Eliminate this column from all other rows
        for(int i = 0; i < n; ++i){
            if (i == row) continue;
            if (a[i][col] == 0) continue;

            ll factor = a[i][col]; // since pivot is 1
            for(int j = col; j <= m; ++j){
                a[i][j] = (a[i][j] - (ll)(factor * a[row][j] % MOD));
                a[i][j] += MOD;
                a[i][j] %= MOD;
            }
        }

        ++row;
    }

    // Build one solution (free vars = 0)
    ans.assign(m, 0);
    for(int i = 0; i < m; ++i){
        if (where[i] != -1){
            ans[i] = a[where[i]][m]; // pivot is 1
        }
    }

    // Check consistency: 0...0 | c (c != 0) => no solution
    for(int i = 0; i < n; ++i){
        bool all0 = true;
        for(int j = 0; j < m; ++j){
            if (a[i][j] != 0){
                all0 = false;
                break;
            }
        }
        if (all0 && a[i][m] != 0) return 0;
    }

    // If any variable is free -> infinite solutions
    for(int i = 0; i < m; ++i){
        if (where[i] == -1) return 2;
    }
    return 1;
}