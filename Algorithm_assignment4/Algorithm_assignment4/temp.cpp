#include "timebomb.h"
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

//N���� ȭ�� ��ۿ� �����̳� �ڽ� �� �ϳ��� ������ź�� �����Ǿ� �ִ�
//�ִ��� �̸��ð��� �� ������ �ڽ��� ã�Ƽ� �����ؾ��Ѵ�
//������ź�� ��ü N���� �ڽ� �߿��� 2��°�� ���ſ� �ڽ��� ����ִ�

//�� �ڽ� B[i], B[j]�� Ŀ�ٶ� �ü� ���� ��ġ�� �÷� � ���� "�� ���ſ�"���� ����� �� �ִ�
//�ּ����� �񱳸����� �� ��°�� ���ſ� �ڽ��� ã�Ƴ���� �Ѵ�


//��� �ڽ��� ���Դ� �ٸ��ٰ� ����
// 
//box_ready() - ������ �غ�
//box_size() - ��ü �ڽ��� ���� Ȯ��
//�ڽ��� 1���� N������ �������� ��ȣ - B[1]���� B[N]
//box_comp(i, j) - B[i]�� B[j]�� ���� �� ���
// B[i] > B[j] ==> 1
// B[i] < B[j] ==> -1
// �� �ܿ��� 0
//box_report() - ������ź�� ��� �ڽ��� index this�� ������


//box_comp(i, j) �Լ��� ȣ�� ��� Ƚ���� �ڽ��� ������ N�̶�� ������ 
//�ִ� b(N) = N + [log2 N] + 1������ ���ȴ� ( [x] - ceiling �ø� ) 


//���� �ڵ忡 �ѱ� �ּ��� ���� ��� ���� ȭ���� �� �� �־����ϴ�
vector<int> max2;
int compare(vector<int> Index,int result, int size) {
	vector<int> temp;
	if (Index.size() == 1) {
		return Index[0];
	}

	for (int i = 0; i < size / 2; i += 2) {
		result = box_comp(Index[i], Index[i + 1]);
		if (result == 1) {
			temp.push_back(Index[i]);
		}
		else if (result == -1) {
			temp.push_back(Index[i + 1]);
		}
		else {
			return -1;
		}
	}

	if (Index.size() % 2 != 0) {
		temp.push_back(*Index.end());
	}
	
	int max_Index = compare(temp, result, Index.size());
	if (max_Index % 2 == 0) {
		max2.push_back(temp[max_Index - 1]);
	}
	else {
		max2.push_back(temp[max_Index + 1]);
	}

}
int main(void) {

	int N, result, bomb;
	box_ready(); //1. ���� ���� ȣ���ؾ���
	N = box_size(); // 2. ���� Ȯ��

	vector<int> Index;
	for (int i = 1; i <= N; i++) {
		Index.push_back(i);
	}
	
	int max = compare(Index, result, N);
	bomb = compare(max2, result, max2.size());


	box_report(bomb); //���� ����. �����
	
	











//#include "timebomb.h"
#include<iostream>
#include<vector>
	using namespace std;

	int N = 10;
	int Box[11] = { 0, 1, 10, 2 ,9 ,3 ,8 ,4 ,7 ,5 ,6 };

	vector<int> max2;
	int Max;

	int box_comp(int i, int j) {
		if (Box[i] > Box[j])
			return 1;
		else if (Box[i] < Box[j])
			return -1;
		else
			return 0;
	}

	void find_max2(vector<int> Index, int size) {
		for (int i = 0; i < size; i++) {
			if (Index[i] == Max) {
				if (i % 2 == 0)
					max2.push_back(Index[i + 1]);
				else
					max2.push_back(Index[i - 1]);
				return;
			}
		}
	}

	int compare(vector<int> Index, int result, int size) {
		vector<int> temp;
		if (Index.size() == 2) {
			result = box_comp(Index[0], Index[1]);
			if (result == 1) {
				Max = Index[0];
				max2.push_back(Index[1]);
			}
			else if (result == -1) {
				Max = Index[1];
				max2.push_back(Index[0]);

			}
			else
				Max = -1;
			return Max;
		}

		if (Index.size() % 2 != 0)
			size -= 2;

		for (int i = 0; i < size; i += 2) {
			result = box_comp(Index[i], Index[i + 1]);
			if (result == 1)
				temp.push_back(Index[i]);
			else if (result == -1)
				temp.push_back(Index[i + 1]);
			else
				return -1;
		}

		if (Index.size() % 2 != 0) {
			temp.push_back(Index[Index.size() - 1]);
		}


		int num = compare(temp, result, temp.size());
		if (Max != 0) {
			find_max2(Index, Index.size());
			return num;
		}
	}


	int main(void) {
		//int N;
		int result = 0, bomb;
		//box_ready(); 
		//N = box_size();

		vector<int> Index;
		for (int i = 1; i <= N; i++)
			Index.push_back(i);

		compare(Index, result, N);

		bomb = compare(max2, result, max2.size());
		cout << bomb;
		//box_report(bomb);
	}