#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);

	long long k, m, n;
	cin >> k >> m >> n;

	pair<long long, long long> a[k+m];

	for(long long i = 0; i < k; i++) cin >> a[i].first >> a[i].second;

	for(long long i = 0; i < m; i++)
	{
		cin >> a[i+k].first;
		a[i+k].second = -1;
	}

	sort(a, a+k+m);

	long long ind = -1, sum = 0;

	vector<long long> v;

	for(long long i = 0; i < k+m; i++)
	{
		if(a[i].second==-1)
		{
			if(ind==-1)
			{
				v.emplace_back(sum);
			}
			else
			{
				long long mx = 0, sm = 0, l = ind+1, r = ind;
				while(l<=r+1 && r<i)
				{
					long long x = min(a[i].first - a[l].first, a[l].first - a[ind].first);
					long long y = min(a[i].first - a[r+1].first, a[r+1].first - a[ind].first);

					if(a[l].first + x - 1 >= a[r+1].first + y - 1)
					{
						r++;
						sm += a[r].second;
						mx = max(sm, mx);
					}
					else
					{
						sm -= a[l].second;
						l++;
					}
				}

				v.emplace_back(mx);
				v.emplace_back(sum - mx);
			}

			sum = 0;
			ind = i;
		}
		else
		{
			sum += a[i].second;
		}
	}

	v.emplace_back(sum);

	long long ans = 0;

	sort(v.rbegin(), v.rend());

	for(long long i  = 0; i < n; i++)
	{
		ans += v[i];
	}

	cout << ans << "\n";
}