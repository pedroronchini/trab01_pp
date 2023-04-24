#include <stdio.h>

int main(void) {
	int min, max, i, j, primo;
	scanf("%i %i", &min, &max);
	
	for (i = min; i <= max; i++) {
		if (i == 0 || i == 1) {
			//números zero e 1 não são primos
			primo = 0;
		} else {
			primo = 1; //considero inicialmente que o número é primo
			for(j = 2; j < i; j++) { //tento provar que ele não é primo
				if (i % j == 0) {
					primo = 0; //consigo provar que ele não é primo
				}
			}
		}
		if (primo == 1) {
			printf("%i ", i);
		}
	}
	
	return 0;
}