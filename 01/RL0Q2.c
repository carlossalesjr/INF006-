#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct point
{
    int ordem_entrada;
    float distancia_origem;
    float x;
    float y;
} point;

typedef struct nomes
{
    char nome[100];
} nomes;

void ordenador(nomes nameStr[], int nameCont, int numbersInt[], int intCont, float numbersFloat[], int floatCont, point numbersPoints[], int pointCont)
{
    for (int i = 0; i < nameCont; i++)
    {
        for (int j = 0; j < nameCont - 1 - i; j++)
        {
            nomes aux;
            if (strcmp(nameStr[j].nome, nameStr[j + 1].nome) > 0)
            {
                aux = nameStr[j];
                nameStr[j] = nameStr[j + 1];
                nameStr[j + 1] = aux;
            }
        }
    }
    for (int i = 0; i < intCont; i++)
    {
        for (int j = 0; j < intCont - 1 - i; j++)
        {
            int aux;
            if (numbersInt[j] > numbersInt[j + 1])
            {
                aux = numbersInt[j];
                numbersInt[j] = numbersInt[j + 1];
                numbersInt[j + 1] = aux;
            }
        }
    }
    for (int i = 0; i < floatCont; i++)
    {
        for (int j = 0; j < floatCont - 1 - i; j++)
        {
            float aux;
            if (numbersFloat[j] > numbersFloat[j + 1])
            {
                aux = numbersFloat[j];
                numbersFloat[j] = numbersFloat[j + 1];
                numbersFloat[j + 1] = aux;
            }
        }
    }
    for (int i = 0; i < pointCont; i++)
    {
        for (int j = 0; j < pointCont - 1 - i; j++)
        {
            point aux;
            if (numbersPoints[j].distancia_origem > numbersPoints[j + 1].distancia_origem)
            {
                aux = numbersPoints[j];
                numbersPoints[j] = numbersPoints[j + 1];
                numbersPoints[j + 1] = aux;
            }
        }
    }
}

float distancia_euclidiana(int x, int y) {
    return sqrt(x * x + y * y);
}

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
    int linha = 0;

    while (fgets(str, sizeof(str), fp_in) != NULL)
    {
        float numbersFloat[100];
        int numbersInt[100];
        point numbersPoints[100];
        nomes nameStr[100];
        int isFloat = false;

        int floatCont = 0, intCont = 0, nameCont = 0, pointCont = 0;

        char *token = strtok(str, " ");

        while (token != NULL)
        {
            if (isdigit(token[0]) || token[0] == '-')
            {
                isFloat = false;
                for (int i = 0; i < strlen(token); i++)
                {
                    if (token[i] == '.')
                    {
                        isFloat = true;
                        break;
                    }
                }
                if (isFloat)
                    numbersFloat[floatCont++] = atof(token);
                else
                    numbersInt[intCont++] = atoi(token);
            }
            else if (token[0] == '(')
            {
                float x, y;
                if (sscanf(token, "(%f,%f)", &x, &y) == 2)
                {
                    numbersPoints[pointCont].x = x;
                    numbersPoints[pointCont].y = y;
                    numbersPoints[pointCont].ordem_entrada = pointCont;
                    numbersPoints[pointCont++].distancia_origem = distancia_euclidiana(x, y);
                }
            }
            else
            {
                strcpy(nameStr[nameCont++].nome, token);
            }
            token = strtok(NULL, " ");
        }
        // Ordenação
        ordenador(nameStr, nameCont, numbersInt, intCont, numbersFloat, floatCont, numbersPoints, pointCont);
        char text[1000];
        if(linha==0)sprintf(text, "str:" );
        else sprintf(text, "\nstr:");
        for (int i = 0; i < nameCont; i++)
        {
            if (i == 0)
                sprintf(text, "%s%s", text, nameStr[i].nome);
            else
                sprintf(text, "%s %s", text, nameStr[i].nome);
        }
        sprintf(text, "%s %s", text, "int:");
        for (int i = 0; i < intCont; i++)
        {
            if (i == 0)
                sprintf(text, "%s%d", text, numbersInt[i]);
            else
                sprintf(text, "%s %d", text, numbersInt[i]);
        }

        sprintf(text, "%s %s", text, "float:");
        for (int i = 0; i < floatCont; i++)
        {
            if (i == 0)
                sprintf(text, "%s%.5g", text, numbersFloat[i]);
            else
                sprintf(text, "%s %.5g", text, numbersFloat[i]);
        }

        sprintf(text, "%s %s", text, "p:");
        for (int i = 0; i < pointCont; i++)
        {
            if (i == 0)
                sprintf(text, "%s(%.5g,%.5g)", text, numbersPoints[i].x, numbersPoints[i].y);
            else
                sprintf(text, "%s (%.5g,%.5g)", text, numbersPoints[i].x, numbersPoints[i].y);
        }

        fputs(text, fp_out);
        linha++;
    }
    
    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}