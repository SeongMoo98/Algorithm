#include<iostream>
using namespace std;

bool compare(int arr[], int input[], int k) {

	for (int i = 1; i <= k; i++) {
		if (arr[i] != input[i])
			return false;
	}
	return true;
}

int* change_range(int* input, int k, int start, int end) {
	int* temp = new int[k + 1];
	copy(input, input + k + 1 , temp);

	for (int i = 0; i < end-start + 1; i++) {
		temp[start + i] = -input[end - i];
	}
	return temp;
}

int* change(int arr[], int input[], int k) {
	int* temp = new int[k + 1];
	for (int i = 1; i <= k; i++) {
		for (int j = i; j <= k; j++) {
			temp = change_range(input, k, i, j);
			if (!compare(arr, temp, k)) {
				continue;
			}
			else
				return temp;
		}
	}
}

void fish_bread(int* arr, int* input, int k) {

	int count = 1;
	int* temp = new int[k + 1];
	while (count <= 2) {
		temp = change(arr, input, k);
		if (compare(arr, temp, k)) {
			break;
		}
		else
			count++;
	}

	if (count == 1) 
		cout << "one\n";
	else if (count == 2)
		cout << "two\n";
	else
		cout << "over\n";
}




int main(void) 
{

	int k;
	cin >> k;

	int* input = new int[k + 1];
	int* arr = new int[k + 1];
	for (int i = 0; i <= k; i++) {
		arr[i] = i;
	}
	input[0] = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= k; j++) {
			int temp;
			cin >> temp;
			input[j] = temp;
		}
		fish_bread(arr, input, k);

	}

	return 0;
}


/*
 * 201812145 이성무
 * Algorithm Assignment #3
 * Fish Bread
 * k개의 붕어빵 틀(frame)이 일렬로 연결
 * 앞 뒤면이 서로 다르게 구별되도록 만들어져 있다
 * 붕어빵 틀은 배열 Fish[k]로 표현
 * 틀의 일부 연속된 구간을 전체 단위로 뒤집을 수 있다
 * 1개만 뒤집을 수도 있다
 * 붕어빵을 뒤집으면 n -> -n 이 된다
 *
 * Example
 * Fish[i:j]를 뒤집으면 j번째 항목이 i번에 오고, i번째 항목이 j번으로 이동한다
 * 즉 수평방향으로 각 내용이 선대칭적(symmetric)으로 이동 = flipping이라고도 한다
 *
 *
 * [1,9,-3,-2,-8,-11,-10,4,5,6,7,12] 인 상태에서
 * flip[2,4] -> flip[6,11] -> flip[4,9]를 수행하면
 * [1,2,3...,11,12]를 만들 수 있고 이 상태에서 붕어빵을 모두 꺼낸다
 *
 * 최소한의 flip[]작업을 이용하여 최초의 상태 1,2,3...k를 만들어야한다
 * 즉, 최종 입력 상태를 읽어서 원상복구에 필요한 최소한의 flip작업의 수를 계산해야한다
 */
#include<iostream>
using namespace std;

int* change(int* arr, int len, int index) {
	//arr[index]의 값을 가진 배열과 바꿔간다 
	int* temp = new int[len + 1];
	copy(arr, arr + index, temp);

	int change_index = abs(arr[index]);
	copy(arr + change_index + 1, arr + len + 1, temp + change_index + 1);

	for (int i = 0; i < change_index - index + 1; i++) {
		temp[index + i] = -arr[change_index - i];
	}

	copy(temp, temp + len + 1, arr);
	delete[]temp;
	return arr;
}

void flip(int* arr, int len) {
	// |배열 값|이 index와 같지 않으면 flip후보군
	// 자기자리에서 음수 ==> 1번 뒤집기 
	int count = 0;
	for (int i = 1; i <= len; i++) {
		int temp = arr[i];
		if (temp < 0) {
			//그 자리에 음수일때
			if (abs(temp) == i) {
				arr[i] = -arr[i];
				count++;
			}
			else {
				arr = change(arr, len, i);
				count++;
			}

		}
		else {
			if (temp != i) {
				arr = change(arr, len, i);
				count++;
			}
		}
	}

	if (count == 1)	cout << "one\n";
	else if (count == 2) cout << "two\n";
	else cout << "over\n";

}


int main(void)
{

	int k;
	cin >> k;

	int* input = new int[k + 1];
	int* arr = new int[k + 1];
	for (int i = 0; i <= k; i++) {
		arr[i] = i;
	}
	input[0] = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= k; j++) {
			int temp;
			cin >> temp;
			input[j] = temp;
		}
		flip(input, k);

	}

	return 0;
}


#include<iostream>
using namespace std;

////처음바꾼 구간 A(3 4 5 6)
//1 2 3 4 5 6 7 8 
////
////1 2 -6 -5 -4 -3 7 8
////1. A구간 안에 쏙 들어가는 경우
////원래와 같아져서 1번만 뒤집는다
//
//양 -> 음 - 1 /2 -6 -5 -4 -3/ 7 8
//==> 1 3 4 5 6 -2 7 8 
//==> A 앞에꺼를 뒤집었다
//
//음 -> 양 - 1 2/ -6 -5 -4 -3 7/8
//==> 1 2 /-7 3 4 5 6 /8
//==> A 뒤에꺼를 뒤집었다
//
//음 -> 양 -> 음 
//==> A 양 옆으로 뒤집었다
//==> A 뒤에 꺼를 뒤집었다
//
//
//그러나 양수는 오름차순 음수는 내림차순이 아니면 같은 덩어리 x
//
//어떤걸 먼저 뒤집었냐??
//양수가 포함된걸 나중에 뒤집었다 왜냐하면 처음 뒤집었을때 음수 이므로
//
//2. A와 일부만 겹치는 형식
//1 /4 5 6 -2 / -3 /7 8 
//or
//4 5 6 -2 -1 /-3/ 7 8 
//or
//1 2/ -6 /-8 -7 3 4 5
//1 2 -6 /-7 3 4 5 /8
//
// 
//3. A와 겹치는 부분이 없을때
//1 /-2 / -6 - 5 - 4 - 3 / 7 8
//뭐를 먼저 뒤집든 상관 x
//음수가 내림차순이 아니거나 양 -> 음 기준으로 덩어리
//
//4. A구간 전체를 포함 
//1/ 3 4 5 6 -2/ 7 8
//or
//1 2 / -8 -7 3 4 5 6 
//
//1 2 3 4 -9 -8 -7 -6 -5 10 11 12
//--> 1 2/ -10 5 6 7 8 9  -4 -3 /11 12 
//or
//--> 1 2 3 4 /-11 -10 5 6 7 8 9/ 12
//여기에 포함이 안되면 over
//



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
	if (flip_once(Fish, k)) {
		cout << "one\n";
		return;
	}
	else {
		//2번 뒤집기
		//A와 일부만 겹치는 형식
		int start = 1, end = k;
		for (int i = 1; i < k; i++) {
			if ((Fish[i] < 0 && Fish[i] - Fish[i + 1]>0) || (Fish[i + 1] != i + 1 && Fish[i + 1] > 0)) {
				start = i + 1;
			}

			if (Fish[i] < 0) {
				if (Fish[i] - Fish[i + 1] > 0) {
					end = i;
					break;
				}
			}
			else {
				if (Fish[i] - Fish[i + 1] < 0) {
					end = i;
					break;
				}
			}
		}
		if (flip_once(flip_range(Fish, k, start, end), k)) {
			cout << "two\n";
			return;
		}
		//A와 겹치는 부분이 없을때
		for (int i = 1; i < k; i++) {
			if (Fish[i] > 0 && Fish[i + 1] < 0) {
				start = i + 1;
			}
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
		for (int i = 1; i < k; i++) {
			if (Fish[i] == i && Fish[i + 1] != i + 1) {
				start = i + 1;
			}
			if (Fish[i] != i && Fish[i + 1] == i + 1) {
				end = i;
				break;
			}
		}

		if (flip_once(flip_range(Fish, k, start, end), k)) {
			cout << "two\n";
			return;
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
















////완전 탐색
////A와 일부만 겹치는 형식
//for (int i = 1; i <= k; i++) {
//	if (Fish[i] == i)
//		continue;
//	for (int j = k; j >= i+1; j--) {
//		if (Fish[j] == j)
//			continue;
//		if (flip_once(flip_range(Fish, k, i, j), k)) {
//			cout << "two\n";
//			return;
//		}
//	}
//}
