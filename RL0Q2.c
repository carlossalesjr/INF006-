#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct points
{
    int ordem_entrada;
    float distancia_origem;
    float x;
    float y;
} points;

typedef struct nomes
{
    char nome[100];
} nomes;

int main()
{
    FILE *fp_in = fopen("L0Q2.in", "r");
    FILE *fp_out = fopen("L0Q2.out", "w");
    char str[1000];

    if (fp_in == NULL || fp_out == NULL)
    {
        printf("Os arquivos nao puderam ser abertos!");
        return EXIT_FAILURE;
    }

    fgets(str, sizeof(str), fp_in);

    char space = " ";
    int lineCount = 0;

    char *token = strtok(str, " ");

    while (str != NULL)
    {
        float numbersFloat[100];
        int isFloat = false;
        int numbersInt[100];

        int floatCont = 0, intCont = 0;
        while (token != NULL)
        {
            if (isdigit(token[0]) || token[0] == '-')
            { // integer or float
                for (int i = 0; i < strlen(token); i++)
                    if (token[i] == ".")
                        isFloat = true;
                if (isFloat)
                    numbersFloat[floatCont++] = atof(token);
                else
                    numbersInt[intCont++] = atoi(token);
            }

            else if (strchr(token, '(') != NULL)
            { // 2D point
                float x, y;
                sscanf(token, "(%f,%f)", &x, &y);
                printf("2D Point: (%.1f,%.1f)\n", x, y);
            }

            else
            { // string
                printf("String: %s\n", token);
            }
            token = strtok(NULL, " ");
        }
        return 0;
    }
}