#include <iostream>

int func(int n1, int n2)
{
    if( (n1>=0 && n2>=0) || (n1<0 && n2<0) )
        return n1*n2;
    else 
        return -(n1*n2);
}

int main (int argc, char **argv)
{
    int N , a , b;
    std::cout <<" Type N: "<< std::endl;
    std::cin>> N;
    for( int i=0; i<N ; i++)
    {
        std::cout <<"Type a and b:"<<std::endl;
        std::cin>> a >> b;
        int res =func(a,b);
        std::cout<<"Result: "<< res <<std::endl;
    }
        /* Podemos fazer com a forma de loop while também:
    while(N!=0){
        std::cout <<"Type a and b:"<<std::endl;
        std::cin>> a >> b;
        int res =func(a,b);
        std::cout<<"Result: "<< res <<std::endl;
        N= N - 1; ou N = -=1;
    }
    */   
}