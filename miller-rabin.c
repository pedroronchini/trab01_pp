#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Função auxiliar para calcular a potência modular (a^b) % mod
unsigned long long int modular_pow(unsigned long long int base, unsigned long long int exponent, unsigned long long int mod) {
    unsigned long long int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

// Função principal que implementa o teste de Miller-Rabin
bool miller_rabin(unsigned long long int n, int k) {
    if (n <= 1 || n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    // Encontrar d e r para a representação de n-1 em que n-1 = 2^r * d
    unsigned long long int d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // Executar k iterações do teste de Miller-Rabin
    for (int i = 0; i < k; i++) {
        // Gerar um número aleatório 'a' entre 2 e n-2
        unsigned long long int a = 2 + rand() % (n - 3);

        // Calcular a^d % n
        unsigned long long int x = modular_pow(a, d, n);

        if (x == 1 || x == n-1) {
            // Se x = 1 ou x = n-1, a condição para esta iteração é satisfeita, passar para a próxima
            continue;
        }

        // Testar as outras condições para a iteração atual
        bool found_composite = false;
        for (int j = 0; j < r-1; j++) {
            x = modular_pow(x, 2, n);
            if (x == n-1) {
                found_composite = true;
                break;
            }
        }
        if (!found_composite) {
            return false; // Encontrado um testemunho de que n é composto
        }
    }

    return true; // Não foi encontrado testemunho suficiente de que n é composto
}

int main() {
    srand(time(NULL)); // Inicializar o gerador de números aleatórios com uma semente baseada no tempo

    unsigned long long int n;
    int k = 10; // Número de iterações a serem executadas no teste de Miller-Rabin

    printf("Digite um número para verificar se é primo: ");
    scanf("%llu", &n);

    if (miller_rabin(n, k)) {
        printf("%llu é provavelmente primo\n", n);
    } else {
        printf("%llu é composto\n", n);
    }

    return 0;
}
