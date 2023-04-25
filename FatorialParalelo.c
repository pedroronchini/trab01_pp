#include <time.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  
  int ret, rank, size, i, tag;
  int  n = 18, aux = 0, aux1 = 0, fat = 1, fat1 = 1, j = 1, fatfinal = 1;
  double tempo;
  //  mpz_t var2; //declaração de um numero gigante
 
  MPI_Status status;
  ret = MPI_Init(&argc, &argv);
  ret = MPI_Comm_rank(MPI_COMM_WORLD, &rank);//o valor do no
  ret = MPI_Comm_size(MPI_COMM_WORLD, &size);//quantidades de no
  tag=100;

  tempo = MPI_Wtime();
  
  if (rank == 0) {
    if (size == 1) {
        for (i = 1;i <= n; i++) {
            fatfinal = fatfinal * i;
            sleep(00002);
        }
        printf("Fatoreal eh-> %d...\n", fatfinal);
        tempo= MPI_Wtime()-tempo;
        printf("\nTempo total de processamento com %d no(s): %f seg\n\n", size, tempo);
    }

    ret = MPI_Send(&n, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);//envia o valor a ser calculado para o no 2 fazer o calculo certo
    aux= n / 2;
    ret = MPI_Send(&aux, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);//envia o valor a ser calculado para os nos
    printf("Valor enviado para o no => %d\n", n);
  }
  
  if(rank == 1) {
    ret = MPI_Recv(&aux,1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    for(j = 1; j <= aux; j++) {
        sleep(00002);
        fat = fat * j;
    }

    ret = MPI_Send(&fat, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);//envia o valor calculado para o no final
  }
  
  if(rank == 2) {
    ret = MPI_Recv(&n,1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    ret = MPI_Recv(&aux,1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
    
    for(j = aux1 + 1; j <= n;j++) {
        sleep(00002);
        fat1 = fat1 * j;
    }
         
    fatfinal = fatfinal * fat1;
    // printf("\nfatorial final eh->%d",fatfinal);
    tempo = MPI_Wtime()-tempo;
    // printf("\nTempo total de processamento com %d no(s): %f seg\n\n", size, tempo); 
  }
  
  ret = MPI_Finalize();
  return 0;
}
