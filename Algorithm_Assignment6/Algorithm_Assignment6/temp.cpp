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
			if (Y[i - 1] == X[j - 1] )
				Table[i][j] = Table[i - 1][j - 1] + 1;
			else
				Table[i][j] = max(Table[i - 1][j], Table[i][j - 1]);
		}
	}
}

vector<int> LCS_Index(string X, string Y, int len, vector<int> v) {
	v.clear();
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


int main(void) {

	vector<int> sIndex;
	string s;
	cin >> s;
	string temp = s;
	reverse(temp.begin(), temp.end());
	int len = s.length();

	LCS(s, temp, len);
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= len; j++) {
			cout << Table[i][j] << " ";

		}
		cout << "\n";
	}
	sIndex = LCS_Index(s, temp, len, sIndex);
	reverse(sIndex.begin(), sIndex.end());
	vector<int> temp_v = sIndex;
	
	int LCS_length = Table[len][len];
	string temp1 = s,temp2;
	if (sIndex.size() == 1) {
		cout << s[sIndex[0]];
	}
	else {

		while (1) {
			if (Table[len][len] != LCS_length) {
				break;
			}
			//temp_v[0]+1과  temp_v[1]사이에 모든 문자에 대해 우선순위를 따져야한다
			for (int i = temp_v[0]+1; i <= temp_v[1]; i++) {
				if (Table[len][len] != LCS_length) {
					break;
				}
				if (s[temp_v[0]] > s[i]) {
					temp1[temp_v[0]] = '0';
					temp2 = temp1;
					reverse(temp2.begin(), temp2.end());
					LCS(temp1, temp2, len);
					temp_v = LCS_Index(temp1, temp2, len, temp_v);
				}
			}
			
		}

	}
	
	for (int i = 0; i < sIndex.size(); i++) {
		cout << s[sIndex[i]];
	}
	cout << "\n\n";
	for (int i = 0; i < temp_v.size(); i++) {
		cout << s[temp_v[i]];
	}


	




	return 0;
}