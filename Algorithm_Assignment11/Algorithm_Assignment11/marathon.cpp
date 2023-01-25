#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

vector<pair<char, int>> mara[26];
bool visited[26] = { 0, };
const int LENGTH = 42;

int compare_end(pair<char, int> p1, pair<char, int> p2) {
	return p1.first < p2.first;
}

void print_vertex() {
	int sum = 0;
	for (int i = 0; i < 26; i++) {
		if (visited[i])
			sum++;
	}
	cout << sum << endl;
	for (int i = 0; i < 26; i++) {
		if (visited[i])
			cout << (char)(i + 'a') << " ";
	}
}

void backtracking(int start) {
	stack <vector<pair<char, int>>> s;
	s.push(mara[start]);
	visited[start] = true;
	int weight_sum = 0;

	stack<int> back_stack;
	bool back = false;

	while (!s.empty()) {
		vector<pair<char, int>> current = s.top();
		s.pop();
		
		for (int i = 0; i < current.size(); i++) {
			vector<pair<char, int>> next = mara[current[i].first - 'a'];
			weight_sum += current[i].second;


			if (visited[current[i].first - 'a']) {
				back = true;
				weight_sum -= current[i].second;
				continue;
			}
			else {

				if (weight_sum > LENGTH) {
					weight_sum -= current[i].second;
					continue;
				}
				else if (weight_sum == LENGTH) {
					for (int j = 0; j < next.size(); j++) {
						if (next[j].first == 'a') {
							visited[current[i].first - 'a'] = true;
							return;
						}
					}
					weight_sum -= current[i].second;
					continue;
				}
				else {
					back = false;
					visited[current[i].first - 'a'] = true;
					back_stack.push(current[i].second);

					s.push(current);
					s.push(next);
					break;
				}
			
			}
		}

		if (back) {
			if (!back_stack.empty()) {
				weight_sum -= back_stack.top();
				back_stack.pop();
			}
		}

	}

}




int main() {

	int vertex, edge;
	cin >> vertex >> edge;

	for (int i = 0; i < edge; i++) {
		char start, end;
		int weight;

		cin >> start >> end >> weight;

		mara[start - 'a'].push_back(pair<char, int>(end, weight));
		mara[end - 'a'].push_back(pair<char, int>(start, weight));
	}

	for (int i = 0; i < 26; i++) {
		if (mara[i].size() == 0)
			continue;
		sort(mara[i].begin(), mara[i].end(), compare_end);
	}

	backtracking(0);
	print_vertex();
	return 0;
}
