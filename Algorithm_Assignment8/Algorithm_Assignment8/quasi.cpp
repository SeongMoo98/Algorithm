#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main(void) {
    string S, T;
    cin >> S >> T;
    S += "  "; T += "  ";
    int slen = S.length() - 2; int tlen = T.length() - 2;
    int** table = new int* [tlen + 3];
    string** strings = new string * [tlen + 3];
    for (int i = 0; i <= tlen + 2; i++) {
        table[i] = new int[slen + 3];
        strings[i] = new string[slen + 3];
    }

    for (int i = 0; i <= tlen; i++) {
        for (int j = 0; j <= slen; j++) {
            table[i][j] = 0;
            strings[i][j] = "";
        }
    }

    int Max = 0;
    for (int i = 1; i <= tlen; i++) {
        for (int j = 1; j <= slen; j++) {
            if (S[j - 1] == T[i - 1]) {
                if (table[i][j] == 0) {
                    table[i][j] = table[i - 1][j - 1] + 1;
                    strings[i][j] = strings[i - 1][j - 1] + S[j - 1];
                }
                if (S[j] == T[i]) {
                    table[i + 1][j + 1] = table[i][j] + 1;
                    strings[i + 1][j + 1] = strings[i][j] + S[j];
                }

                if (S[j + 1] == T[i + 1]) {
                    table[i + 2][j + 2] = table[i][j] + 1;
                    strings[i + 2][j + 2] = strings[i][j] + S[j + 1];
                }

                if (S[j] == T[i + 1]) {
                    table[i + 2][j + 1] = table[i][j] + 1;
                    strings[i + 2][j + 1] = strings[i][j] + S[j];
                }

                if (S[j + 1] == T[i]) {
                    table[i + 1][j + 2] = table[i][j] + 1;
                    strings[i + 1][j + 2] = strings[i][j] + S[j + 1];
                }


                if (table[i][j] >= Max) {
                    Max = table[i][j];
                }
            }
            else {
                strings[i][j] = "";
                table[i][j] = 0;
            }
        }
    }

    vector<string> quasi_substr_vector;

    for (int i = 1; i <= tlen; i++) {
        for (int j = 1; j <= slen; j++) {
            if (table[i][j] == Max)
                quasi_substr_vector.push_back(strings[i][j]);
        }
    }

    sort(quasi_substr_vector.begin(), quasi_substr_vector.end());

    cout << quasi_substr_vector[0];

}

