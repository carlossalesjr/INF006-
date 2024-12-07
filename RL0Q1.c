#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int x, y;
    double distancia;
} points;

float distancia_euclidiana(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void selection(points pontos[], int n) {
    int i, j, min_idx;
    points temp;

    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (pontos[j].distancia < pontos[min_idx].distancia) {
                min_idx = j;
            }
        }
        temp = pontos[min_idx];
        pontos[min_idx] = pontos[i];
        pontos[i] = temp;
    }
}

int main() {
    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char linha[1000];
    points pontos[500];
    int count = 0;

    while (fgets(linha, sizeof(linha), fp_in)) {
        char *token = strtok(linha, " ");
        while (token != NULL) {
            if (strcmp(token, "points") == 0) {
                token = strtok(NULL, " ");
                continue;
            }
            int x, y;
            sscanf(token, "(%d,%d)", &x, &y);
            pontos[count].x = x;
            pontos[count].y = y;
            pontos[count].distancia = distancia_euclidiana(0, 0, x, y);
            count++;
            token = strtok(NULL, " ");
        }
    }

    selection(pontos, count);

    fprintf(fp_out, "points");
    for (int i = 0; i < count; i++) {
        fprintf(fp_out, " (%d,%d)", pontos[i].x, pontos[i].y);
    }

    float distanciaTotal = 0.0;
    for (int i = 0; i < count - 1; i++) {
        distanciaTotal += distancia_euclidiana(pontos[i].x, pontos[i].y, pontos[i + 1].x, pontos[i + 1].y);
    }

    float shortcut = distancia_euclidiana(pontos[0].x, pontos[0].y, pontos[count - 1].x, pontos[count - 1].y);

    fprintf(fp_out, " distance %.2f", distanciaTotal);
    fprintf(fp_out, " shortcut %.2f\n", shortcut);

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}