#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
  
  int n = 18, aux = 0, aux1 = 0, j = 1;
  mpz_t fat, fat1, fatfinal;
  double tempo;
  
  tempo = clock();

  mpz_init_set_ui(fat, 1); // Inicializa fat com 1
  mpz_init_set_ui(fatfinal, 1); // Inicializa fatfinal com 1
  
  if (n > 1) {
    aux= n / 2;
    for(j = 1; j <= aux; j++) {
      // fat = fat * j;
      mpz_mul_ui(fat, fat, j); // Multiplica fat por j
    }
    // fatfinal = fat;
    mpz_set(fatfinal, fat); // Copia o valor de fat para fatfinal
    mpz_set_ui(fat, 1); // Reinicializa fat com 1
    for(j = aux + 1; j <= n;j++) {
      // fat1 = fat1 * j;
      mpz_mul_ui(fat1, fat1, j); // Multiplica fat1 por j
    }
    // fatfinal = fatfinal * fat1;
    mpz_mult(fatfinal, fatfinal, fat1); // Multiplica fatfinal por fat1
  } else {
    fatfinal = 1;
  }

  gmp_printf("Fatorial é: %Zd\n", fatfinal);
  tempo = clock() - tempo;
  printf("\nTempo total de processamento: %f seg\n\n", ((float)tempo)/CLOCKS_PER_SEC);

  // libera a memória alocada para as variáveis
  mpz_clear(fat);
  mpz_clear(fat1);
  mpz_clear(fatfinal);

  return 0;
}