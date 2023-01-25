#include<iostream>
#include<string>
#include<stack>
using namespace std;

#define MAX 1001
int Table[MAX][MAX];

void LCS(string X, string Y, int len) {
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			if (Y[i - 1] == X[j - 1])
				Table[i][j] = Table[i - 1][j - 1] + 1;
			else
				Table[i][j] = max(Table[i - 1][j], Table[i][j - 1]);
		}
	}
}

void LCS_Print(string X, string Y, int len) {
	stack<int> s;
	int i = len;
	int j = len;
	while (Table[i][j] != 0) {
		if (Table[i][j] == Table[i][j - 1])
			j--;
		else if (Table[i][j] == Table[i - 1][j])
			i--;
		else if (Table[i][j] == Table[i - 1][j - 1] + 1) {
			i--; j--;
		}
	}
}

int main(void) {

	string s;
	cin >> s;
	string temp;
	int len = s.length();
	for (int i = 0; i < len; i++)
		temp += s[len - (i + 1)];

	int** Table = new int* [len + 1];
	for (int i = 0; i < len + 1; i++) {
		Table[i] = new int[len + 1];
		Table[0][i] = 0;
		Table[i][0] = 0;
	}

	LCS(s, temp, len);
	LCS_Print(s, temp, len);

	int LCS_Length = Table[len][len];

	//LCS_Length가 같은것들만 LCS_Print해서 alpha가 제일 작은것

	return 0;
}