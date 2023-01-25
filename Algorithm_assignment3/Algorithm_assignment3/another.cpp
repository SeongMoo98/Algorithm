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
 * 201812145 �̼���
 * Algorithm Assignment #3
 * Fish Bread
 * k���� �ؾ Ʋ(frame)�� �Ϸķ� ����
 * �� �ڸ��� ���� �ٸ��� �����ǵ��� ������� �ִ�
 * �ؾ Ʋ�� �迭 Fish[k]�� ǥ��
 * Ʋ�� �Ϻ� ���ӵ� ������ ��ü ������ ������ �� �ִ�
 * 1���� ������ ���� �ִ�
 * �ؾ�� �������� n -> -n �� �ȴ�
 *
 * Example
 * Fish[i:j]�� �������� j��° �׸��� i���� ����, i��° �׸��� j������ �̵��Ѵ�
 * �� ����������� �� ������ ����Ī��(symmetric)���� �̵� = flipping�̶�� �Ѵ�
 *
 *
 * [1,9,-3,-2,-8,-11,-10,4,5,6,7,12] �� ���¿���
 * flip[2,4] -> flip[6,11] -> flip[4,9]�� �����ϸ�
 * [1,2,3...,11,12]�� ���� �� �ְ� �� ���¿��� �ؾ�� ��� ������
 *
 * �ּ����� flip[]�۾��� �̿��Ͽ� ������ ���� 1,2,3...k�� �������Ѵ�
 * ��, ���� �Է� ���¸� �о ���󺹱��� �ʿ��� �ּ����� flip�۾��� ���� ����ؾ��Ѵ�
 */
#include<iostream>
using namespace std;

int* change(int* arr, int len, int index) {
	//arr[index]�� ���� ���� �迭�� �ٲ㰣�� 
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
	// |�迭 ��|�� index�� ���� ������ flip�ĺ���
	// �ڱ��ڸ����� ���� ==> 1�� ������ 
	int count = 0;
	for (int i = 1; i <= len; i++) {
		int temp = arr[i];
		if (temp < 0) {
			//�� �ڸ��� �����϶�
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

////ó���ٲ� ���� A(3 4 5 6)
//1 2 3 4 5 6 7 8 
////
////1 2 -6 -5 -4 -3 7 8
////1. A���� �ȿ� �� ���� ���
////������ �������� 1���� �����´�
//
//�� -> �� - 1 /2 -6 -5 -4 -3/ 7 8
//==> 1 3 4 5 6 -2 7 8 
//==> A �տ����� ��������
//
//�� -> �� - 1 2/ -6 -5 -4 -3 7/8
//==> 1 2 /-7 3 4 5 6 /8
//==> A �ڿ����� ��������
//
//�� -> �� -> �� 
//==> A �� ������ ��������
//==> A �ڿ� ���� ��������
//
//
//�׷��� ����� �������� ������ ���������� �ƴϸ� ���� ��� x
//
//��� ���� ��������??
//����� ���ԵȰ� ���߿� �������� �ֳ��ϸ� ó�� ���������� ���� �̹Ƿ�
//
//2. A�� �Ϻθ� ��ġ�� ����
//1 /4 5 6 -2 / -3 /7 8 
//or
//4 5 6 -2 -1 /-3/ 7 8 
//or
//1 2/ -6 /-8 -7 3 4 5
//1 2 -6 /-7 3 4 5 /8
//
// 
//3. A�� ��ġ�� �κ��� ������
//1 /-2 / -6 - 5 - 4 - 3 / 7 8
//���� ���� ������ ��� x
//������ ���������� �ƴϰų� �� -> �� �������� ���
//
//4. A���� ��ü�� ���� 
//1/ 3 4 5 6 -2/ 7 8
//or
//1 2 / -8 -7 3 4 5 6 
//
//1 2 3 4 -9 -8 -7 -6 -5 10 11 12
//--> 1 2/ -10 5 6 7 8 9  -4 -3 /11 12 
//or
//--> 1 2 3 4 /-11 -10 5 6 7 8 9/ 12
//���⿡ ������ �ȵǸ� over
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


	//1�� ������
	if (flip_once(Fish, k)) {
		cout << "one\n";
		return;
	}
	else {
		//2�� ������
		//A�� �Ϻθ� ��ġ�� ����
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
		//A�� ��ġ�� �κ��� ������
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

		//A���� ��ü�� ���� 
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
















////���� Ž��
////A�� �Ϻθ� ��ġ�� ����
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
