#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define TARGET 0
#define DELAY 0.075
#define RANDOM 50

#define DELTA 1

#define KQ 50
#define KR 10000
#define Kp 0.56
#define Ki 0.2
#define Kd 0.3
#define Dt 2.25

float PIDF(float target, int i, float feedback, float X);
float Random();

int main() {
	float P, K, Z, X = TARGET;
	float Pnext, Xnext = 0;
	
	float PID = 0;
	float control = 0;
	float error = 0;
	
	int i = 0;
	int Rand = 0;
	
	while (1) {
		i += DELTA;
		
		Rand = Random();
		
		// PIDF Control
		PID = PIDF(TARGET, i, PID, X);
		
		// Kalman Filter
		Xnext = X + DELTA;
		Pnext = P + KQ;
		
		K = Pnext / (Pnext + KR);
		Z = TARGET + Rand + i;
		X = Xnext + K * (Z - Xnext);
		P = (1 - K) * Pnext;
		
		// Control
		control = X + PID;
		error =  i - control;
		
		printf("rand: %d, i: %d, num: %f, err: %f\n", Rand, i, control, error);
		
		Sleep(DELAY * 1000);
	}
	
	return 0;
}

float Random() {
	int Rand, Sign;
	
	// srand((unsigned)time(NULL));
	
	Rand = rand() % RANDOM;
	Sign = Rand % 2 == 1 ? 1 : -1;
	
	return Rand * Sign;
}

float PIDF(float target, int i, float feedback, float X) {
	float P, I, D;
	float error, preverror, control;
	
	error = (i - DELTA - X) - feedback;
	
	preverror = error;
	
	P = error;
	I = I + P * Dt;
	D = (P - preverror) / Dt;
	
	control = control + (Kp * P) + (Ki * I) + (Kd * D);
	
	return feedback + control;
}
