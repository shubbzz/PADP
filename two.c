#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
	int  nt,size,j;
	for(size=250;size<=1000;size+=250){
		printf("\nsize = %d",size);
		for(nt=1;nt<=8;nt*=2){
			printf("\nthreads = %d",nt);
			int r=size,c=size,i,j,count=0,k;
			int **arr1=(int **)malloc(r*sizeof(int*));
			for(i=0;i<r;i++){
				arr1[i]=(int *)malloc(c*sizeof(int*));
			}
			int **arr2=(int **)malloc(r*sizeof(int*));
			for(i=0;i<r;i++){
				arr2[i]=(int *)malloc(c*sizeof(int*));
			}
			int **arr3=(int **)malloc(r*sizeof(int*));
			for(i=0;i<r;i++){
				arr3[i]=(int *)malloc(c*sizeof(int*));
			}
			for(i=0;i<c;i++){
				for(i=0;i<r;i++){
					arr1[i][j]=count++;
				}
			}
			for(i=0;i<c;i++){
				for(i=0;i<r;i++){
					arr2[i][j]=count++;
				}
			}
			double t=omp_get_wtime();
			#pragma omp parallel for private(j,k)
			for(i=0;i<r;i++){
				for(j=0;j<c;j++){
					for(k=0;k<r;k++){
						arr3[i][j]+=arr1[i][k]*arr2[k][j];
					}
				}
			}
			t=omp_get_wtime()-t;
			printf(" time = %lf",t);
		}
	}
}
