#include <bits/stdc++.h>

using namespace std;

int main(){
	long long k, m, n; cin >> k >> m >> n;
	vector<pair<long long, long long>> locations; vector<long long> res;
	for(long long i = 0; i < k; i++){
		long long p, t; 
        cin >> p >> t;
		locations.push_back({p, t});
	}
	for(long long i = 0; i < m; i++){
		long long f; 
        cin >> f;
		locations.push_back({f, -1});
	}
	sort(begin(locations), end(locations));
	long long twoCow = 0, lst = -1;
	for(long long i = 0; i < k + m; i++){
		if(locations[i].second != -1){
			twoCow += locations[i].second;
		} else {
			if(lst == -1){
				res.push_back(twoCow);
			} else {
				long long oneCow = 0, curSum = 0;
				long long l = lst + 1, r = lst + 1;
				while(r <= i){
					if(locations[r].second == -1){
						break;
					} else {
						long long dist1 = (locations[r].first - locations[l].first);
						long long dist2 = (locations[r].first - locations[lst].first);
						long long dist3 = (locations[i].first - locations[r].first);
						if(dist1 <= dist2 && dist1 <= dist3){
							curSum += locations[r].second;
							r++;
						} else {
							oneCow = max(oneCow, curSum);
							curSum -= locations[l].second;
							l++;
						}
					}
				}
				res.push_back(oneCow);
				res.push_back(twoCow - oneCow);
			}
			lst = i;
			twoCow = 0;
		}
	}
	res.push_back(twoCow);
	sort(begin(res), end(res), greater<long long>()); long long ans = 0;
	for(long long i = 0; i < n; i++){
		ans += res[i];
	}
	cout << ans << endl;
}