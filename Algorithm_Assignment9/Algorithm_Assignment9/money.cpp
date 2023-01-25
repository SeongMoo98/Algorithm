#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

#define MAX 31
int Table[MAX][MAX];

int findOp(vector<string> op, int index) {
    string c = op[((index)+(index + 1)) / 2];
    if (c == "+")
        return 1;
    if (c =="-")
        return 2;
    return 3;
}
vector<string> split(string s, string del) {
    vector<string> v;
    char* c = strtok((char*)s.c_str(), del.c_str());
    while (c) {
        v.push_back(c);
        c = strtok(NULL, del.c_str());
    }
    return v;
}
int main(void) {
    string str;
    getline(cin, str);
    vector<int> number; vector<string> op;
    vector<string> div = split(str, " ");

    for (int i = 0; i < div.size(); i++) {
        if (i % 2 != 0)
            op.push_back(div[i]);
        else
            number.push_back(atoi(div[i].c_str()));
    }

    int len = number.size();
    for (int i = 0; i < len; i++) {
        Table[i][i] = number[i];
    }

    int i = 0;
    int j = 1;
    int j_count = 1;
    while (j <= len) {
        if (j == len) {
            i = 0; j = ++j_count;
            if (j_count == 5)
                break;
        }
        if (i == j)
            continue;
        vector<int> result;
        for (int k = i; k < j; k++) {
            //"+"여기가 Operation이 들어가야함

            int op_num = findOp(op, k);
            if (op_num == 1)
                result.push_back(Table[i][k] + Table[k + 1][j]);
            else if (op_num == 2)
                result.push_back(Table[i][k] - Table[k + 1][j]);
            else if (op_num == 3)
                result.push_back(Table[i][k] * Table[k + 1][j]);
        }

        int max = 0x80000000;
        for (int value : result) {
            if (value >= max) {
                max = value;
            }
        }
        Table[i++][j++] = max;
    }
    cout<<Table[0][len - 1];



}