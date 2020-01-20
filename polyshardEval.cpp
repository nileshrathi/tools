#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


float a[]={0,5,6,7,8,9,10,11,12,13};
float w[]={0,1,2,3};
float b[]={0,13,15,17}; //ledger/chain
float s[]={0,3,2,3};    //current spend block
float eb[10];           //encode chain
float es[10];           //encode spend block
float erb[10];           //encoded remaining balance;


struct Data 
{ 
    int x, y; 
};


float coeff[4][10];

double interpolate(Data f[], int xi, int n, int coeff_index) 
{ 
    double result = 0; // Initialize result 
  
    for (int i=0; i<n; i++) 
    { 
        // Compute individual terms of above formula 
        double term = f[i].y; 
        double temp=1;
        for (int j=0;j<n;j++) 
        { 
            if (j!=i) 
                temp = temp*(xi - f[j].x)/double(f[i].x - f[j].x); 
        }

        coeff[coeff_index][i+1]=temp;
        term=term*temp; 
  
        // Add current term to result 
        result += term; 
    } 
  
    return result; 
} 


float lagrangeEval( float x , float w[], float  b[])
{
    float result = (b[1]*(((x-w[2])*(x-w[3]))/((w[1]-w[2])*(w[1]-w[3]))))+ 
           (b[2]*(((x-w[1])*(x-w[3]))/((w[2]-w[1])*(w[2]-w[3]))))+
           (b[3]*(((x-w[1])*(x-w[2]))/((w[3]-w[1])*(w[3]-w[2]))));

    return result;   
}


int main()
{
    
    //encode chain
    for(int i=1;i<10;i++)
    {

        int x=a[i];
        // eb[i]= (b[1]*(((x-w[2])*(x-w[3]))/((w[1]-w[2])*(w[1]-w[3]))))+ 
        //        (b[2]*(((x-w[1])*(x-w[3]))/((w[2]-w[1])*(w[2]-w[3]))))+
        //        (b[3]*(((x-w[1])*(x-w[2]))/((w[3]-w[1])*(w[3]-w[2]))));   
        eb[i]=lagrangeEval(x,w,b); 
    }
       
    cout <<"encoded blocks are ";
    for(int i=0;i<10;i++)
    {
        cout<<eb[i]<<" ";
    }
    cout<<"\n";

  //encode block

  for(int i=1;i<10;i++)
  {
      int x=a[i];

      es[i]=lagrangeEval(x,w,s);
  }

   cout <<"encoded output blocks are ";
   for(int i=0;i<10;i++)
    {
        cout<<es[i]<<" ";
    }
   cout<<"\n";

//polyshard code starts here


//calculate the remaining balance

for(int i=0;i<10;i++)
    {
        erb[i]=eb[i]-es[i];
    }

   cout<<"encoded remaining  balance are ";
   for(int i=0;i<10;i++)
    {
        cout<<erb[i]<<" ";
    }
   cout<<"\n";

//interpolate the function
// x=    5 ,6 ,7 ,8  ,9  ,10 ,11 ,12 ,13
// f(x)= 10 5 -2 -11 -22 -35 -50 -67 -86




    Data f[] = {{5,10}, {6,5}, {7,-2}, {8,-11},{9,-22},{10,-35},{11,-50},{12,-67},{13,-86}}; 


    

  
    // Using the interpolate function to obtain a data point 
    // corresponding to x=3 
    cout << "Value of f(1) is : " << interpolate(f, int(w[1]), 9,1)<<"\n"; 
    cout << "Value of f(1) is : " << interpolate(f, int(w[2]), 9,2)<<"\n"; 
    cout << "Value of f(1) is : " << interpolate(f, int(w[3]), 9,3)<<"\n"; 


    cout<<"Coefficients are...."<<"\n";

    for(int i=1;i<10;i++)
    {
        cout<<coeff[2][i]<<" ";
    }
    cout<<"\n";


    int temp=0;
    for(int i=1;i<10;i++)
    {
        temp=temp+(f[i-1].y)*coeff[2][i];
    }
    cout<<"linear comnination encoded blocks X coefficients "<<temp<<"\n";



    return 0;

}



