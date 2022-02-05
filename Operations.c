#include<stdio.h>
 
int main()
{
    //DATA Assumption
    //M(11)->a
    //M(12)->b
    //M(13)->c

    //For M1 M2
    //M(11)+M(12)->M(13)
    //Load Data
    int a = -6;
    //Data for Addition
    int b = -4;
    //Add and Store
    int c = a + b; //c = -10
    
    //For M3 M4
    //M(12)+M(13)->M(11)
    //Load Data
    int b = -4;
    //Data for Addition
    int c = -10;
    //Add and Store
    int a = b + c; //a = -14

    //For M5 M6
    //M(11)-M(13)->M(12)
    //Load Data
    int a = -14;
    //Data for Subtraction
    int c = -10;
    //Sub and Store
    int b = a - c; //b = -4

    return 0;
}