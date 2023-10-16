#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	FILE *fp;
	int i, j, xnum, ynum;
	double x, y, z, xmin, xmax, ymin, ymax, dx, dy;

	xmin = atof(argv[2]); xmax = atof(argv[3]); xnum = atoi(argv[4]);
	ymin = atof(argv[5]); ymax = atof(argv[6]); ynum = atoi(argv[7]);

	dx = (xmax - xmin) / (xnum - 1);
	dy = (ymax - ymin) / (ynum - 1);

	fp = fopen(argv[1], "w");

	x = xmin;
	for (i = 0; i < xnum; i++)
	{
		y = ymin;
		for (j = 0; j < ynum; j++)
		{
			z = x*x + y*y;
			fprintf(fp, "%f, %f, %f\n", x, y, z);
			y += dy;
		}
		x += dx;
	}

	fclose(fp);

	return 0;
}
