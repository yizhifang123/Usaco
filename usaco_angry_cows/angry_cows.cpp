#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

using ll = long long;

const int MAX_POS = 1e9;

int main(){
    int n;
    cin >> n;
    vector<int> bales(n);
	for (int i = 0; i < n; i++) {
		cin >> bales[i];
		// to avoid floats, double all coordinates
	}
    sort(bales.begin(), bales.end());

}