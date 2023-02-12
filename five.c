#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>
char mess[5][20]={"Hello","CSE","RVCE","NEW"};

int main(int argc,char ** argv){
	int tag=0,root=0,nP,rank;
	char mes[32];
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&nP);
	if(rank!=0){
		strcpy(mes,mess[rank-1]);
		MPI_Send(&mes,32,MPI_CHAR,root,tag,MPI_COMM_WORLD);
	}
	else{
		for(int i=1;i<nP;i++){
			MPI_Recv(&mes,32,MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
			printf("\n%s from %d",mes,i);
		}
	}
	MPI_Finalize();
}
