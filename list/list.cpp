#include <vector>
#include <iostream>

using namespace std;

static const int MAX = 2147483647;

int main () {
	int n, k;
	cin >> n >> k;

	vector <int> q;
	vector <int> mins;

	int tmin = MAX;

	for (int i = 0; i < k; i++) {
		int t;
		cin >> t;
		tmin = t < tmin ? t : tmin;
		q.push_back(t);
	}

	mins.push_back(tmin);

	for (int i = k; i < n; i++) {
		tmin = MAX;
		int t;
		cin >> t;
		q.push_back(t);
		if (t <= mins[i - k])
			mins.push_back(t);
		else if (q[0] == mins[i - k]) {
			for (int j = 1; j <= k; j++) {
				tmin = q[j] < tmin ? q[j] : tmin;
			}
			mins.push_back(tmin);
		} else mins.push_back(mins[i - k]);
		q.erase(q.begin());
	}

	for (int i = 0; i < n - k + 1; i++) {
		cout << mins[i] << endl;
	}
	return 0;
}