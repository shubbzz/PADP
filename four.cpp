#include<stdio.h>
#include<error.h>
#include<omp.h>
#include<gd.h>
int main(int argc,char** argv){
	int x,y,h,w,r,g,b,tmp,color;
	tmp=x=y=w=h=r=g=b=color=0;
	gdImagePtr img;
	FILE* fp=NULL;
	char *iname=NULL,*oname=NULL;
	if(argc!=3){
		error(1,0,"wrong usage");
	}
	else{
		iname=argv[1];
		oname=argv[2];
	}
	if((fp=fopen(iname,"r"))==NULL){
		error(1,0,"error opening file");
	}
	else{
		img=gdImageCreateFromPng(fp);
		w=gdImageSX(img);
		h=gdImageSY(img);
	}
	omp_set_num_threads(4);
	double t=omp_get_wtime();
	#pragma omp parallel for private(x,y,r,g,b,color) schedule(static,50)
	for(int x=0;x<=w;x++){
		for(int y=0;y<=h;y++){
			color=gdImageGetPixel(img,x,y);
			r=gdImageRed(img,color);
			g=gdImageGreen(img,color);
			b=gdImageBlue(img,color);
			tmp=(r+g+b)/3;
			color=gdImageColorAllocate(img,tmp,tmp,tmp);
			gdImageSetPixel(img,x,y,color);
		}
	}
	t=omp_get_wtime()-t;
	printf("%lf time for %d threads",t,4);
	if((fp=fopen(oname,"w"))==NULL){
		error(1,0,"error opening file");
	}
	else{
		gdImagePng(img,fp);
		fclose(fp);
	}
	gdImageDestroy(img);
}
