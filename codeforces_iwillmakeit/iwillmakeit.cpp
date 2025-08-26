#include <iostream>
#include <algorithm>
using namespace std;
int main() {
  int t;
  cin >> t;
  while(t--) {
    int n,p;
    cin >> n >> p;
    int a[n + 1];
    for(int i = 1;i <= n;i++) cin >> a[i];
    int cur = a[p];
    int dist = a[p];
    sort(a + 1,a + n + 1);
    bool ans = true;
    for(int i = 1;i <= n;i++) {
      if(a[i] < cur) continue;
      if(a[i] - cur > dist) {
        ans = false;
      }
      cur = a[i];
    }
    if(ans) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
}