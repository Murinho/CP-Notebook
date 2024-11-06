const ll maxn = 1e7+1;
ll mobius[maxn],sum[maxn];
/* Mobius function: mu(n)
    mu(n) = 1, if n = 1.
    mu(n) = 0, if n has a squared prime factor.
    mu(n) = (-1)^k, if n is a product of k distinct prime factors.
*/
void computeMobius(){
    mobius[1] = -1;
    for (int i = 1; i < maxn; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i];
            for (int j = 2 * i; j < maxn; j += i) { mobius[j] += mobius[i]; }
        }
    }
}