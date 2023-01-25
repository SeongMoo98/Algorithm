#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string.h>
using namespace std;

#define MAX_NUTRIENT 50
#define COST_INDEX 4
#define INDEX 5

vector<vector<int>> nutrient;
vector<int> min_nutrient;
vector<int> answer;

int* min_cost = new int(0);
int* nutrient_sum = new int(0);
bool checked[MAX_NUTRIENT] = { 0, };
int N;

int comp(vector<int> v1, vector<int> v2) {
	return v1[COST_INDEX] < v2[COST_INDEX];
}

vector<int> operator+(vector<int> v1, vector<int> v2) {
	for (int i = 0; i < 5; i++)
		v1[i] += v2[i];
	return v1;
}

void init() {
	cin >> N;

	for (int i = 0; i < 4; i++) {
		int val; cin >> val;
		min_nutrient.push_back(val);
	}
	nutrient.push_back(vector<int>(6, 0));

	for (int i = 0; i < N; i++) {
		vector<int> temp;
		for (int j = 0; j < 5; j++) {
			int val; cin >> val;
			temp.push_back(val);
		}
		temp.push_back(i + 1);

		nutrient.push_back(temp);
	}

	sort(nutrient.begin(), nutrient.end(), comp);
}

int return_nutrient_sum(int index) {
	int ret = 0;
	for (int i = 0; i < 4; i++)
		ret += nutrient[index][i];
	return ret;
}

void init_solution() {
	vector<int> temp(5, 0);
	bool flag = false;

	for (int i = 1; i <= N; i++) {
		if (flag) break;

		temp = temp + nutrient[i];

		for (int j = 0; j < 4; j++) {
			if (temp[j] < min_nutrient[j]) {
				flag = false;
				break;
			}
			flag = true;
		}
		answer.push_back(nutrient[i][INDEX]);
		*nutrient_sum += return_nutrient_sum(i);
	}

	if (flag) *min_cost = temp.back();
	else {
		cout << "0";
		exit(0);
	}
}

bool check_nutrient(vector<int> current_node) {
	for (int j = 0; j < 4; j++) {
		if (current_node[j] < min_nutrient[j])
			return false;
	}
	return true;
}

void check_answer() {
	vector<int> temp;
	int temp_cost = 0, temp_sum = 0;

	for (int i = 1; i <= N; i++) {
		if (checked[i]) {
			temp.push_back(nutrient[i][INDEX]);
			temp_cost += nutrient[i][COST_INDEX];
			temp_sum += return_nutrient_sum(i);
		}
	}

	sort(answer.begin(), answer.end());
	sort(temp.begin(), temp.end());

	if (temp_cost < *min_cost) {
		*min_cost = temp_cost;
		*nutrient_sum = temp_sum;
		answer = temp;
	}
	else if (temp_cost == *min_cost) {
		if (*nutrient_sum < temp_sum) {
			*nutrient_sum = temp_sum;
			answer = temp;
		}
		else if (*nutrient_sum == temp_sum) {
			for (int i = 0; i < answer.size(); i++) {
				if (answer[i] > temp[i]) {
					answer = temp;
					break;
				}
			}
		}
	}

}

void BFS(int curr_index, vector<int> curr_node) {
	queue<vector<int>> q;

	checked[curr_index] = true;

	bool visited[MAX_NUTRIENT] = { 0, };
	memcpy(visited, checked, 50 * sizeof(bool));

	q.push(curr_node);

	while (!q.empty()) {
		vector<int> curr = q.front();
		q.pop();
		//i´Â next node
		for (int i = curr_index + 1; i <= N; i++) {
			if (visited[i] == false) {
				visited[i] = true;
				vector<int> next = curr + nutrient[i];

				if (*min_cost < next[COST_INDEX]) continue;

				if (check_nutrient(next)) {
					checked[i] = true;
					check_answer();
					checked[i] = false;
					continue;
				}
				else q.push(next);

				BFS(i, next);
				checked[i] = false;
			}
		}
	}
	return;
}

int main(void) {

	init();
	init_solution();
	BFS(0, nutrient[0]);
	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << " ";

	return 0;
}