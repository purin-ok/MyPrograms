#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mkfile(const char *fname, const char *equation)
{
	FILE *fp;
	char fnamec[32];

	sprintf(fnamec, "%s.c", fname);

	fp = fopen(fnamec, "w");
	if (fp == NULL)
	{
		printf("%s file not open.\n", fnamec);
		exit(EXIT_FAILURE);
	}

	fprintf(
		fp,
		"#include <stdio.h>\n"
		"#include <stdlib.h>\n"
		"#include <math.h>\n"
		"\n"
		"int main(int argc, char **argv)\n"
		"{\n"
		"\tFILE *fp;\n"
		"\tint i, j, xnum, ynum;\n"
		"\tdouble x, y, z, xmin, xmax, ymin, ymax, dx, dy;\n"
		"\n"
		"\txmin = atof(argv[2]); xmax = atof(argv[3]); xnum = atoi(argv[4]);\n"
		"\tymin = atof(argv[5]); ymax = atof(argv[6]); ynum = atoi(argv[7]);\n"
		"\n"
		"\tdx = (xmax - xmin) / (xnum - 1);\n"
		"\tdy = (ymax - ymin) / (ynum - 1);\n"
		"\n"
		"\tfp = fopen(argv[1], \"w\");\n"
		"\n"
		"\tx = xmin;\n"
		"\tfor (i = 0; i < xnum; i++)\n"
		"\t{\n"
		"\t\ty = ymin;\n"
		"\t\tfor (j = 0; j < ynum; j++)\n"
		"\t\t{\n"
		"\t\t\tz = %s;\n"
		"\t\t\tfprintf(fp, \"%s\", x, y, z);\n"
		"\t\t\ty += dy;\n"
		"\t\t}\n"
		"\t\tx += dx;\n"
		"\t}\n"
		"\n"
		"\tfclose(fp);\n"
		"\n"
		"\treturn 0;\n"
		"}\n",
		equation,
		"%f, %f, %f\\n"
	);

	fclose(fp);
}

void compile(const char *fname)
{
	char command[128];

	sprintf(command, "bcc32c %s.c -o %s\n", fname, fname);
	system(command);
}

void mkcsv(const char *fname, double xmin, double xmax, int xnum, double ymin, double ymax, int ynum)
{
	char command[128];

	sprintf(command, "%s %s.csv %f %f %d %f %f %d\n", fname, fname, xmin, xmax, xnum, ymin, ymax, ynum);
	system(command);
}

void mkfunc(const char *fname, const char *equation, double xmin, double xmax, int xnum, double ymin, double ymax, int ynum)
{
	mkfile(fname, equation);
	compile(fname);
	mkcsv(fname, xmin, xmax, xnum, ymin, ymax, ynum);
}
