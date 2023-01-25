#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 101
int Table[MAX];
int work_day[MAX];
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

pair<int,int> Job_Scheduling(vector<Task> schedule, int N) {

	

	if (schedule.size() == 0) {
		return pair<int, int>(0, 0);
	}	
	if (schedule.size() == 1) {
		return pair<int, int>(schedule[0].get_Cost(), schedule[0].get_EndTime() - schedule[0].get_BeginTime() + 1);
	}

	Table[0] = schedule[0].get_Cost();
	work_day[0]= schedule[0].get_EndTime() - schedule[0].get_BeginTime() + 1;
	for (int i = 1; i < N; i++) {
		if (schedule[i].get_Cost() <= 0) {
			continue;
		}
		int Max_Profit = schedule[i].get_Cost();
		int Min_WorkDay = schedule[i].get_EndTime() - schedule[i].get_BeginTime() + 1;
		//schedule[i]를 포함
		//i를 무조건 넣고 endTime 안겹치는것 중 Max
		vector<Task> beforeTask;
		for (int j = 0; j < i; j++) {
			if (schedule[i].get_BeginTime() > schedule[j].get_EndTime()) {
				beforeTask.push_back(schedule[j]);
			}
		}
		if (beforeTask.size() != 0) {
			pair<int, int> result = Job_Scheduling(beforeTask, beforeTask.size());
			Max_Profit = result.first + schedule[i].get_Cost() - 10;
			Min_WorkDay = result.second + (schedule[i].get_EndTime() - schedule[i].get_BeginTime() + 1);
		}

		//schedule[i]를 포함 x는 Table[i-1]
		if (Max_Profit == Table[i - 1]) {
			Table[i] = min(Min_WorkDay, Table[i - 1].second);
		}
		Table[i] = max(Max_Profit, Table[i - 1]);
		work_day[i] = Min_WorkDay;
	}
	return Table[N - 1];

}


int main(void) {

	int N;
	cin >> N;
	
	vector<Task> schedule;

	for (int i = 0; i < N; i++) {
		int b, e, c;
		cin >> b >> e >> c;
		schedule.push_back(Task(b, e, c));
	}

	sort(schedule.begin(), schedule.end(), compare);

	pair<int, int> result = Job_Scheduling(schedule, N);
	cout<<result.first<< " " <<result.second;

	return 0;
}








