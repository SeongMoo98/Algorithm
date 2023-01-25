#include<iostream>
#include<string>
#include<vector>
using namespace std;


//�߼۵� ���ڿ����� �����ִ� ��ȣ�� �ش� ���ڿ��� �μ���(Subsequence)�߿��� 
//���� �� ȸ�� ������ �����Ǵ� ���ڿ�
//�μ���(Subsequence)
//� ���� si�� �μ����� �� ������ �κ����� �߿��� si�� index�� �����Ǵ� ������ ����� ����
//ex) S = "mygamebox"
//�μ��� : mabx, mybox, gebo, yamex, gamebox ...
//���� S�� ���̰� l�̶� �Ѵٸ� ������ �μ��� ���ڿ��� ������ 2^l - 1 ���� �����ϴ�


//��¥ ��ȣ - �μ��� ���ڿ� �߿��� ���� �� ������ ȸ��
//���� ���̶�� ������ ������ �� �� ���� "����" ���� ������ ����

//���ڿ� s[i:j]�� ���� �˰� �ִٰ� �����Ͽ� S[0 : L-1]�� ���� ã�´�

#define MAX 1001
int Table[MAX][MAX];

void LCS(string X, string Y, int len) {
	//0�� base condition
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
	//LCS_Index���� �������� push_back�ϹǷ� reverse
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