#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 100
int Table[MAX];
int WorkDay[MAX];

//û�Ҿ�ü�� �Һ��ڵ��� ��û�� �̸� �޾� �� �߿��� ������ �ִ밡 �ǵ��� ������ ��´�
//�۾������� ��(daily) ���� �̸� 365*3(��)������ ������ �� ���� ��� Ȯ���Ѵ�
//û�Ҹ� ��û�ϴ� ������ �� û�Ҹ� ���ϴ� �Ⱓ2)(�� ����)�� �׶� ������ ����� HCC�� ��û Web�� ���Ͽ� ����Ѵ�
//�� û�Ҹ� ��û�� ���� i��� �� �� �� ��û ������ (bi,ei,ci)�� ǥ���ȴ�.
//bi�� �۾��� ������, ei�� ������, ci�� ������ û���� ���(cost, ����)�� ��Ÿ����

//1 <= bi < ei <= 365*3�� �׻� �����Ѵ�


//Ư�� �ð��� �� ���� �̻��� �۾��� ���ÿ� �� �� ����
//�׸��� �ѹ� ������ �۾��� �ش� ���� �۾��� ������ ���� ������ �������� ���Ѵ�
//�۾� ��Ҹ� �ٲ� ������ �����ϰ� 10�� ���� �ΰ� ����� �߻��Ѵٰ� �����Ѵ�.
//==> ���� �̵��̶�� ������ �۾� ����� ������ ���̴� ���� �̵��� �ȴ�
//������ �����ϴ� ������ �ִ� ������ Ȯ���ϱ� ���Ͽ� �۾� ������ �Ĳ��ϰ� ����ؾ� �Ѵ�

//���� ���� �׼��� ������ �����ϴ� ������ �ϳ� �̻� �����ϸ� ���߿��� �۾��ϴ� �ϼ��� ���� ���� ���� �����ؾ� �Ѵ�


//�����
//�Է�
//ù �ٿ� ��û�� �۾��� �� N
//N���� �ٿ� ���� ��û�� û���۾��� ���� (bi, ei, ci)
//���
//�ִ�� ���� �� �ִ� �̵� P ( 10������ �ΰ������ �A ������ )
//�װ��� ���� �ּ� �۾��� �� D


//https://enumclass.tistory.com/150
//counter�� �߰��ؼ� �̵��Ҷ����� -10���Ѵ�
//�۾��ϼ� ��� �ϰ� max���� �۾��ϼ� ��
// 
//DP Table�� profit�� ���


//****�߰��ؾ��� ���� *******
//���� Profit�϶� �ϼ��� ������ ����
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

//Task�� beginTime�� ���������� ����
//���� beginTime�� ���ٸ� cost�� ������ ������
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
		//if���� �ɷȴٸ� Ti�� ���ԾȵȰŰ� �Ȱɷ����� Ti�� ���ԵȰ�
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

	//Max Profit�� ���� Index
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

	//end_time�� �������� ����
	//end_time�� �������� ��������
	//�� �� end_time�� ������ cost�� ������ ������
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
