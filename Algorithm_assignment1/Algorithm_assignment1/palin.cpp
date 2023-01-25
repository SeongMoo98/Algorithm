/*
 * 201812145 이성무
 * Algorithm Assignment #1
 * Palindrome
 * 회문(Palindrome) - 앞뒤, 어떤 방향으로 읽어도 같은 문자 순서인 문자열
 * 유사회문 - 만일 주어진 문자열 그 자체로는 회문이 아니지만, 그 안에 특정 한개의 문자만을 제거하여 회문이 되는 문자열
 * ex) 회문 - abba, madam 유사회문 - summu'u's, colaloc'c'
 * 
 * 
 * 제시된 문자열이 회문(0)인지 유사회문(1)인지 아무것도 아닌지(2) 판단 - count로
 * 
 */
#include<iostream>
#include<string>
using namespace std;

int Palindrome(string s, int left, int right, int count)
{
	
	while (left <= right) {
		if (s[left] == s[right]) {
			left++; right--;
		}
		//회문이 안되는데 count == 0 일때 
		else if (count == 0) {
			if (Palindrome(s, left, right - 1, 1) == 1 || Palindrome(s, left + 1, right, 1) == 1) 
				count = 1;
			else 
				count = 2;
			break;
		}
		else {
			count = 2;
			break;
		}
	}
	return count;
}

int main(void)
{

	int N;
	cin >> N;

	string s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		cout << Palindrome(s, 0, s.length() - 1, 0) + 1 << endl;
		s.clear();
	}

	return 0;
}