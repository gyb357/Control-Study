#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TARGET 1000
#define DELAY 0.1

#define KP 0.55
#define KI 0.2
#define KD 0.3
#define DT 2.25

float PIDF(float feedback);
void loop(float num);

int main() {
	float first= 0;
	
	loop(first);
	
	return 0;
}

float PIDF(float feedback) {
	float P, I, D;
	float error, preverror, control;
	
	error = TARGET - feedback;
	
	preverror = error;
	
	P = error;
	I = I + (P * DT);
	D = (P - preverror) / DT;
	
	control = control + (KP * P) + (KI * I) + (KD * D);
	
	return feedback + control;
}

void loop(float num) {
	float error = 0;
	int count = 0;
	
	while (num != TARGET) {
		count++;
		num = PIDF(num);
		error = TARGET - num;
		
		printf("Control = %f, Error = %f\n", num, error);
		
		if (num > TARGET * 10 || num < -TARGET * 10) {
			printf("Control Fail.\n");
			
			system("pause");
		}
		else if (num == TARGET) {
			printf("Control Finished.\n");
		}
		
		Sleep(DELAY * 1000);
	}
}
