#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

float detcalc(float** arr, int n, int sign)
{

    float det = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                det *= arr[i][j];
            }
        }
    }

    return det * sign;

}
float** trig_matr2(float** arr, int n, int* sign)
{

    int k = 0, ind;
    float t_ind;
    while (k < n)
    {
        if (arr[k][k] == 0)
        {
            *sign*= -1;
            ind= 0;
            for (int i = k + 1; i < n; i++)
            {
                if (arr[i][k] != 0)
                {
                    ind = i;
                    break;
                }
            }

            if (ind== 0)
            {

                return NULL;
            }

            else
            {
                for (int j = 0; j < n; j++)
                {
                    float t;
                    t=arr[k][j];
                    arr[k][j]=arr[ind][j];
                    arr[ind][j]=t;
                }
            }
        }

        t_ind= arr[k][k];
        for (int i = k + 1; i < n; i++)
        {
            float m= arr[i][k];
            for (int j = 0; j < n; j++)
                arr[i][j] = arr[i][j] - (arr[k][j] / t_ind) * m;
        }
        k++;
        printf("\n");
    }

    return arr;
}


int main()
{
    setlocale(LC_ALL, "Russian");
int n;
    printf("Введите кол-во строк и столбцов:\n ");
    scanf("%d", &n);

    float det = 0;

    float** arr = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (float*)malloc(n * sizeof(float));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("arr[%i][%i] = ", i, j);
            scanf("%f", &arr[i][j]);
        }

    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", arr[i][j]);
        }
        printf("\n");
    }

    int sign = 1;
    arr = trig_matr2(arr, n, &sign);
    if (arr == NULL)
    {
        printf("Определитель матрицы 0\n ");
    }
    else
    {
        det = detcalc(arr, n, sign);

        printf("Определитель матрицы :\n ");
        printf("%f", det);
    }

}
