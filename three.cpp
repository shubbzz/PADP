#include<iostream>
#include<stdlib.h>
#include<vector>
#include<omp.h>
#include<string.h>
#include<math.h>
double t;
using namespace std;
inline long Strike(vector<bool>& composite, long i,long stride,long limit){
	for(;i<=limit;i+=stride){
		composite[i]=true;
	}
	return i;
}

long CU(long n){
	long count=0;
	vector <bool> composite(n+1,false);
	long m=sqrt(n);
	for(int i=2;i<=m;i++){
		if(!composite[i]){
			Strike(composite,i*2,i,n);
			count++;
		}
	}
	for(int i=m+1;i<=n;i++){
		if(!composite[i]){
			count++;
		}
	}
	return count;
}

long CF(long n){
	long m=sqrt(n);
	long count=0;
	vector<bool> composite(n+1,false);
	vector<long> striker,factor;
	for(int i=2;i<=m;i++){
		if(!composite[i]){
			count++;
			striker.push_back(Strike(composite,i*2,i,m));
			factor.push_back(i);
		}
	}
	for(int w=m+1;w<=n;w+=m){
		long limit=min(w+m-1,n);
		for(int i=0;i<factor.size();i++){
			striker[i]=Strike(composite,striker[i],factor[i],limit);
		}
		for(long i=w;i<=limit;i++){
			if(!composite[i]){
			count++;
			}
		}
	}
	return count;
}

int main(){
	t=omp_get_wtime();
	cout<<CU(10000000)<<" "<<"time = "<<omp_get_wtime()-t<<"\n";
	t=omp_get_wtime();
	cout<<CF(10000000)<<" "<<"time = "<<omp_get_wtime()-t;
}
