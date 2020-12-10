#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void transform(int k, int n, float **matr, int *res)
{
    int i, j;
    int imax = k, jmax = k;

    for (i = k; i < n; i++)
        for (j = k; j < n; j++)
            if (fabs(matr[imax][jmax]) < fabs(matr[i][j]))
            {
                imax = i;

                jmax = j;

            }

    for (j = k; j < n + 1; j++)
    {
        float t = matr[k][j];
        matr[k][j] = matr[imax][j];
        matr[imax][j] = t;
    }

    for (i = 0; i < n; i++)
    {
        float t = matr[i][k];
        matr[i][k] = matr[i][jmax];
        matr[i][jmax] = t;
    }
    i = res[k];

    res[k] = res[jmax];

    res[jmax] = i;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    float **matr;
    float *x;
    int i,j,k;
    int *res;
    int n;

    printf("¬ведите кол-во уравнений\n");
    scanf("%d", &n);

    matr = (float**) malloc(n*sizeof(float*));
    x = (float*) malloc(n*sizeof(float));
    res = (int*) malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
    {
        matr[i] = (float*) malloc((n+1)*sizeof(float));
    }

    printf("¬ведите строки матрицы\n");
    for (i = 0; i < n; i++)
        for (j = 0; j <= n; j++)
            scanf("%f", &matr[i][j]);

    for (i = 0; i < n; i++)
        res[i] = i;

    for (k = 0; k < n; k++)
    {
        transform(k, n, matr, res);

        if (fabs(matr[k][k]) < 0.00001 )
        {
            printf("");
            return 0;
        }

        for (j = n; j >= k; j--)
            matr[k][j]= matr[k][j]/matr[k][k];


        for (i = k+ 1; i < n; i++)
            for (j = n; j >= k; j--)
                matr[i][j] = matr[i][j] - (matr[k][j] * matr[i][k]);

    }

    for ( i = 0; i < n; i++)
        x[i] = matr[i][n];

    for (i = n - 2; i >= 0; i--)
        for (j = i + 1; j < n; j++)
            x[i]= x[i] - (x[j] * matr[i][j]);

    printf("\n");

    printf("–ешение системы:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j <= n; j++)

            if (i == res[j])
            {
                printf("%f\n", x[j]);
                break;
            }
    return 0;
}
