#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 100
int Table[MAX];
int WorkDay[MAX];

//청소업체는 소비자들의 요청을 미리 받아 그 중에서 이익이 최대가 되도록 일정을 잡는다
//작업단위는 일(daily) 단위 이며 365*3(년)까지의 일정을 그 전에 모두 확정한다
//청소를 요청하는 고객들은 집 청소를 원하는 기간2)(일 단위)와 그때 지급할 비용을 HCC의 신청 Web을 통하여 등록한다
//집 청소를 신청한 고객을 i라고 할 때 그 신청 정보는 (bi,ei,ci)로 표현된다.
//bi는 작업의 시작일, ei는 종료일, ci는 제시한 청소의 비용(cost, 만원)을 나타낸다

//1 <= bi < ei <= 365*3을 항상 만족한다


//특정 시간에 두 군데 이상의 작업을 동시에 할 수 없다
//그리고 한번 시작한 작업은 해당 집의 작업이 완전히 끝날 때까지 중지하지 못한다
//작업 장소를 바꿀 때마다 균일하게 10만 원의 부가 비용이 발생한다고 가정한다.
//==> 같은 이득이라면 가능한 작업 장소의 개수를 줄이는 것이 이득이 된다
//조건을 만족하는 선에서 최대 이익을 확보하기 위하여 작업 일정을 꼼꼼하게 계산해야 한다

//만일 같은 액수의 이익을 보장하는 일정이 하나 이상 존재하면 그중에서 작업하는 일수가 제일 적은 것을 선택해야 한다


//입출력
//입력
//첫 줄에 신청한 작업의 수 N
//N개의 줄에 각각 요청한 청소작업의 정보 (bi, ei, ci)
//출력
//최대로 얻을 수 있는 이득 P ( 10만원의 부가비용을 뺸 순이익 )
//그것을 위한 최소 작업일 수 D


//https://enumclass.tistory.com/150
//counter를 추가해서 이동할때마다 -10을한다
//작업일수 기록 하고 max에서 작업일수 비교
// 
//DP Table에 profit을 기록


//****추가해야할 조건 *******
//같은 Profit일때 일수가 적은것 선택
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
	friend ostream& operator<<(ostream& os, Task t);
};
ostream& operator<<(ostream& os, Task t) {
	os << "Begin TIme : " << t.get_BeginTime();
	os << " End TIme : " << t.get_EndTime();
	os << " Cost : " << t.get_Cost();
	os << "\n\n";
	return os;
}

//Task를 beginTime이 빠른순으로 정렬
//만약 beginTime이 같다면 cost가 작은게 앞으로
int compare(Task a, Task b) {
	if (a.get_BeginTime() == b.get_BeginTime()) {
		return a.get_Cost() < b.get_Cost();
	}
	return a.get_BeginTime() < b.get_BeginTime();
}


void Job_Scheduling(vector<Task> schedule, int N) {

	vector<int>* task_Index = new vector<int>[N];
	if (N == 0) {
		cout << "0 0";
		return;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			
			if (schedule[i].get_BeginTime() > schedule[j].get_EndTime() && Table[i] < Table[j]) {
				task_Index[i] = task_Index[j];
				Table[i] = Table[j];
			}
		}
		//if문에 걸렸다면 Ti가 포함안된거고 안걸렸으면 Ti가 포함된것
		task_Index[i].push_back(i);
		Table[i] += schedule[i].get_Cost();
		for (int k : task_Index[i]) {
			WorkDay[i]+= schedule[k].get_EndTime() - schedule[k].get_BeginTime() + 1;
		}
	}

	for (int i = 0; i < N; i++) {
		int transfer = task_Index[i].size() - 1;
		Table[i] -= 10 * transfer;
	}

	//Max Profit을 갖는 Index
	int Index = 0;
	for (int i = 0; i < N; i++) {
		if (Table[i] > Table[Index]) {
			Index = i;
		}
		else if (Table[i] == Table[Index]) {
			if (WorkDay[i] <= WorkDay[Index]) {
				Index = i;
			}
		}
	}

	
	for (int i : task_Index[Index]) {
		cout << schedule[i];
	}
	cout << Table[Index] << " " << WorkDay[Index];

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

	

	return 0;
}





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

	int get_begintime() { return begin_time; }
	int get_endtime() { return end_time; }
	int get_cost() { return cost; }

};

int compare(Task a, Task b) {
	if (a.get_endtime() == b.get_endtime()) {
		return a.get_cost() < b.get_cost();
	}
	return a.get_endtime() < b.get_endtime();
}

int latestNonConflict(vector<Task> schedule, int i)
{
	for (int j = i - 1; j >= 0; j--) {
		if (schedule[j].get_endtime() < schedule[i].get_begintime())
			return j;
	}
	return -1;
}

void Job_Scheduling(vector<Task> schedule, int N) {

	//end_time을 기준으로 정렬
	//end_time이 빠를수록 앞쪽으로
	//이 때 end_time이 같으면 cost가 작은게 앞으로
	Table[0] = schedule[0].get_cost();
	work_day[0] = schedule[0].get_endtime() - schedule[0].get_begintime() + 1;

	for (int i = 1; i < N; i++) {
		int profit = schedule[i].get_cost();
		int work = schedule[i].get_endtime() - schedule[i].get_begintime() + 1;
		int l = latestNonConflict(schedule, i);
		if (l != -1) {
			profit = Table[l] + profit - 10;
			work += work_day[l];
		}


		// Store maximum of including and excluding
		if (profit == Table[i - 1]) {
			Table[i] = profit;
			work_day[i] = min(work, work_day[i - 1]);
		}
		else {
			if (profit > Table[i - 1]) {
				Table[i] = profit;
				work_day[i] = work;
			}
			else {
				Table[i] = Table[i - 1];
				work_day[i] = work_day[i - 1];
			}
		}

		/*for (int j = i - 1; j >= 0; j--) {
			if (Table[i] == Table[j]) {
				if (work_day[j] + (schedule[i].get_endtime() - schedule[i].get_begintime() + 1) < work) {
					profit = Table[j] + schedule[i].get_cost() - 10;
					work = work_day[j] + schedule[i].get_endtime() - schedule[i].get_begintime() + 1;
				}
			}
		}
		Table[i] = profit;
		work_day[i] = work;*/
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
	cout << Table[N - 1] << " " << work_day[N - 1];
	return 0;
}
