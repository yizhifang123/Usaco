#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pl = pair<ll, ll>;
using vl = vector<ll>;

#define forn(i, n) for(ll i = 0; i < n; i++)
#define rofn(i, n) for(ll i = n - 1; i >= 0; i--)
#define f first
#define s second

int main(){
	ll n; cin >> n;
	vl h(n), l(n), r(n);
	stack<pl> st1, st2;
	forn(i, n){
		cin >> h[i];
		l[i] = i, r[i] = i;
	}
	forn(i, n){
		while(!st1.empty()){
			if(st1.top().f > h[i]){
				l[i] = st1.top().s;
				break;
			} else {
				st1.pop();
			}
		}
		st1.push({h[i], i});
	}
	rofn(i, n){
		while(!st2.empty()){
			if(st2.top().f > h[i]){
				r[i] = st2.top().s;
				break;
			} else {
				st2.pop();
			}
		}
		st2.push({h[i], i});
	}
	ll res = 0;
	forn(i, n){
		if(i != l[i]){
			res += (i - l[i] + 1);
		}
		if(i != r[i]){
			res += (r[i] - i + 1);
		}
	}
	cout << res << endl;
}