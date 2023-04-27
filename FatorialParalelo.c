#include <time.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  
  int ret, rank, size, i, tag;
  int  n = 1526255, aux = 0, aux1 = 0, j = 1;
  mpz_t fat, fat1, fatfinal;
  double tempo;

  MPI_Status status;
  ret = MPI_Init(&argc, &argv);
  ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);//o valor do no
  ret = MPI_Comm_size(MPI_COMM_WORLD, &size);//quantidades de no
  tag=100;

  mpz_init_set_ui(fat, 1); // Inicializa fat com 1
  mpz_init_set_ui(fat1, 1); // Inicializa fat1 com 1
  mpz_init_set_ui(fatfinal, 1); // Inicializa fatfinal com 1

  tempo = MPI_Wtime();
  
  if (rank == 0) {
    ret = MPI_Send(&n, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);//envia o valor a ser calculado para o no 2 fazer o calculo certo
    aux= n / 2;
    ret = MPI_Send(&aux, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);//envia o valor a ser calculado para os nos
    printf("Valor enviado para o no => %d\n", n);
  }
  
  if(rank == 1) {
    ret = MPI_Recv(&aux,1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    for(j = 1; j <= aux; j++) {
        sleep(00002);
        // fat = fat * j;
        mpz_mul_ui(fat, fat, j);
    }

    ret = MPI_Send(&fat, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);//envia o valor calculado para o no final
  }
  
  if(rank == 2) {
    ret = MPI_Recv(&n,1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    ret = MPI_Recv(&aux,1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
    
    for(j = aux1 + 1; j <= n; j++) {
        sleep(00002);
        // fat1 = fat1 * j;
        mpz_mul_ui(fat1, fat1, j);
    }
         
    // fatfinal = fatfinal * fat1;
    mpz_mul(fatfinal, fatfinal, fat1);
    printf("\nfatorial final eh->%Zd", fatfinal);
    tempo = MPI_Wtime()-tempo;
    printf("\nTempo total de processamento com %d no(s): %f seg\n\n", size, tempo); 
  }

  mpz_clear(fat);
  mpz_clear(fat1);
  mpz_clear(fatfinal);
  
  ret = MPI_Finalize();
  return 0;
}
