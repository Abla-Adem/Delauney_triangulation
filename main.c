#include <stdio.h>
#include<omp.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct para{
double *x;
double *y;
} point;

typedef struct paras{
double pts[3*2];
double center[2];
double radius;
struct element *neighbors;
} element;
/**
 * @brief 
 * 
 * @param D 
 * @param elem 
 * @param print 
 * @return double 
 */
double determinant(double *D,element elem,int print){
    double test[9];
    test[0]=elem.pts[0]-D[0];
    test[1]=elem.pts[1]-D[1];
    test[2]=elem.pts[0]*elem.pts[0]+elem.pts[1]*elem.pts[1]-D[0]*D[0]-D[1]*D[1];
    test[3]=elem.pts[2]-D[0];
    test[4]=elem.pts[3]-D[1];
    test[5]=elem.pts[2]*elem.pts[2]+elem.pts[3]*elem.pts[3]-D[0]*D[0]-D[1]*D[1];
    test[6]=elem.pts[4]-D[0];
    test[7]=elem.pts[5]-D[1];
    test[8]=elem.pts[4]*elem.pts[4]+elem.pts[5]*elem.pts[5]-D[0]*D[0]-D[1]*D[1];
    if(print){
        printf("Testing\n[");
    for (int i = 0; i<3;i++){
        for (int j = 0; j <3;j++){
            printf("%lf,",test[i*3+j]);
    }
    printf("]\n[");
    }
    
    }
    double determinant=test[0]*(test[4]*test[8]-test[5]*test[7]);
    determinant=determinant-test[1]*(test[3]*test[8]-test[5]*test[6]);
    determinant=determinant+test[2]*(test[3]*test[7]-test[4]*test[6]);
    return determinant;   
}
void center(element *elem) 
{
    double *gauss=malloc(sizeof(double)*6);
    gauss[0]=elem->pts[4]-elem->pts[0];
    gauss[1]=elem->pts[5]-elem->pts[1];
    gauss[3]=elem->pts[4]-elem->pts[2];
    gauss[4]=elem->pts[5]-elem->pts[3];
    gauss[2]=0.5 * ( ( elem->pts[4]*elem->pts[4] + elem->pts[5]*elem->pts[5] ) - ( elem->pts[0]*elem->pts[0] + elem->pts[1]*elem->pts[1] ) );
    gauss[5]=0.5 * ( ( elem->pts[4]*elem->pts[4] + elem->pts[5]*elem->pts[5] ) - ( elem->pts[2]*elem->pts[2] + elem->pts[3]*elem->pts[3] ) );
    
    
    double pivot=gauss[3];
    for( int i = 3; i <6;i++)
    {
        gauss[i]=gauss[i]-(pivot/gauss[0])*gauss[i-3];
        
    }
    elem->center[1]=gauss[5]/gauss[4];
    elem->center[0]=(gauss[2]-gauss[1]*elem->center[1])/gauss[0];
    elem->radius=sqrt((elem->center[0]-elem->pts[0])*(elem->center[0]-elem->pts[0])+(elem->center[1]-elem->pts[1])*(elem->center[1]-elem->pts[1]));
  
    }
    

int main(int argc, char *argv[]) {
    element elem;
    elem.pts[0]=-2;
    elem.pts[1]=1;
    elem.pts[2]=2;
    elem.pts[3]=2;
    elem.pts[4]=0;
    elem.pts[5]=4;
    double D[2];
     point test;
     test.x=malloc(sizeof(double)*50);
     test.y=malloc(sizeof(double)*50);
    for(int i = 0; i < 50; i++) {
        test.x[i]=rand()/(RAND_MAX+1.)*6-3;
        test.y[i]=rand()/(RAND_MAX+1.)*6-2;
        printf("[%lf,%lf]",test.x[i],test.y[i]);
        D[0]=test.x[i];
        D[1]=test.y[i];
        double determinan=determinant(D,elem,0);
        center(&elem);
        double dist=sqrt((elem.center[0]-D[0])*(elem.center[0]-D[0])+(elem.center[1]-D[1])*(elem.center[1]-D[1]));
        printf("%lf %lf %lf %lf %lf\n",determinan,elem.center[0],elem.center[1],elem.radius,dist);
    }
    
    
    
    
    
    
    
    /* point test;
     test.x=malloc(sizeof(double)*50);
     test.y=malloc(sizeof(double)*50);
    for(int i = 0; i < 50; i++) {
        test.x[i]=rand()/(RAND_MAX+1.)*50;
        test.y[i]=rand()/(RAND_MAX+1.)*50;
    }
    printf("points \n");
    for(int i = 0; i < 50;i++){
            printf("%lf,%lf \n",test.x[i],test.y[i]);
    }
    printf("\n");
    */
     return 0;
}