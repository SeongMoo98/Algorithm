#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct Task {
	int cost;
	int deadline;
};

int compare(Task a, Task b) {
	if (a.cost == b.cost) {
		return a.deadline > b.deadline;
	}
	return a.cost > b.cost;
}

int findMax(int** Table, int T, int k) {
	int sum = 0;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < T; j++)
			sum += Table[i][j];
	}
	return sum;
}

int main(void) 
{
	int N, T, k;
	cin >> N >> T >> k;

	int** Table = new int*[k];
	for (int i = 0; i < k; i++)
		Table[i] = new int[T] {0};

	bool* flag = new bool[T];

	vector<Task> v;
	bool* task_flag = new bool[N] {false};
	for (int i = 0; i < N; i++) {
		Task t;
		cin >> t.cost >> t.deadline;
		v.push_back(t);
	}
	//cost를 기준으로 내림차순 정렬
	sort(v.begin(), v.end(), compare);

	int machine_index = 0;
	while (k > machine_index) {
		fill(flag, flag + T, false);
		for (int i = 0; i < N; i++) {
			if (task_flag[i])
				continue;
			for (int j = v[i].deadline - 1; j >= 0; j--) {
				if (flag[j] == false) {
					Table[machine_index][j] = v[i].cost;
					task_flag[i] = true;
					flag[j] = true; 
					break;
				}
			}
		}
		machine_index++;
	}	

	int max_profit = findMax(Table, T, k);

	int gap = 101;
	//Task가 모두선택됨 ==> 제일 작은거 뺸다
	for (int i = 0; i < N; i++) {
		if (i == N - 1 && task_flag[i]) {
			cout << max_profit << " " << max_profit - v[i].cost;
			return 0;
		}
		if (task_flag[i]) continue;
		else break;
	}
	
	machine_index = 0;

	for (int i = 0; i < N; i++) {
		if (task_flag[i])
			continue;
		while (k > machine_index) {
			for (int j = v[i].deadline - 1; j >= 0; j--) {
				if (Table[machine_index][j] != 0 && Table[machine_index][j] - v[i].cost > 0); {
					gap = min(gap, Table[machine_index][j] - v[i].cost);
				}
			}
			machine_index++;
		}
		machine_index = 0;
	}

	//선택된 job에서 제일 작은애를 뺴느냐
	int Min = 0;
	for (int i = N - 1; i >= 0; i--) {
		if (task_flag[i]) {
			Min = v[i].cost;
			break;
		}
	}
	gap = min(gap, Min);
	cout << max_profit << " " << max_profit - gap;
	return 0;
}