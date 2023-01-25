#include<iostream>
#include<string>
#include<vector>
#include <unordered_map>
using namespace std;


// ���ڿ��� ���� �������� �ϰ�
// ���� phase�� ���ڿ� ���̸� �Ѿ�� ���� �� ���ڸ� �������� sort 
int k, N=0;
vector<pair<string, int>> input;
int alpha_count[128 + 1] = { 0, };

void result() {
    cout << input[k - 2].second << " " << input[k - 1].second << " " << input[k].second;
}

void init() {
	//cin�� ���๮�ڸ� ���ۿ� �״�� ���ܵα⶧����, ���̾� �ٷ� �����Է��� ������
	//���ۿ� �ִ� ���๮�ڰ� �״�� �ԷµŹ����� ������ �߻�
	//==> �Է¹��۸� ����ִ� cin.ignore() ���
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

int get_ASCII(string str, int d)
{
	if (str.size() <= d)
		return -1;
	else
		return str.at(d);
}

void radix(int lo, int hi, int d)
{

    // recursion break condition
    if (hi <= lo) {
        return;
    }

    int count[128 + 2] = { 0 };

    // temp is created to easily swap strings in str[]
    // int temp[n] can also be used but,
    // it will take more space.
    unordered_map<int, pair<string,int>> temp;

    // Store occurrences of most significant character
    // from each string in count[]
    for (int i = lo; i <= hi; i++) {
        int c = get_ASCII(input[i].first, d);
        count[c + 2]++;
    }

    // Change count[] so that count[] now contains actual
    //  position of this digits in temp[]
    for (int r = 0; r < 128 + 1; r++)
        count[r + 1] += count[r];

    // Build the temp
    int index = 0;
    for (int i = lo; i <= hi; i++) {
        int c = get_ASCII(input[i].first, d);
        temp[count[c + 1]++] = input[i];

    }

    // Copy all strings of temp to str[], so that str[] now
    // contains partially sorted strings
    for (int i = lo; i <= hi; i++) {
        int c = get_ASCII(input[i].first, d);
        input[i] = temp[i - lo];
    }


    // Recursively MSD_sort() on each partially sorted
    // strings set to sort them by their next character
    for (int r = 0; r < 128; r++)
        radix(lo + count[r], lo + count[r + 1] - 1, d + 1);
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	init();
    radix(0, N - 1, 0);
    result();


	return 0;
}