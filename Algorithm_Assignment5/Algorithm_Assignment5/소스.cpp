#include<iostream>
#include<math.h>
using namespace std;
float t1 = 0.50f; float t2 = 0.50f; float epsilon = 0.01;
float A[3]; float B[3]; float P[3]; float C[3]; float D[3]; float Q[3];


double len(float Point_1[3], float Point_2[3]) {
	return pow(Point_2[0] - Point_1[0], 2) + pow(Point_2[1] - Point_1[1], 2) + pow(Point_2[2] - Point_1[2], 2);
}

void set_vector(float Point_1[3], float Point_2[3], float t, float X[3]) {
	for (int i = 0; i < 3; i++)
		X[i] = (1 - t) * Point_1[i] + t * Point_2[i];
}

void AB_compare(float Point_1[3], float Point_2[3]) {
	float Moving_Point[3];
	float case_t, case_t_minus_epsilon, case_t_plus_epsilon;
	set_vector(A, B, t1, Moving_Point);	case_t = len(Moving_Point, Q);
	set_vector(A, B, t1 + epsilon, Moving_Point);	case_t_plus_epsilon = len(Moving_Point, Q);
	set_vector(A, B, t1 - epsilon, Moving_Point);	case_t_minus_epsilon = len(Moving_Point, Q);

	if ((case_t_plus_epsilon > case_t) && (case_t_minus_epsilon < case_t)) {
		t1 -= epsilon;	set_vector(A, B, t1, Point_1);
		AB_compare(Point_1, Point_2);
	}
	else if ((case_t_plus_epsilon < case_t) && (case_t_minus_epsilon > case_t)) {
		t1 += epsilon;	set_vector(A, B, t1, Point_1);
		AB_compare(Point_1, Point_2);
	}
	else
		return;
}

void CD_compare(float Point_1[3], float Point_2[3]) {
	float Moving_Point[3];
	float case_t, case_t_minus_epsilon, case_t_plus_epsilon;
	set_vector(C, D, t2, Moving_Point);	 case_t = len(Moving_Point, P);
	set_vector(C, D, t2 + epsilon, Moving_Point);	case_t_plus_epsilon = len(Moving_Point, P);
	set_vector(C, D, t2 - epsilon, Moving_Point);	case_t_minus_epsilon = len(Moving_Point, P);

	if ((case_t_plus_epsilon > case_t) && (case_t_minus_epsilon < case_t)) {
		t2 -= epsilon;	set_vector(C, D, t2, Point_2);
		CD_compare(Point_1, Point_2);
	}
	else if ((case_t_plus_epsilon < case_t) && (case_t_minus_epsilon > case_t)) {
		t2 += epsilon;	set_vector(C, D, t2, Point_2);
		CD_compare(Point_1, Point_2);
	}
	else
		return;
}

int main(void) {
	cin >> A[0] >> A[1] >> A[2];	cin >> B[0] >> B[1] >> B[2];	cin >> C[0] >> C[1] >> C[2]; 	cin >> D[0] >> D[1] >> D[2];
	set_vector(A, B, 0.50, P); set_vector(C, D, 0.50, Q);

	float AB_After = 0, CD_After = 0;
	while (true) {
		AB_compare(P, Q);
		if (t1 >= 0.50) {
			t1 = 0.50f;
			copy(P, P + 3, A);
		}
		else {
			t1 = 0.5f;
			copy(P, P + 3, B);
		}
		AB_After = len(P, Q);
		if (abs(AB_After - CD_After) <= 20) {
			break;
		}
		CD_compare(P, Q);
		if (t2 >= 0.50) {
			t2 = 0.50f;
			copy(Q, Q + 3, C);
		}
		else {
			t2 = 0.5f;
			copy(Q, Q + 3, D);
		}
		CD_After = len(P, Q);
		if (abs(AB_After - CD_After) <= 20) {
			break;
		}

	}
	if (sqrt(AB_After) <= 0.005)
		cout << "0";
	else
		cout << ceil(sqrt(AB_After));
	return 0;
}

//#include<iostream>
//#include<math.h>
//using namespace std;
//
////우주정거장(튜브모양) S1 = (A, B) S2 = (C, D)
////S1은 3차원 공간의 두 점 A, B를 튜브로 연결 S2는 C, D를 연결
////이 두 튜브 모양의 우주 정거장을 연결하는 연결통로 T를 건설하려고 한다
////둘은 연결하는 가장 짧은 길이의 연결통로를 찾아야 한다
////즉, T는 S1과 S2를 연결하는 최소 "정수" 길이의 선분
//
//
////입출력
////입력 : 두 우주정거장 S1, S2의 양 끝점 A, B, C, D의 각 3차원 좌표 (x, y, z)가 3개의 정수로 주어진다
////출력 : 정수단위로 출력 (올림)
//
////P,Q 는 S1, S2 위의 점
//float t1 = 0.50f; float t2 = 0.50f; float epsilon = 0.01;
//float A[3]; float B[3]; float P[3]; float C[3]; float D[3]; float Q[3];
//
////거리를 최소정수단위로 return
////sqrt는 무거운 계산이므로 마지막에 한번만 쓴다
//double len(float Point_1[3], float Point_2[3]) {
//	return pow(Point_1[0] - Point_2[0], 2) + pow(Point_1[1] - Point_2[1], 2) + pow(Point_1[2] - Point_2[2], 2);
//}
//
//void set_vector(float Point_1[3], float Point_2[3], float t, float X[3]) {
//	for (int i = 0; i < 3; i++)
//		X[i] = (1 - t) * Point_1[i] + t * Point_2[i];
//}
////한바퀴 돌면 CD위의 점 Point_2는 고정된 상태에서 Point_1의 좌표가 최소 거리의 점으로 바뀐다
//void AB_compare(float Point_1[3], float Point_2[3]) {
//	float Moving_Point[3];
//	float case_t, case_t_minus_epsilon, case_t_plus_epsilon;
//	set_vector(A, B, t1, Moving_Point);	case_t = len(Moving_Point, Q);
//	set_vector(A, B, t1 - epsilon, Moving_Point);	case_t_minus_epsilon = len(Moving_Point, Q);
//	set_vector(A, B, t1 + epsilon, Moving_Point);	case_t_plus_epsilon = len(Moving_Point, Q);
//
//	if ((case_t_plus_epsilon > case_t) && (case_t_minus_epsilon < case_t)) {
//		t1 -= epsilon;	set_vector(A, B, t1, Point_1);
//		AB_compare(Point_1, Point_2);
//	}
//	else if ((case_t_plus_epsilon < case_t) && (case_t_minus_epsilon > case_t)) {
//		t1 += epsilon;	set_vector(A, B, t1, Point_1);
//		AB_compare(Point_1, Point_2);
//	}
//	else
//		return;
//}
//
//void CD_compare(float Point_1[3], float Point_2[3]) {
//	float Moving_Point[3];
//	float case_t, case_t_minus_epsilon, case_t_plus_epsilon;
//	set_vector(C, D, t2, Moving_Point);	 case_t = len(P, Moving_Point);
//	set_vector(C, D, t2 - epsilon, Moving_Point);	case_t_minus_epsilon = len(P, Moving_Point);
//	set_vector(C, D, t2 + epsilon, Moving_Point);	case_t_plus_epsilon = len(P, Moving_Point);
//
//	if ((case_t_plus_epsilon > case_t) && (case_t_minus_epsilon < case_t)) {
//		t2 -= epsilon;	set_vector(C, D, t2, Point_2);
//		CD_compare(Point_1, Point_2);
//	}
//	else if ((case_t_plus_epsilon < case_t) && (case_t_minus_epsilon > case_t)) {
//		t2 += epsilon;	set_vector(C, D, t2, Point_2);
//		CD_compare(Point_1, Point_2);
//	}
//	else
//		return;
//}
//
//// 1) P(A-B), Q(C-D) 중점끼리 거리측정
//// 2) CD위의 점 고정, P의 중점을 움직여 본다
//// 3) P의 점에서 좌우 어디로 가도 손해라면(거리 증가) ==> 그 점 고정
//// 4) 그 점에서부터 중점을 잡고 길이가 -되는 방향으로 간다
//int main(void) {
//	cin >> A[0] >> A[1] >> A[2];	cin >> B[0] >> B[1] >> B[2];	cin >> C[0] >> C[1] >> C[2]; 	cin >> D[0] >> D[1] >> D[2];
//	set_vector(A, B, 0.5, P); set_vector(C, D, 0.5, Q); 	//초기 시작점 (AB의 중점 P), (CD의 중점 Q)
//
//	float AB_After, CD_After;
//	while (true) {
//		AB_compare(P, Q);
//		if (t1 >= 0.5) {
//			t1 = 0.50f;
//			copy(P, P + 3, A);
//		}
//		else {
//			t1 = 0.5f;
//			copy(P, P + 3, B);
//		}
//		AB_After = len(P, Q);
//
//		CD_compare(P, Q);
//		if (t2 >= 0.5) {
//			t2 = 0.50f;
//			copy(Q, Q + 3, C);
//		}
//		else {
//			t2 = 0.5f;
//			copy(Q, Q + 3, D);
//		}
//		CD_After = len(P, Q);
//		if (abs(AB_After - CD_After) <= 0.005) {
//			break;
//		}
//
//	}
//
//
//	if (sqrt(AB_After) <= 0.005)
//		cout << "0";
//	else
//		cout << ceil(sqrt(AB_After));
//	return 0;
//}
//
