#include<fstream>
#include<omp.h>
#include<iostream>
#include<ctype.h>
#include<cstring>

using namespace std;

int strcmpi(string a,string b){
	if(a.length()!=b.length()){return -1;}
	for(int i=0;i<a.length();i++){
		if(tolower(a[i])!=tolower(b[i])){
			return -1;
		}
	}
	return 1;
}

int main(){
	string filename="six.cpp";
	string words[4]={"if","#include","for","omp"};
	for(int j=1;j<=8;j*=2){
		double t=omp_get_wtime();
		#pragma omp parallel for shared(words) num_threads(j)
		for(int k=0;k<4;k++){
			int count=0;
			fstream file;
			string word1;
			file.open(filename.c_str());
			while(file>>word1){
				if(strcmpi(word1,words[k])==1){count++;}			
			}
			cout<<words[k]<<" = "<<count;
		}
		cout<<"\ntime = "<<omp_get_wtime()-t<<" for "<<j<<"threads\n";
	}
	return 0;
}
