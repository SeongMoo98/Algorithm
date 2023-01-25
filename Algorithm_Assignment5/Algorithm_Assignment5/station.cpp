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
