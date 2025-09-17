#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int task_num;
	cin >> task_num;
	vector<pair<int, int>> tasks(task_num);
	for (auto &[duration, deadline] : tasks) { cin >> duration >> deadline; }

	sort(tasks.begin(), tasks.end());

	long long time = 0;
	long long reward = 0;
	for (const auto &[duration, deadline] : tasks) {
		time += duration;
		reward += deadline - time;
	}

	cout << reward << endl;
}