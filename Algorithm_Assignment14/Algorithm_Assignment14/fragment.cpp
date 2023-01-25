#include<iostream>
#include<string>
#include<vector>
#include <unordered_map>
using namespace std;

int k, N = 0;
vector<pair<string, int>> input;

void result() {
    cout << input[k - 2].second << "\n" << input[k - 1].second << "\n" << input[k].second;
}

void init() {
    //cin은 개행문자를 버퍼에 그대로 남겨두기때문에, 연이어 바로 다음입력을 받을때
    //버퍼에 있던 개행문자가 그대로 입력돼버려서 문제가 발생
    //==> 입력버퍼를 비워주는 cin.ignore() 사용
    cin >> k; cin.ignore();
    string gen; int index = 0;
    do {
        getline(cin, gen, '\n');
        if (gen == "") break;
        N++;
        pair<string, int> temp(gen, ++index);
        input.push_back(temp);
    } while (1);
}

int get_ASCII(string str, int index)
{
    if (str.size() <= index) return -1;
    else return str.at(index);
}

void radix(int start, int end, int index)
{

    if (start >= end) return;

    int alpha_count[128 + 2] = { 0 };

    unordered_map<int, pair<string, int>> temp;

    for (int i = start; i <= end; i++) {
        int c = get_ASCII(input[i].first, index);
        alpha_count[c + 2]++;
    }

    for (int i = 0; i < 128 + 1; i++)
        alpha_count[i + 1] += alpha_count[i];


    for (int i = start; i <= end; i++) {
        int c = get_ASCII(input[i].first, index);
        temp[alpha_count[c + 1]++] = input[i];

    }

    for (int i = start; i <= end; i++) {
        int c = get_ASCII(input[i].first, index);
        input[i] = temp[i - start];
    }

    for (int i = 0; i < 128; i++) {
        if (start + alpha_count[i] >= start + alpha_count[i + 1] - 1) continue;
        radix(start + alpha_count[i], start + alpha_count[i + 1] - 1, index + 1);
    }
  
}

int main(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    init();
    radix(0, N - 1, 0);
    result();


    return 0;
}