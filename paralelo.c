#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, min, max, i, j, primo, local_min, local_max, local_count = 0, global_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // verificar se o número de argumentos está correto
    if (argc != 3) {
        if (rank == 0) {
            printf("Uso: %s min max\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    // converter os argumentos de string para inteiro
    min = atoi(argv[1]);
    max = atoi(argv[2]);

    // dividir o intervalo entre as máquinas
    local_min = min + (max - min + 1) * rank / size;
    local_max = min + (max - min + 1) * (rank + 1) / size - 1;

    // percorrer os números locais e verificar se são primos
    for (i = local_min; i <= local_max; i++) {
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
            local_count++;
        }
    }

    // reduzir o número de primos em todas as máquinas para a máquina 0
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // imprimir os números primos na máquina 0
    if (rank == 0) {
        printf("Números primos entre %d e %d: %d\n", min, max, global_count);
    }

    MPI_Finalize();
    return 0;
}