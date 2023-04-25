#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  
  int n = 5, aux = 0, aux1 = 0, fat = 1, fat1 = 1, j = 1, fatfinal = 1;
  double tempo;
  
  tempo = clock();
  
  if (n > 1) {
    aux= n / 2;
    for(j = 1; j <= aux; j++) {
        fat = fat * j;
    }
    fatfinal = fat;
    for(j = aux + 1; j <= n;j++) {
        fat1 = fat1 * j;
    }
    fatfinal = fatfinal * fat1;
  } else {
    fatfinal = 1;
  }

  printf("Fatorial é: %d\n", fatfinal);
  tempo = clock() - tempo;
  printf("\nTempo total de processamento: %f seg\n\n", ((float)tempo)/CLOCKS_PER_SEC);

  return 0;
}