#include <bits/stdc++.h>
using namespace std;

int count_prefix(const vector<int> &v, int r) {
	return lower_bound(begin(v), end(v), r) - begin(v);
}

struct Wavelet {
	vector<int> inds;
	Wavelet *l, *r;
	void build(const vector<int> &A, int b) {
		if (b == 0 || inds.empty()) return;
		l = new Wavelet();
		r = new Wavelet();
		for (int x : inds) {
			if (A[x] & (1 << (b - 1))) r->inds.push_back(x);
			else l->inds.push_back(x);
		}
		l->build(A, b - 1);
		r->build(A, b - 1);
	}
	// k-th (0-indexed) smallest value, only considering A[l, r)
	int range_kth_smallest(int l, int r, int k, int b) {
		if (b == 0) return 0;
		int num_left = count_prefix(this->l->inds, r) - count_prefix(this->l->inds, l);
		if (k < num_left) return this->l->range_kth_smallest(l, r, k, b - 1);
		return (1 << (b - 1)) + this->r->range_kth_smallest(l, r, k - num_left, b - 1);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;
	vector<int> A(N);
	for (int &a : A) cin >> a;

	// build tree
	Wavelet *root = new Wavelet();
	root->inds.resize(N);
	iota(begin(root->inds), end(root->inds), 0);
	const int MAX_BIT = 30;
	root->build(A, MAX_BIT);

	// answer queries
	for (int q = 0; q < Q; ++q) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << root->range_kth_smallest(l, r, k, MAX_BIT) << "\n";
	}
}