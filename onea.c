#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void main(int argc,char** argv){
	int n=0,i,count=0;
	int nt=1;
	double pi,x,y,z,st,end;
	for(i=1;i<=8;i*=2){
		printf("\n %d threads",i);
		for(n=100;n<=1000000;n*=10){
			count=0;
			srand(56372);
			st=omp_get_wtime();
			omp_set_num_threads(i);
			#pragma omp parallel for
			for(i=1;i<n;i++){
				x=(double)rand()/RAND_MAX;
				y=(double)rand()/RAND_MAX;
				if((x*x+y*y)<=1){
					count++;	
				}
			}
			pi=(double)count/n*4;
			end=omp_get_wtime();
			printf("\npi = %lf\t time = %lf n = %d",pi,end-st,n);
		}
	}
}
