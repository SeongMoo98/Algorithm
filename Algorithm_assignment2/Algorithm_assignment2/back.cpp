/*
 * 201812145 이성무
 * Algorithm Assignment #2
 * Backspace
 * 
 * k개의 영문 소문자로만 구성된 문자열 s
 * 특정문자를 backspace로 바꾸면 문자열 t를 얻는다(단, 첫 문자를 backspace로 바꾸면 변화가 없다고 가정)
 *
 * backspce = '\'라 가정한다
 * ex) "abcbd" - 1,4번째 ==> "\bc\d ==> "bd
 * 
 * 주어진 문자열 s에서 backspace를 섞어 문자열 t를 만들 수 있는지 계산
 * Example 
 * "abcaa"에서 "a", "aa"를 얻을 수 있는가 - YES
 * "abcbd"에서 "bb"를 얻을 수 있는가 - NO
 */

#include<iostream>
#include<string>
#include<vector>

using namespace std;


bool check(vector<char> v, string t) {

	string temp;
	for (int i = 0; i < v.size(); i++)
		temp.push_back(v[i]);

	if (temp == t)
		return true;
	return false;

}

void backspace(string s, string t) {
	//길이 차이가 홀수 - 맨앞 지움, 짝수면 안지움
	int sub = s.length() - t.length();
	if (sub < 0) {
		cout << "NO\n";
		return;
	}

	if (sub > 0 && sub % 2 != 0)
		s[0] = '\b';

	int j = 0;
	//stack에 push된 문자열 개수를 확인할 vector
	for (int i = 0; i < s.length() - 1; i++) {
		if (s[i] == '\b') continue;

		if (s[i] == t[j])
			j++;
		else
			s[i + 1] = '\b';
	}

	vector<char> v;
	for (int i = 0; i < s.length(); i++) {
		//위에서 바꾼 s[i] == '\b' 일때 v.pop_back()을 하면 backspace한 것과 같다
		if (s[i] == '\b') {
			if (!v.empty())
				v.pop_back();
		}
		else
			v.push_back(s[i]);
	}

	if (check(v, t))
		cout << "YES\n";
	else
		cout << "NO\n";
}



int main(void)
{

	int N;
	cin >> N;
	string s, t;

	for (int i = 0; i < N; i++) {

		cin >> s >> t;
		backspace(s, t);
	}


	return 0;
}
