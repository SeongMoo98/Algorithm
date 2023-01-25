#include<iostream>
using namespace std;

bool compare(int temp[], int k) {

	for (int i = 1; i <= k; i++) {
		if (temp[i] != i)
			return false;
	}
	return true;
}

int* flip_range(int Fish[], int k, int start, int end) {
	int* temp = new int[k + 1];
	copy(Fish, Fish + k + 1, temp);

	for (int i = 0; i < end - start + 1; i++) {
		temp[start + i] = -Fish[end - i];
	}
	return temp;
}
bool flip_once(int Fish[], int k) {
	int start = 1, end = k;
	for (int i = 1; i < k; i++) {
		if (Fish[i] > 0 && Fish[i + 1] < 0)
			start = i + 1;
		if (Fish[i] < 0 && Fish[i + 1] > 0)
			end = i;
	}
	int* temp = flip_range(Fish, k, start, end);
	if (compare(temp, k))
		return true;
	return false;
}

void Fish_Bread(int Fish[], int k) {
	//1번 뒤집기
	if (flip_once(Fish,k)) {
		cout << "one\n";
		return;
	}
	else {
		
		//2번 뒤집기
		//A 구간안에 쏙 들어가는 경우
		int start = 1, end = k;
		for (int i = 1; i < k; i++) {
			if (Fish[i-1] ==i-1 && Fish[i]==i )
				start = i + 1;
			if (Fish[i] !=i && Fish[i+1]==i+1) {
				end = i;
				break;
			}	
		}
		if (Fish[1] != 1) start = 1;
		if (Fish[k] != k) end = k;
		if (flip_once(flip_range(Fish, k, start, end), k)) {
			cout << "two\n";
			return;
		}

		//A와 겹치는 부분이 없을때
		start = 1, end = k;
		for (int i = 1; i < k; i++) {
			if (start == 1 && Fish[i] > 0 && Fish[i + 1] < 0)
				start = i + 1;
			if ((Fish[i] < 0 && Fish[i + 1] > 0) || (Fish[i] < 0 && Fish[i] > Fish[i + 1])) {
				end = i;
				break;
			}
		}
		if (flip_once(flip_range(Fish, k, start, end), k)) {
			cout << "two\n";
			return;
		}

		//A구간 전체를 포함 
		start = 1, end = k;
		for (int i = 1; i < k; i++) {
			if (start == 1 && Fish[i] == i && Fish[i + 1] != i + 1)
				start = i + 1;
			if (Fish[i] != i && Fish[i + 1] == i + 1 && (abs(Fish[i])-abs(Fish[i+1]) != 1) ) {
				end = i;
				break;
			}
		}
		if (flip_once(flip_range(Fish, k, start, end), k)) {
			cout << "two\n";
			return;
		}

		//A와 일부만 겹치는 형식
		start = 1; end = k;
		for (int i = 1; i <= k; i++) {
			if (Fish[i]<0 && Fish[i]>Fish[i + 1]) {
				start = i + 1;
				end = -Fish[i + 1];

				if (i > k/2) {
					start = -Fish[i];
					end = i;
				}
				
				if (flip_once(flip_range(Fish, k, start, end), k)) {
					cout << "two\n";
					return;
				}
			}
		}
		cout << "over\n";
	}
}

int main(void)
{
	
	int k;
	cin >> k;

	int* Fish = new int[k + 1];
	int* arr = new int[k + 1];
	for (int i = 0; i <= k; i++) {
		arr[i] = i;
	}
	Fish[0] = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= k; j++) {
			int temp;
			cin >> temp;
			Fish[j] = temp;
		}
		Fish_Bread(Fish, k);
	}

	return 0;
}
