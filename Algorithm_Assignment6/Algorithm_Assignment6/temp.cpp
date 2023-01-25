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
			//temp_v[0]+1��  temp_v[1]���̿� ��� ���ڿ� ���� �켱������ �������Ѵ�
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