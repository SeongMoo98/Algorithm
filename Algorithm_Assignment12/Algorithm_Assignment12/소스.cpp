#include <iostream>
#include <queue>
using namespace std;

struct compare {  // private compare function
    bool operator()(const int& l, const int& r) {
        return l % 100 > r % 100;  // 끝 2자리 숫자만 비교 대상
    }
};

// (56,45)

int main() {
    int ndata[10] = { 566, 634, 812, 534, 770, 952, 784, 812, 564, 98 };
    priority_queue<int, deque<int>, compare > pq(ndata, ndata + 9);

    pq.push(313); pq.push(25);
    pq.push(59); pq.push(108);

    cout << "하나씩 뽑아 내어 봅시다.\n";
    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
    //cin.get();
}
