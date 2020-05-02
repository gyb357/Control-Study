#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define TARGET 100
#define DELAY 0.08
#define RANDOM 50

#define KQ 50
#define KR 10000

float Random();

int main() {
	float P, K, Z, X = TARGET;
	float Pnext, Xnext = 0;
	
	int i, Rand = 0;
	
	while (1) {
		i++;
		
		Rand = Random();
		
		Xnext = X;
		Pnext = P + KQ;
		
		K = Pnext / (Pnext + KR);
		Z = TARGET + Rand + i;
		X = Xnext + K * (Z - Xnext);
		P = (1 - K) * Pnext;
		
		printf("Rand: %d, i: %d, k: %f, z: %f, x: %f\n", Rand, i, K, Z, X);
		
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
