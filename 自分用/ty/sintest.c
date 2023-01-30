#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main()
{
    int i, n;
    float x, f, delta;

    printf("Enter the number of samples: ");
    scanf("%d", &n);

    printf("Enter the frequency of the wave: ");
    scanf("%f", &f);

    delta = (2 * PI * f) / n;

    for (i = 0; i < n; i++)
    {
        x = i * delta;
        printf("%.2f\n", sin(x));
    }

    return 0;
}