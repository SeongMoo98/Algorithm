#include "timebomb.h"
#include<iostream>
#include<vector>
using namespace std;

vector<int> max2;
int Max;

void find_max2(vector<int> Index, int size) {
	if (size % 2 != 0) {
		size -= 1;
	}
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
	if (Index.size() == 1) {
		Max = Index[0];
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

	int N,result = 0, bomb;
	box_ready(); 
	N = box_size();

	vector<int> Index;
	for (int i = 1; i <= N; i++)
		Index.push_back(i);

	compare(Index, result, N);

	bomb = compare(max2, result, max2.size());

	box_report(bomb);
}