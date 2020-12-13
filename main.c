#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void res(float** arr, int n, float** a)
{

    int k = 0;
    float m;
    for (k = n - 1; k > 0; k--)
    {
        for (int j = k - 1; j >= 0; j--)
        {
            m = arr[j][k];
            arr[j][k] -= arr[k][k] * m;
            for (int i = n - 1; i >= 0; i--)
                a[j][i] -= a[k][i] * m;
        }
    }

}


void Copy(float** arr1, float** arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr2[i][j] = arr1[i][j];
        }
    }

}

float** Proizv(float** arr1, float** arr2, int n)
{

    float** p = (float**)malloc(n * sizeof(float*));

    for (int i = 0; i < n; i++)
    {
        p[i] = (float*)malloc(n * sizeof(float));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p[i][j] = 0;

            for (int k = 0; k < n; k++)
                p[i][j] += arr1[i][k] * arr2[k][j];

        }

    }
    return p;
}
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
            *sign = -1;
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


float** trig_matr(float** arr, int n, float** a)
{

    int k = 0, ind;
    float t_ind;
    while (k < n)
    {
        if (arr[k][k] == 0)
        {
            ind = 0;
            for (int i = k + 1; i < n; i++)
            {
                if (arr[i][k] != 0)
                {
                    ind= i;
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
                    float t,temp;
                    t=arr[k][j];
                    arr[k][j]=arr[ind][j];
                    arr[ind][j]=t;

                    temp=a[k][j];
                    a[k][j]=a[ind][j];
                    a[ind][j]=temp;
                }
            }

        }


        t_ind= arr[k][k];

        for (int j = 0; j < n; j++)
        {
            arr[k][j] = arr[k][j] / t_ind;
            a[k][j] = a[k][j] / t_ind;
        }

        for (int i = k + 1; i < n; i++)
        {

            int m= arr[i][k];
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = arr[i][j] - arr[k][j] * m;
                a[i][j] = a[i][j] - a[k][j] * m;
            }
        }
        k++;
    }

    return a;
}


void task9_7()
{
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
    arr = trig_matr2(arr, n,&sign);
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

void task9_6()
{
    int n;
    printf("Введите кол-во строк и столбцов:\n ");
    scanf("%d", &n);

    float** arr = (float**)malloc(n * sizeof(float*));
    float** arr_copy = (float**)malloc(n * sizeof(float*));
    float** Edmatr = (float**)malloc(n * sizeof(float*));
    float** ans= (float**)malloc(n * sizeof(float*));

    for (int i = 0; i < n; i++)
    {
        arr [i]= (float**)malloc(n * sizeof(float*));
        arr_copy [i]= (float**)malloc(n * sizeof(float*));
        Edmatr[i]= (float**)malloc(n * sizeof(float*));
        ans[i]= (float**)malloc(n * sizeof(float*));

    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("arr[%d][%d] = ", i, j);
            scanf("%f", &arr[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (i == j)
            {
                Edmatr[i][j] = 1;
            }
            else Edmatr[i][j] = 0;
        }
    }
    Copy(arr, arr_copy, n);
    if (trig_matr(arr, n, Edmatr) != NULL)
    {


        res(arr, n, Edmatr);
        printf("\nОбратная матрица\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%f ", Edmatr[i][j]);
            }
            printf("\n");
        }

        printf("\nПроверка\n");
        printf("A * A^-1 = ");
        printf("\n");
        ans = Proizv(Edmatr, arr_copy, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%f ", ans[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Решений нет");
    }

}


int main()
{
    setlocale(LC_ALL, "Russian");

    int n =3 ;

    while (n != 0)
    {
        printf("\nВведите номер задания\n");
        printf("\n1-9_6, 2-9_7, 0-выход\n");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            task9_6();

            break;

        case 2:
            task9_7();
            break;
            break;
        default:
            n = 0;
            break;
        }

    }

}
