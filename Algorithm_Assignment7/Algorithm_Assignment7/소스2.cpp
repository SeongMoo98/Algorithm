#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//#define MAX 101
//int Table[MAX];
//int work_day[MAX];

class Task {
private:
	int begin_time;
	int end_time;
	int cost;
public:
	Task(int b, int e, int c) { begin_time = b, end_time = e; cost = c; }

	int get_BeginTime() { return begin_time; }
	int get_EndTime() { return end_time; }
	int get_Cost() { return cost; }

	void set_Task(int b, int e, int c) {
		begin_time = b;
		end_time = e;
		cost = c;
	}
};


int compare(Task a, Task b) {
	if (a.get_BeginTime() == b.get_BeginTime()) {
		return a.get_Cost() < b.get_Cost();
	}
	return a.get_BeginTime() < b.get_BeginTime();
}

void Job_Scheduling(vector<Task> schedule, int N, pair<int, int> *Table) {

	vector<int>* task_Index = new vector<int>[N];

	for (int i = 0; i < N; i++) {
		if (schedule[i].get_Cost() <= 0) {
			continue;
		}
		for (int j = 0; j < i; j++) {
			if (schedule[i].get_BeginTime() > schedule[j].get_EndTime() && Table[i].first <= Table[j].first) {
				if (Table[i].first < Table[j].first) {
					task_Index[i] = task_Index[j];
					Table[i].first = Table[j].first;
					Table[i].second = Table[j].second;
				}
				else {
					if (Table[i].second > Table[j].second) {
						task_Index[i] = task_Index[j];
						Table[i].first = Table[j].first;
						Table[i].second = Table[j].second;
					}
				}
			}
		}
		task_Index[i].push_back(i);
		Table[i].first += schedule[i].get_Cost();
		Table[i].second += schedule[i].get_EndTime() - schedule[i].get_BeginTime() + 1;

	}

	for (int i = 0; i < N; i++) {
		if (task_Index[i].size() == 0)
			continue;
		Table[i].first -= 10 * (task_Index[i].size() - 1);
	}

	int Index = 0;
	for (int i = 0; i < N; i++) {
		if (Table[i].first > Table[Index].first) {
			Index = i;
		}
		else if (Table[i].first == Table[Index].first) {
			if (Table[i].second < Table[Index].second) {
				Index = i;
			}
		}
	}
	cout << Table[Index].first << " " << Table[Index].second;
}


int main(void) {

	int N;
	cin >> N;
	pair<int, int>* Table = new pair<int, int>[N];
	for (int i = 0; i < N; i++) {
		Table[i].first = 0;
		Table[i].second = 0;
	}

	vector<Task> schedule;

	for (int i = 0; i < N; i++) {
		int b, e, c;
		cin >> b >> e >> c;
		schedule.push_back(Task(b, e, c));
	}

	sort(schedule.begin(), schedule.end(), compare);

	Job_Scheduling(schedule, N, Table);

	return 0;
}
