#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc,char **argv){
	int iter=1000000000;
	int i,rc,ri,count=0;
	double pi,x,y,z,t;
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0) t=MPI_Wtime();
	if(rank>0){
		srand(57843);
		for(i=0;i<iter;i++){
			x=(double)rand()/RAND_MAX;
			y=(double)rand()/RAND_MAX;
			if((x*x+y*y)<=1) count++;
		}
	}
	MPI_Reduce(&count,&rc,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&iter,&ri,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	ri=ri-iter;
	if(rank==0){
		t=MPI_Wtime()-t;
		pi=(double)rc/(double)ri*4;
		printf("time = %lf\t pi = %lf",t,pi);
	}
	MPI_Finalize();
}
