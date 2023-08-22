//Code tested with: https://cses.fi/problemset/task/2195/
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define nl '\n'
#define ll long long
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define P complex<int>
#define X real()
#define Y imag()
 
int orientation(P a, P b, P c) {
  double v = a.X * (b.Y - c.Y) + b.X * (c.Y - a.Y) + c.X * (a.Y - b.Y);
  if (v < 0)
    return -1; // clockwise
  if (v > 0)
    return +1; // counter-clockwise
  return 0;
}
 
vector<P> hull(vector<P> &v) {
  vector<P> ans = {v[0]};
  for (int i = 1; i < v.size(); i++) {
    while (ans.size() > 1) {
      P b = ans.back();
      ans.pop_back();
      P a = ans.back();
      P c = v[i];
      if (orientation(a, b, c) !=
          1) { // si no es clockwise (que sea colineal o counter-clockwise).
        ans.push_back(b);
        break;
      }
    }
    ans.push_back(v[i]);
  }
  return ans;
}
 
signed main() {
  fast;
 
  int n;
  cin >> n;
  vector<P> v(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    v[i] = {x, y};
  }
  // Do Convex-Hull from the leftmost and bottommost point:
  sort(v.begin(), v.end(), [](const P &a, const P &b) {
    return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
  });
  vector<P> v1 = hull(v);
 
  // Do Convex-Hull from the rightmost and topmost point:
  sort(v.begin(), v.end(), [](const P &a, const P &b) {
    return (a.X == b.X) ? (a.Y > b.Y) : (a.X > b.X);
  });
  vector<P> v2 = hull(v);
 
  for (int i = 1; i < v2.size(); i++) {
    if (v2[i] == v1[0])
      break;
    v1.push_back(v2[i]);
  }
  cout << v1.size() << endl;
  for (auto i : v1)
    cout << i.X << " " << i.Y << nl;
}