#include <iostream>
#include <string>
using namespace std;

#define MAX 1001
int Table[MAX][MAX];
string String_Table[MAX][MAX];

void Table_Init(int len);
void LCS(string X, string Y, int len);
void LCS_Alpha(string X, string Y, int len);


int main() {
    string s, s_reverse;
    cin >> s;
    int len = s.length();
    for (int i = 0; i < len; i++)
        s_reverse += s[len - (i + 1)];

    Table_Init(len);
    LCS(s, s_reverse, len);
    LCS_Alpha(s, s_reverse, len);

    cout << String_Table[len][len];

    return 0;
}


void Table_Init(int len) {
    for (int i = 0; i <= len; i++) {
        Table[i][0] = 0; Table[0][i] = 0;
        String_Table[i][0] = ""; String_Table[0][i] = "";
    }
}

void LCS(string X, string Y, int len) {
    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            if (X[i - 1] == Y[j - 1])
                Table[i][j] = Table[i - 1][j - 1] + 1;
            else
                Table[i][j] = max(Table[i - 1][j], Table[i][j - 1]);
        }
    }
}

void LCS_Alpha(string X, string Y, int len) {
    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            if (X[i - 1] == Y[j - 1]) {
                Table[i][j] = Table[i - 1][j - 1] + 1;
                String_Table[i][j] = String_Table[i - 1][j - 1] + X[i - 1];
            }
            else {
                if (Table[i - 1][j] > Table[i][j - 1]) {
                    String_Table[i][j] = String_Table[i - 1][j];
                    Table[i][j] = Table[i - 1][j];
                }
                else if (Table[i - 1][j] < Table[i][j - 1]) {
                    String_Table[i][j] = String_Table[i][j - 1];
                    Table[i][j] = Table[i][j - 1];
                }
                else if (Table[i - 1][j] == Table[i][j - 1]) {
                    Table[i][j] = Table[i - 1][j];
                    if (String_Table[i - 1][j] == "") {
                        String_Table[i][j] = String_Table[i][j - 1];
                    }
                    else if (String_Table[i][j - 1] == "") {
                        String_Table[i][j] = String_Table[i - 1][j];
                    }
                    else {
                        String_Table[i][j] = (String_Table[i - 1][j] < String_Table[i][j - 1]) ? String_Table[i - 1][j] : String_Table[i][j - 1];
                    }
                }
            }
        }
    }
}