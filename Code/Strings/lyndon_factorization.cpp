// A Lyndon word is a non-empty string that is strictly smaller than any of its non-trivial suffixes.
vector<string> duval(string const& s){
    int i = 0;
    vector<string> factorization;
    while (i < sz(s)) {
        int j = i + 1, k = i;
        while (j < sz(s) && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) {
            factorization.pb(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

string duvalMinShift(string s){ // finds the minimum cyclic shift of a string.
    s += s;
    int i = 0, ans = 0;
    while (i < sz(s) / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < sz(s) && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) i += j - k;
    }
    return s.substr(ans, sz(s) / 2);
}