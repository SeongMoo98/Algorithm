#include<iostream>
#include<string>
using namespace std;

/**
 * LCS(The Longest Common Subsequence
 * 
 * Subsequence
 * X = <x1, x2, x3 ... xm>
 * Z = <z1, z2, z3 ... zn>
 * Z가 X의 subsequence라 할때
 * <i1, i2, ... ik>라는 X의 index와 j = 1, 2, ... k(=n)에 대해
 * Xiq = Zj를 만족한다
 * 
 * Example)
 * X = <A, B, C, D, F, M, Q>
 * Z = <B, F, M>
 * X index : < i1 = 2, i2 = 4, i3 = 5>,  j = 1,2,3
 *
 * 
 * Common Subsequence
 * 만약 Z가 X의 subsequence이면서, Y의 subsequence이면
 * Z는 X, Y의 Common Subsequence이다
 * 
 * Longest Common Subsequence
 * Subsequence중 길이가 가장 긴 Subsequence
 * 
 * 
 * Naice Approach for LCS
 * X의 모든 Subsequence 에 대해 Y의 Subsequence인지 아닌지 check 
 * 
 * DP for LCS
 * 1. Charcterize the structure of an optimal solution: show that the problem has the optimal substructure 
 * 2. Recursively define the value of an optimal solution: Make recurrence of the optimal solution
 * 3. Compute the value of an optimal solution, typically in a botton-up fashion
 * 4. Construct an optimal solution from computed information
 */


//LCS출력
//https://zoosso.tistory.com/187


int DP[1002][1002];

//int LCS(string X, string Y, int m, int n) {
//	if (m == 0 || n == 0)
//		return 0;
//	else if (X[n] == Y[m])
//		return LCS(X, Y, m - 1, n - 1) + 1;
//	else
//		return max(LCS(X, Y, m - 1, n), LCS(X, Y, m, n - 1));
//}

void lcs(string X, string Y, int m, int n) {
	for (int i = 1; i <= n; i++) {
		for(int j=1; j<=m; j++){
			if (Y[i - 1] == X[j - 1])
				DP[i][j] = DP[i - 1][j - 1] + 1;
			else
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
		}
		
	}
}
int main(void) {
	string s1, s2;
	int len1, len2;
	cin >> s1 >> s2;
	len1 = s1.length(); len2 = s2.length();

	//cout << LCS(s1, s2, len1, len2) << endl;
	lcs(s1, s2, len1, len2);
	cout << DP[len2][len1] << endl;

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++)
			cout << DP[i][j];
		cout << "\n";
	}
	





	return 0;
}