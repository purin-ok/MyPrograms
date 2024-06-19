#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUF 80
#define DATANUM 1000

int main(int argc, char **argv){

	FILE *fp;
	double amp[DATANUM],tm[DATANUM];
	int i,j,n;
	double re,im,x,dt,df;
	char buf[BUF];

    if(argc < 2){
        fprintf(stderr, "File does not exist\n");
        return EXIT_FAILURE;
    }

	if ((fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "File not open\n");
		return EXIT_FAILURE;
	}

	for (n=0; n<DATANUM;){
		if(fgets(buf, sizeof(buf), fp) == NULL) break;
		if(buf[0] == '#') continue;
		tm[n] = atof(strtok(buf,","));
		amp[n] = atof(strtok(NULL, "\r\n\0"));
		n++;
	}

	dt = (tm[1] - tm[0])*0.001; //•W–{‰»ŠÔŠudt[s]

	for (i=0; i<n; i++){
		for(j=0,re=0,im=0; j<n; j++) {
			re += amp[j]*cos(2*M_PI*j*i/n)*dt;
			im += amp[j]*sin(2*M_PI*j*i/n)*dt;
		}
		x = sqrt(re*re+im*im)*2;
		printf("%f, %f\n", i/dt/n, x);
	}

	fclose(fp);
	return 0;
}