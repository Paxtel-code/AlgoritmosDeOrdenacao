#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int particioneLomuto(int vetor[], int esq, int dir) {
    int pivo = vetor[dir];
    int i = esq;

    for (int j = esq; j < dir; ++j) {
        if (vetor[j] < pivo) {
            int aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
        }
    }
    int aux = vetor[i];
    vetor[i] = vetor[dir];
    vetor[dir] = aux;

    return i;
}
void quicksortLomuto(int vetor[], int esq, int dir){
    int i;
    if(dir>esq){
        i = particioneLomuto(vetor, esq, dir);
        quicksortLomuto(vetor, esq, i - 1);
        quicksortLomuto(vetor, i + 1, dir);
    }
}

int particioneHoare(int vetor[], int esq, int dir) {
    int x = vetor[esq];
    int up = dir;
    int down = esq;
    while (down < up) {
        while ((vetor[down] <= x) && (down < dir))
            down = down + 1;
        while (vetor[up] > x)
            up = up - 1;
        if (down < up) {
            int aux = vetor[down];
            vetor[down] = vetor[up];
            vetor[up] = aux;
        }
    }
    vetor[esq] = vetor[up];
    vetor[up] = x;
    return (up);
}
void quicksortHoare(int vetor[], int esq, int dir) {
    if (dir > esq) {
        int i = particioneHoare(vetor, esq, dir);
        quicksortHoare(vetor, esq, i - 1);
        quicksortHoare(vetor, i + 1, dir);
    }
}

void merge(int vetor[], int esq, int meio, int dir) {
    int vetor2Size = dir - esq + 1;
    int vetor2[vetor2Size];

    for (int i = esq; i <= dir; i++)
        vetor2[i-esq] = vetor[i];

    int i = esq;
    int j = meio + 1;
    int k = esq;


    while (i <= meio && j <= dir) {
        if (vetor2[i - esq] <= vetor2[j - esq]) {
            vetor[k] = vetor2[i - esq];
            i++;
        } else {
            vetor[k] = vetor2[j - esq];
            j++;
        }
        k++;
    }

    while (i <= meio) {
        vetor[k] = vetor2[i - esq];
        i++;
        k++;
    }

    while (j <= dir) {
        vetor[k] = vetor2[j - esq];
        j++;
        k++;
    }
}
void mergeSort(int vetor[], int esq, int dir) {
    if (esq < dir) {
        int meio = (esq - dir) / 2;
        mergeSort(vetor, esq, meio);
        mergeSort(vetor, meio + 1, dir);
        merge(vetor, esq, meio, dir);
    }
}

int main(void) {
    int op = 0;
    int tam = 0;
    remove("Numeros.txt");
    remove("NumerosResultado.txt");

    printf("Digite a quantidade de numeros no arquivo:\n");
    scanf("%d", &tam);
    int *vetor = (int *) malloc(sizeof(int) * tam);

    printf("Digite a opcao desejada:\n1 - Ordenado \n2 - Invertido \n3 - "
           "Aleatorio\n");
    scanf("%d", &op);

    clock_t fim, inicio = clock();
    switch (op) {
        case 1: // ordenado -----------------------------------------
            for (int i = 0; i < tam; i++) {
                vetor[i] = i + 1;
            }
            break;
        case 2: // invertido -----------------------------------------
            for (int i = tam; i > 0; i--) {
                vetor[tam - i] = i;
            }
            break;
        case 3: // aleatorio -----------------------------------------

            for (int i = 0; i < tam; i++) {
                vetor[i] = i + 1;
            }

            for (int i = 0; i < tam; i++) {
                int index = rand() % tam;
                int temp = vetor[i];
                vetor[i] = vetor[index];
                vetor[index] = temp;
            }

    }

    fim = clock();
    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;

    FILE *file = fopen("Numeros.txt", "w");
    if (file != NULL) {
        printf("Arquivo txt criado com sucesso em %.7f s\n", tempo);
    }

    for (int i = 0; i < tam; i++) {
        fprintf(file, "%d\n", vetor[i]);
    }

    fclose(file);

    printf("\nDigite a opcao desejada:\n"
           "1 - Bubble \n"
           "2 - Insert\n"
           "3 - Shell\n"
           "4 - Select\n"
           "5 - Quick [LOMUTO]\n"
           "6 - Quick [HOARE]\n"
           "7 - Merge [ARRUMAR]\n");
    scanf("%d", &op);
    inicio = clock();

    switch (op) {
        case 1: //bubble
            for (int x = tam; x > 1; x--) {
                for (int y = 0; y < x - 1; y++) {
                    if (vetor[y] > vetor[y + 1]) {
                        int aux = vetor[y];
                        vetor[y] = vetor[y + 1];
                        vetor[y + 1] = aux;
                    }
                }
            }
            fim = clock();

            break;
        case 2: //insert
            for (int i = 0; i < tam; i++) {
                int aux = vetor[i];
                int j = i - 1;
                while (j >= 0 && aux < vetor[j]) {
                    vetor[j + 1] = vetor[j];
                    j = j - 1;
                    vetor[j + 1] = aux;
                }
            }
            fim = clock();

            break;
        case 3: { //shell
            int aux, i, j, h;
            for (h = 1; h < tam; h = 3 * h + 1);
            while (h > 0) {
                h = (h - 1) / 3;
                for (i = h; i < tam; i++) {
                    aux = vetor[i];
                    j = i;
                    while (vetor[j - h] > aux) {
                        vetor[j] = vetor[j - h];
                        j -= h;
                        if (j < h)
                            break;
                    }
                    vetor[j] = aux;
                }
            }
            fim = clock();
            break;
        }


        case 4: //select
            for (int i = 0; i < tam-1; i++) {
                int indiceMenor = i;
                for (int j = i+1; j < tam; j++) {
                    if (vetor[j] < vetor[indiceMenor]) {
                        indiceMenor = j;
                    }
                }
                int aux = vetor[i];
                vetor[i] = vetor[indiceMenor];
                vetor[indiceMenor] = aux;
            }
            break;
            fim = clock();
        case 5: //quick lomuto
            quicksortLomuto(vetor, 0, tam - 1);
            fim = clock();
            break;
        case 6: //quick hoare
            quicksortHoare(vetor, 0, tam - 1);
            fim = clock();
            break;
        case 7: //merge]
            mergeSort(vetor, 0, tam - 1);
            fim = clock();
            break;
    }

    tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    FILE *fileResultado = fopen("NumerosResultado.txt", "w");
    if (file != NULL) {
        printf("Arquivo txt resultado criado com sucesso\n");
    }
    int minutos = (int) tempo / 60;
    int segundos = (int) fmod(tempo, 60);

    fprintf(fileResultado, "Tempo de ordenação: %d:%d \n\n", minutos, segundos);
    printf("Tempo de ordenacao: %d:%d \n\n", minutos, segundos);
    for (int i = 0; i < tam; i++) {
        fprintf(fileResultado, "%d\n", vetor[i]);
    }

    return 0;
}