#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define TARGET 100
#define DELAY 0.05
#define RANDOM 50

#define K 0.05

float Random();

int main() {
	float X = TARGET;
	float Z = X;
	float Xnext = 0;
	
	int i = 0;
	int Rand = 0;
	
	while (1) {
		i++;
		
		Rand = Random();
		
		Xnext = X;
		Z = TARGET + Rand;
		X = Xnext * (1 - K) + K * (Z);
		
		printf("Rand: %d, i: %d, x: %f\n", Rand, i, X);
		
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
