#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define A 1
#define B 1
#define C 1
#define D 0

#define Q 1
#define R 0.01

#define First 1000
#define Delay 100

#define Solve 1

float Riccati(float p, float k);
float SolveK(float p);
float Cost(float x, float u);

int main() {
	float p, pn;
	float k, u;
	float x, xhat = First;
	float cost;
	float ac;
	
	float y;
	
	int count = 1;
	
	while (abs(y) > 0.0001) {
		pn = p;
		
		p = Riccati(pn, k);
		k = SolveK(pn);
		cost = Cost(x, u);
		
		x = xhat;
		u = -k * x; // Control Value
		
		xhat = A * x + B * u;
		y = C * x + D * u;
		
		ac = A - B * k;
		
		printf("%d,  u = %f, y = %f\n", count, u, y);
		
		count++;
		
		if (abs(y) > First * 2.5) {
			printf("Control Fail\n");
			
			system("pause");
			return 0;
		}
		
		Sleep(Delay);
	}
		
	return 0;
}

float Riccati(float p, float k) {
	// Infinite
	// A'*P + P*A - P*B * R^-1*B'*P + Q
	
	// Finite
	// A'*P*A - (A'*P*B)*(R + B'*P*B)^-1*(B'*P*A) + Q
	
	// --- Infinite ---
	return 
	A * p - (A - B * k) * p + Q;
	/*
	A * p + p * A
	- (p * B * B * p) / R
	+ Q;
	*/
	
	// --- Finite ---
	/*
	return 
	A * p * A
	- (A * p * B) * (B * p * A)
	/ (R + B * p * B);
	*/
}

float SolveK(float p) {
	// Infinite
	// P * B * -R^-1
	
	// Finite
	// (R + B' * P * B)^-1 * B' * P * A
	
	// --- Infinite ---
	/* return 
	-(p * B / R);
	*/
	
	// --- Finite ---
	return 
	(B * p * A) / (R + B * p * B);
}
	
float Cost(float x, float u) {
	float Cost;
	
	// Integral 0.5*(X'*Q*X + U'*R*U)*dt
	
	Cost += (0.5 * (x * Q * x) + (u * R * u)) * 0.1;
	return Cost;
}
