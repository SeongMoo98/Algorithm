#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
};
vector<Point> points;
vector<int> answer;

void init() {
	cin >> N;
;	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		points.push_back(Point(x,y));
	}
	points.push_back(points[0]);
	points.push_back(points[1]);
}

int signed_area(Point P, Point Q, Point R) {
	return (Q.x * P.y + R.x * Q.y + P.x * R.y) - (P.x * Q.y + Q.x * R.y + R.x * P.y);
}
void check_marina(int i) {
	Point P = points[i];
	Point Q = points[i+1];
	Point R = points[i+2];
	int area = signed_area(P,Q,R);

	if (area > 0) {
		if (i+1 == N) {
			answer.insert(answer.begin(), 1);
			return;
		}
		answer.push_back((i + 1) + 1);

	}
		
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cout.tie(NULL); cin.tie(NULL);

	init();
	for (int i = 0; i < N; i++)
		check_marina(i);

	if (answer.size() == 0)
		cout << "0";

	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i] << "\n";
	}
	return 0;
}