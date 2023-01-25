#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX 101
int Table[MAX];
int Work[MAX];

class Task {
private:
	int begin_time;
	int end_time;
	int cost;
public:
	Task(int b, int e, int c) { begin_time = b, end_time = e; cost = c; }

	int get_begintime() { return begin_time; }
	int get_endtime() { return end_time; }
	int get_cost() { return cost; }

};


//end_time을 기준으로 정렬
//end_time이 빠를수록 앞쪽으로
//이 때 end_time이 같으면 cost가 작은게 앞으로
int compare(Task a, Task b) {
	if (a.get_endtime() == b.get_endtime()) {
		return a.get_cost() < b.get_cost();
	}
	return a.get_endtime() < b.get_endtime();
}
//안겹치는 Task중 Index가 제일 큰 것
int Latest_Task(vector<Task> schedule, int i)
{
	for (int j = i - 1; j >= 0; j--) {
		if (schedule[j].get_endtime() < schedule[i].get_begintime())
			return j;
	}
	return -1;
}

void Job_Scheduling(vector<Task> schedule, int N) {

	Table[0] = schedule[0].get_cost();
	Work[0] = schedule[0].get_endtime() - schedule[0].get_begintime() + 1;

	for (int i = 1; i < N; i++) {
		int profit = schedule[i].get_cost();
		int work_day = schedule[i].get_endtime() - schedule[i].get_begintime() + 1;
		int index = Latest_Task(schedule, i);
		if (index != -1) {
			profit = Table[index] + profit - 10;
			work_day += Work[index];
		}
			
		if (profit == Table[i - 1]) {
			Table[i] = profit;
			Work[i] = min(work_day, Work[i - 1]);
		}
		else {
			if (profit > Table[i - 1]) {
				Table[i] = profit;
				Work[i] = work_day;
			}
			else {
				Table[i] = Table[i - 1];
				Work[i] = Work[i-1];
			}
		}
	}		
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
	
	Job_Scheduling(schedule, N);
	cout << Table[N - 1] << " " << Work[N - 1];
	return 0;
}
