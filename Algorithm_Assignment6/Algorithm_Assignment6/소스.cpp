#include<iostream>
#include<string>
#include<vector>
using namespace std;


//발송된 문자열에서 숨어있는 암호는 해당 문자열의 부순서(Subsequence)중에서 
//가장 긴 회문 순서로 구성되는 문자열
//부순서(Subsequence)
//어떤 서열 si의 부순서란 이 서열의 부분집합 중에서 si의 index가 증가되는 순서로 추출된 순서
//ex) S = "mygamebox"
//부순서 : mabx, mybox, gebo, yamex, gamebox ...
//만약 S의 길이가 l이라 한다면 가능한 부순서 문자열의 개수는 2^l - 1 까지 가능하다


//진짜 암호 - 부순서 문자열 중에서 가장 긴 길이의 회문
//깉은 길이라면 사전식 순서로 볼 때 가장 "빠른" 것이 유일한 정답

//문자열 s[i:j]의 답을 알고 있다고 가정하여 S[0 : L-1]의 답을 찾는다

#define MAX 1001
int Table[MAX][MAX];

void LCS(string X, string Y, int len) {
	//0은 base condition
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			if (Y[i - 1] == X[j - 1])
				Table[i][j] = Table[i - 1][j - 1] + 1;
			else
				Table[i][j] = max(Table[i - 1][j], Table[i][j - 1]);
		}
	}
}

vector<int> LCS_Index(string X, string Y, int len, vector<int> v) {
	v.clear();
	v = { 0, };
	int i = len;
	int j = len;
	while (Table[i][j] != 0) {
		if (Table[i][j] == Table[i][j - 1])
			j--;
		else if (Table[i][j] == Table[i - 1][j])
			i--;
		else if (Table[i][j] == Table[i - 1][j - 1] + 1) {
			v.push_back(j - 1);
			i--; j--;
		}
	}
	return v;
}

//abcdefgh_jkflmn
int main(void) {

	vector<int> temp_s = { 0, }, sIndex = { 0, };
	string s, s_reverse;
	cin >> s;
	int len = s.length();
	for (int i = 0; i < len; i++)
		s_reverse += s[len - (i + 1)];
	LCS(s, s_reverse, len);
	if (Table[len][len] == 1) {
		int min = s[0];
		for (int i = 0; i < len; i++) {
			if (s[i] < min)
				min = s[i];
		}
		cout << (char)min;
		return 0;
	}
	temp_s = LCS_Index(s, s_reverse, len, temp_s);
	//LCS_Index에서 역순으로 push_back하므로 reverse
	for (int i = temp_s.size() - 1; i > 0; i--)
		sIndex.push_back(temp_s[i]);
	
	int LCS_length = Table[len][len];
	int half_length;

	if (LCS_length % 2 == 0) half_length = LCS_length / 2;
	else half_length = LCS_length / 2 + 2;

	vector<int> tempro = { 0, };
	for (int i = 1; i <= half_length; i++) {
		tempro.clear();
		tempro = { 0, };
		for (int j = sIndex[i] + 1; j < sIndex[i+1]; j++) {
			if (s[sIndex[i]] > s[j]) {
				tempro.push_back(j);
			}
		}
		if (tempro.size() == 1)
			continue;
		vector<int> abc = { 0, };
		abc = tempro;
		string temp1 = s, temp2 = "";
		temp1[sIndex[i]] = '0';
		for (int k = 0; k < len; k++)
			temp2 += temp1[len - (k + 1)];
		LCS(temp1, temp2, len);
		abc = LCS_Index(temp1, temp2, len, abc);
		
		if (Table[len][len] != LCS_length)
			continue;
		else {
			s.erase(s.begin() + sIndex[i], s.begin() + sIndex[i] + 1);
			
			if (sIndex[i] == 1) {
				for (int l = 3; l < sIndex.size(); l++)
					sIndex[l] -= 1;
			}
			else {
				for (int l = 1; l < sIndex.size(); l++)
					sIndex[l] -= 1;
			}
			

				
			len--;
			continue;
		}
	}

	len = s.size();
	s_reverse = "";
	for (int i = 0; i < len; i++)
		s_reverse += s[len - (i + 1)];
	LCS(s, s_reverse, s.size());
	sIndex = LCS_Index(s, s_reverse, len, sIndex);
	for (int i = 1; i < sIndex.size(); i++) {
		cout << s[sIndex[i]];
	}


	return 0;
}