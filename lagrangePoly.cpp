#include <stdlib.h>
#include <iostream>

using namespace std;


float a[]={0,5,6,7,8,9,10,11,12,13};
float w[]={0,1,2,3};
float b[]={0,13,15,17};
float eb[10];


float lagrangeEval( float x , float w[], float  b[])
{
    float result = (b[1]*(((x-w[2])*(x-w[3]))/((w[1]-w[2])*(w[1]-w[3]))))+ 
           (b[2]*(((x-w[1])*(x-w[3]))/((w[2]-w[1])*(w[2]-w[3]))))+
           (b[3]*(((x-w[1])*(x-w[2]))/((w[3]-w[1])*(w[3]-w[2]))));

    return result;   
}


int main()
{
    
    int check=lagrangeEval(w[1],w,b);
    cout<<"get check"<<check<<"   ";

    for(int i=1;i<10;i++)
    {

        int x=a[i];
        // eb[i]= (b[1]*(((x-w[2])*(x-w[3]))/((w[1]-w[2])*(w[1]-w[3]))))+ 
        //        (b[2]*(((x-w[1])*(x-w[3]))/((w[2]-w[1])*(w[2]-w[3]))))+
        //        (b[3]*(((x-w[1])*(x-w[2]))/((w[3]-w[1])*(w[3]-w[2]))));   
        eb[i]=lagrangeEval(x,w,b); 
    }
    

    for(int i=0;i<10;i++)
    {
        cout<<eb[i]<<" ";
    }
    return 0;

}
