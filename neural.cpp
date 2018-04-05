#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>

using namespace std;

double v[3] = {0.4,-0.3,-0.5}, w[3]={0.2,-0.4,0.2},x1[2]={0.0,1.0},x2[2]={1.0,0.0},t[2]={1.0,0.0},zIn,zOut,yIn,yOut,dIn,dK,dZ;
bool accept[2] = {false, false};
bool flag = false;


double sigmoid(double z)
{
    double out;
    out = 1/(1+exp(-z));
    return out;
}

double diffSig(double z)
{
     double out;
     out = sigmoid(z) * (1 - sigmoid(z));
     return out;
}

void calculateOutput(int idx)
{
     zIn = v[0] +((x1[idx]*v[1])+(x2[idx]*v[2]));
     zOut = sigmoid(zIn);
     yIn = w[0]+ ((w[1]*zOut)+(w[2]*x2[idx]));
     yOut = sigmoid(yIn);

     double err = t[idx]-yOut;

     if(abs(err)<=0.002)
     {
          printf("x1=%lf x2=%lf desiredOutput=%lf output=%lf\n",x1[idx],x2[idx],t[idx],yOut);
          printf("error %lf\n",err);
          accept[idx] = true;
          int i,k=0;
          for(i=0;i<2;i++)
          {
              if(!accept[i]) k=1;
          }
          if(k==0)
          {
              flag = true;
              return;
          }
     }
     dK = err * diffSig(yIn);
     double difW1 = dK * zOut;
     double difW2 = dK * x2[idx];
     double difW0 = dK;
     dIn = dK * w[1];
     dZ = dIn * diffSig(zIn);
     double difV1 = dZ * x1[idx];
     double difV2 = dZ * x2[idx];
     double difV0 = dZ;
     w[0] += difW0;
     w[1] += difW1;
     w[2] += difW2;
     v[0] += difV0;
     v[1] += difV1;
     v[2] += difV2;
}



void initialize()
{
    int i, j;
    for(i=0;i<3;i++)
    {

        v[i] = (double)rand();
        w[i] = (double)rand();
    }
}

main()
{
    int indx = 0;
    int iterCnt = 0;
    while(!flag)
    {

         if(!accept[indx]) calculateOutput(indx);
         if(indx==1) indx=0;
         else indx = 1;
         iterCnt++;
    }
    printf("Number of iteration %d\n",iterCnt);
    int i;
    for(i=0;i<3;i++) printf("v%d %lf\n",i,v[i]);
    for(i=0;i<3;i++) printf("w%d %lf\n",i,w[i]);
    return 0;
}
