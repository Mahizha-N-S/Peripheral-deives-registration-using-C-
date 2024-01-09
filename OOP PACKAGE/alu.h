#ifndef ALU_H_INCLUDED
#define ALU_H_INCLUDED
#include<iostream>
#include<string>
using namespace std;
class ALU
{
    string operation;
public:
    ALU()
    {
        address="none";
        operation="none";
    }
    ALU(string a,string o)
    {
        address=a;
        operation=o;
    }
    void setALU()
    {
        cout<<"enter the operation to proceed(arithmetic,logical):";
        cin>>operation;
    }
    void chooseOperation()
    {
        if(operation=="arithmetic")
    }
};



#endif // ALU_H_INCLUDED
