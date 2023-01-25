#include "timebomb.h"
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

//N개의 화물 운송용 컨테이너 박스 중 하나에 시한폭탄이 장착되어 있다
//최대한 이른시간에 이 문제의 박스를 찾아서 제거해야한다
//시한폭탄은 전체 N개의 박스 중에서 2번째로 무거운 박스에 들어있다

//두 박스 B[i], B[j]를 커다란 시소 같은 장치에 올려 어떤 것이 "더 무거운"지만 계산할 수 있다
//최소한의 비교만으로 두 번째로 무거운 박스를 찾아내어야 한다


//모든 박스의 무게는 다르다고 가정
// 
//box_ready() - 데이터 준비
//box_size() - 전체 박스의 개수 확인
//박스는 1부터 N번까지 순차적인 번호 - B[1]부터 B[N]
//box_comp(i, j) - B[i]와 B[j]의 무게 비교 결과
// B[i] > B[j] ==> 1
// B[i] < B[j] ==> -1
// 그 외에는 0
//box_report() - 시한폭탄이 담긴 박스의 index this를 보고함


//box_comp(i, j) 함수의 호출 허용 횟수는 박스의 개수를 N이라고 했을때 
//최대 b(N) = N + [log2 N] + 1번까지 허용된다 ( [x] - ceiling 올림 ) 


//제출 코드에 한글 주석이 있을 경우 에러 화면을 볼 수 있었습니다
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
	box_ready(); //1. 제일 먼저 호출해야함
	N = box_size(); // 2. 갯수 확인

	vector<int> Index;
	for (int i = 1; i <= N; i++) {
		Index.push_back(i);
	}
	
	int max = compare(Index, result, N);
	bomb = compare(max2, result, max2.size());


	box_report(bomb); //정답 보고. 종료됨
	
	











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