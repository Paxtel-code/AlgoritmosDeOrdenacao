#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

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
void quickSortLomuto(int vetor[], int esq, int dir){
    int i;
    if(dir>esq){
        i = particioneLomuto(vetor, esq, dir);
        quickSortLomuto(vetor, esq, i - 1);
        quickSortLomuto(vetor, i + 1, dir);
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
void quickSortHoare(int vetor[], int esq, int dir) {
    if (dir > esq) {
        int i = particioneHoare(vetor, esq, dir);
        quickSortHoare(vetor, esq, i - 1);
        quickSortHoare(vetor, i + 1, dir);
    }
}

void merge(int vetor[], int esq, int meio, int dir) {
    int auxSize = dir - esq + 1;
    int aux[auxSize];
    for (int i = esq; i <= dir; i++) {
        aux[i - esq] = vetor[i];
    }
    int i = esq;
    int j = meio + 1;
    int k = esq;
    while (i <= meio && j <= dir) {
        if (aux[i - esq] <= aux[j - esq]) {
            vetor[k] = aux[i - esq];
            i++;
        } else {
            vetor[k] = aux[j - esq];
            j++;
        }
        k++;
    }
    while (i <= meio) {
        vetor[k] = aux[i - esq];
        i++;
        k++;
    }
    while (j <= dir) {
        vetor[k] = aux[j - esq];
        j++;
        k++;
    }
}
void mergeSort(int vetor[], int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        mergeSort(vetor, esq, meio);
        mergeSort(vetor, meio + 1, dir);
        merge(vetor, esq, meio, dir);
    }
}

void bucketSort(int vetor[], int n) {
    int i, j;
    int count[n];
    for (i=0; i < n; i++) {
        count[i] = 0;
    }
    for (i=0; i < n; i++) {
        (count[vetor[i]])++;
    }
    for (i=0,j=0; i < n; i++) {
        for (; count[i]>0;(count[i])--) {
            vetor[j++] = i;
        }
    }
}

void radixSort(int vetor[], int tam) {
    int base = 10, r;
    int digit = 3;
    int *B = (int *)malloc(tam * sizeof(int));
    int *C = (int *)malloc(base * sizeof(int));

    for (int m = 0; m < digit; m++) {
        for (int i = 0; i < base; ++i)
            C[i] = 0;
        for (int j = 0; j < tam; ++j) {
            r = (vetor[j] / (int)(pow(10.0, m))) % base;
            ++C[r];
        }
        for (int i = 1; i < base; ++i)
            C[i] += C[i - 1];
        for (int j = tam - 1; j >= 0; --j) {
            r = (vetor[j] / (int)(pow(10.0, m))) % base;
            int i = --C[r];
            B[i] = vetor[j];
        }
        for (int j = 0; j < tam; ++j)
            vetor[j] = B[j];
    }

    free(B);
    free(C);
}

void bubbleSort(int vetor[], int tam){
    for (int x = tam; x > 1; x--) {
        for (int y = 0; y < x - 1; y++) {
            if (vetor[y] > vetor[y + 1]) {
                int aux = vetor[y];
                vetor[y] = vetor[y + 1];
                vetor[y + 1] = aux;
            }
        }
    }
}

void insertSort(int vetor[], int tam){
    for (int i = 0; i < tam; i++) {
        int aux = vetor[i];
        int j = i - 1;
        while (j >= 0 && aux < vetor[j]) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
            vetor[j + 1] = aux;
        }
    }
}

void shellSort(int vetor[], int tam){
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
}

void selectSort(int vetor[], int tam){
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
}

int main(void) {
    int op = 0;
    int tam = 0;
    remove("Numeros.txt");
    remove("NumerosResultado.txt");

    printf("Digite a quantidade de numeros no arquivo: \n"
           "1 - 500K \n"
           "2 - 750K \n"
           "3 - 1KK \n"
           );
    scanf("%d", &tam);
    if(tam == 1)
        tam = 500000;
    if(tam == 2)
        tam = 750000;
    if(tam == 3)
        tam = 1000000;
    int *vetor = (int *) malloc(sizeof(int) * tam);

    printf("Digite a opcao desejada:\n1 - Ordenado \n2 - Invertido \n3 - "
           "Aleatorio\n");
    scanf("%d", &op);


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


    FILE *file = fopen("Numeros.txt", "w");
    if (file != NULL) {
        printf("Arquivo txt criado com sucesso\n");
    }

    for (int i = 0; i < tam; i++) {
        fprintf(file, "%d\n", vetor[i]);
    }

    fclose(file);

    printf("\nDigite a opcao desejada:\n"
           "1 - Bubble \n"
           "2 - Insert\n"
           "3 - Select\n"
           "4 - Quick [LOMUTO] problema\n"
           "5 - Quick [HOARE] problema\n"
           "6 - Merge\n"
           "7 - Radix\n"
           "8 - Heap\n");
    scanf("%d", &op);
    clock_t fim, inicio = clock();

    switch (op) {
        case 1: //bubble -----------------------------------------
            bubbleSort(vetor,tam);
            fim = clock();

            break;
        case 2: //insert -----------------------------------------
            insertSort(vetor,tam);
            fim = clock();

            break;
        case 3: //select -----------------------------------------
            selectSort(vetor,tam);
            break;
            fim = clock();
        case 4: //quick lomuto -----------------------------------------
            quickSortLomuto(vetor, 0, tam - 1);
            fim = clock();
            break;
        case 5: //quick hoare -----------------------------------------
            quickSortHoare(vetor, 0, tam - 1);
            fim = clock();
            break;
        case 6: //merge -----------------------------------------
            mergeSort(vetor, 0, tam - 1);
            fim = clock();
            break;
        case 7: //radix ------------------------------------------
            radixSort(vetor,  tam);
            fim = clock();
            break;
        case 8:
            bucketSort(vetor,tam);
            fim = clock();
            break;
    }

    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    FILE *fileResultado = fopen("NumerosResultado.txt", "w");
    if (file != NULL) {
        printf("Arquivo txt resultado criado com sucesso\n");
    }


    int min = (int) tempo / 60;
    int seg = (int) fmod(tempo, 60);
    int mil =  (tempo-min*60-seg)*1000;

    fprintf(fileResultado,"%f\n",tempo);
    printf("%f\n",tempo);

    //fprintf(fileResultado, "Tempo de ordenação: %d:%d:%d \n\n", min, seg,mil);
    //printf("Tempo de ordenacao: %d:%d:%d \n\n", min, seg,mil);

    for (int i = 0; i < tam; i++) {
        fprintf(fileResultado, "%d\n", vetor[i]);
    }

    for (int x = 0; x < 5; x++) {
        Beep(200, 250);
    }

    return 0;
}