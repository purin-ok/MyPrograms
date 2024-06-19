#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main()
{
    int n, i, j;
    float x[20], y[20], real, imag;

    printf("Enter the number of points: ");
    scanf("%d", &n);

    printf("Enter the data points: ");
    for (i = 0; i < n; i++)
    {
        scanf("%f", &x[i]);
    }

    for (i = 0; i < n; i++)
    {
        real = 0;
        imag = 0;

        for (j = 0; j < n; j++)
        {
            real += x[j] * cos(2 * PI * i * j / n);
            imag -= x[j] * sin(2 * PI * i * j / n);
        }

        y[i] = sqrt(real * real + imag * imag);
    }

    printf("DFT of the given data: ");
    for (i = 0; i < n; i++)
    {
        printf("%.2f ", y[i]);
    }

    return 0;
}