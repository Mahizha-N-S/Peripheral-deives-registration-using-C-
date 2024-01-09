#include<iostream>
#include<conio.h>
#include<windows.h>
#include<string>
#include<fstream>
#include<time.h>
using namespace std;
class ALU
{
    string operation;   //arithmetic,logical
public:
    ALU()
    {
        operation="none";
    }
    ALU(string o)
    {
        operation=o;
    }
    void setALU()
    {
        cout<<"SETTING ALU OPERATION../n/n";
        cout<<"enter the operation to proceed...."; //storing what type of operation the user wants into the ALU operations
        cin>>operation;
    }
};

    /*it will get the address of i/o device and it will check whether the device already conected and registered in input
     or output device file.. new device ask need to connect and if yes add it to particular input or output file.
     if virus address detected then warning and not connected with the device*/

class CU
{
public:
   virtual void setAddress()=0;
   virtual string getAddress()=0;
   virtual void DataProcess()=0;
   friend void assignAddress(CU *c)
   {
        c->setAddress();
   }
   friend void assignData(CU *c)
   {
       char ch;
       int check=0;
       string add,line;
       cout<<"IS IT INPUT OR OUTPUT DEVICE?(i/o)";    //to make sure that an input device not to manipulate data
       cin>>ch;
       add= c->getAddress();
       if(ch=='i' || ch=='I')
       {
            ifstream fin("Input_Device.txt");
            if(!fin.is_open())
            {
                cout<<"FILE IS NOT OPENED!";
            }
            else
            {
                while(!fin.eof())
                {
                   getline(fin,line);
                    if(add==line)
                    {
                        check=1;
                        break;
                    }
                    else
                        check=0;
                }
                if(check==0)
                {
                    cout<<"WARNING!! ACCESS DENIED.. UNAUTHORISED DATA MANIPULATION!!"<<endl;
                }
                else
                {
                    c->DataProcess();
                }
            }
       }
       else if(ch=='o' || ch=='O')
       {
           ifstream fin("Output_Device.txt");
            if(!fin.is_open())
            {
                cout<<"FILE IS NOT OPENED!";
            }
            else
            {
                while(!fin.eof())
                {
                   getline(fin,line);
                    if(add==line)
                    {
                        check=1;
                        break;
                    }
                    else
                        check=0;
                }
                if(check==0)
                {
                    cout<<"WARNING!! ACCESS DENIED.. UNAUTHORISED DATA MANIPULATION!!"<<endl;
                }
                else
                {
                    c->DataProcess();
                }
            }
       }

   }


};


class KeyBoard:public CU
{
    string address;
    string selectKey;
    string data;
    bool input=1;
    bool output=0;
public:
    KeyBoard()
    {
        address="none";
        selectKey="none";
    }
    KeyBoard(string a)
    {
        address=a;
    }
    void setAddress()
    {
        cout<<"KEYBOARD DEVICE....."<<endl;
        int check=0;
        string line;
        cout<<"Enter the i/o device address:";
        cin>>address;
        ifstream fin("Input_Device.txt");
        if(!fin.is_open())
        {
            cout<<"Device address file not opened!"<<endl;
        }
        else
        {
            while(!fin.eof())
            {
                getline(fin,line);
                if(address==line)
                {
                    cout<<"THIS IS A PRE REGISTRED DEVICE...."<<endl<<"CONNECTION SUCCESSFUL :)"<<endl;
                    check=1;
                    break;
                }
                else
                    check=0;
            }
            fin.close();
            if(check==0)
            {
                ofstream fout("Input_Device.txt",ios::app);
                char choice;
                cout<<"THIS IS AN UNREGISTRED DEVICE. DO YOU WISH TO REGISTER(y/n):";
                cin>>choice;
                if(choice=='y' || choice=='Y')
                {
                    fout<<address<<endl;
                    cout<<"REGISTRED SUCCESSFULLY :)"<<endl;
                }
                else
                {
                    cout<<"DEVICE NOT REGISTERED :("<<endl;
                }
                fout.close();
            }
        }


    }
    void setData()
    {
        cout<<"ENTERING DATA.....";
        cin>>data;
        ofstream fout;
        fout.open("DATA.txt",ios::app);
        if(!fout.is_open())
        {
            cout<<"OOPS! FILE IS NOT OPENED!"<<endl;
            data="none";
        }
        else
        {
            fout<<data<<endl;
            cout<<"DATA IS STORED"<<endl;
            data="none";        //data is cleared after data is stored
        }
        fout.close();
    }
    string getAddress()
    {
        return address;
    }
    void DataProcess()
    {
        setData();
    }

};
class DeskTop:public CU
{
    string address;
    string data;
    bool input=0;
    bool output=1;
public:
    DeskTop()
    {
        address="none";
    }
    DeskTop(string a)
    {
        address=a;
    }
    void setAddress()
    {
        cout<<"DESKTOP DEVICE...."<<endl;
        int check=0;
        string line;
        cout<<"Enter the i/o device address:";
        cin>>address;
        ifstream fin("Output_Device.txt");
        if(!fin.is_open())
        {
            cout<<"Device address file not opened!"<<endl;
        }
        else
        {
            while(!fin.eof())
            {
                getline(fin,line);
                if(address==line)
                {
                    cout<<"THIS IS A PRE REGISTRED DEVICE...."<<endl<<"CONNECTION SUCCESSFUL :)"<<endl;
                    check=1;
                    break;
                }
                else
                    check=0;
            }
            fin.close();
            if(check==0)
            {
                ofstream fout("Output_Device.txt",ios::app);
                char choice;
                cout<<"THIS IS AN UNREGISTRED OUTPUT DEVICE. DO YOU WISH TO REGISTER(y/n):";
                cin>>choice;
                if(choice=='y' || choice=='Y')
                {
                    fout<<address<<endl;
                    cout<<"REGISTRED SUCCESSFULLY :)"<<endl;
                }
                else
                {
                    cout<<"DEVICE NOT REGISTERED :("<<endl;
                }
                fout.close();
            }

        }


    }
    void getData()
    {
            cout<<"THE DATA CURRENTLY IN SYSTEM IS...."<<endl;
            ifstream fin("DATA.txt");
            char ch;
            if(!fin.is_open())
            {
                cout<<"file not opened!!"<<endl;
            }
            else
            {
                while(!fin.eof())
                {
                    fin.get(ch);
                    cout<<ch;
                }
            }
    }
    void  DataProcess ()
    {
        getData();
    }
    string getAddress()
    {
        return address;
    }
};
class Pendrive:public CU
{
    string address;
    string data;
    bool input=1;
    bool output=1;
public:
    Pendrive()
    {
        address="none";
    }
    Pendrive(string a)
    {
        address=a;
    }
    void setAddress()
    {
        cout<<"PENDRIVE DEVICE..."<<endl;
       int check=0;
        string line;
        cout<<"Enter the i/o device address:";
        cin>>address;
        ifstream fin1("Input_Device.txt");
        ifstream fin2("Output_Device.txt");
        if(!fin1.is_open() || !fin2.is_open())
        {
            cout<<"Device address file not opened!"<<endl;
        }
        else
        {
            while(!fin1.eof())
            {
                getline(fin1,line);
                if(address==line)
                {
                    cout<<"THIS IS A PRE REGISTRED DEVICE...."<<endl<<"CONNECTION SUCCESSFUL :)"<<endl;
                    check=1;
                    break;
                }
                else
                    check=0;
            }
            fin1.close();
            char choice;
            if(check==0)
            {
                ofstream fout1("Input_Device.txt",ios::app);

                cout<<"THIS IS AN UNREGISTRED INPUT DEVICE. DO YOU WISH TO REGISTER(y/n):";
                cin>>choice;
                if(choice=='y' || choice=='Y')
                {
                    fout1<<address<<endl;
                    cout<<"REGISTRED SUCCESSFULLY IN INPUT DEVICE :)"<<endl;
                }
                else
                {
                    cout<<"DEVICE NOT REGISTERED IN INPUT IO :("<<endl;
                }
                fout1.close();
            }
            while(!fin2.eof())
            {
                getline(fin2,line);
                if(address==line)
                {
                    cout<<"THIS IS A PRE REGISTRED OUTPUT DEVICE...."<<endl<<"CONNECTION SUCCESSFUL :)"<<endl;
                    check=1;
                    break;
                }
                else
                    check=0;
            }
            fin2.close();
            if(check==0)
            {
                ofstream fout2("Output_Device.txt",ios::app);
                cout<<"THIS IS AN UNREGISTRED DEVICE. DO YOU WISH TO REGISTER(y/n):";
                cin>>choice;
                if(choice=='y' || choice=='Y')
                {
                    fout2<<address<<endl;
                    cout<<"REGISTRED SUCCESSFULLY IN OUTPUT DEVICE:)"<<endl;
                }
                else
                {
                    cout<<"DEVICE NOT REGISTERED IN OUTPUT IO :("<<endl;
                }
                fout2.close();
            }

        }

    }

    string getAddress()
    {
        return  address;
    }
    void DataProcess()
    {
        //it makes the copy of data available in system and put it into pendrive ie) copy and paste
        string line;
        ifstream fin("DATA.txt");
        ofstream fout("pendrive.txt",ios::app);
        if(!fin.is_open() || !fout.is_open())
        {
            cout<<"PENDRIVE AND SYSTEM CONNECTION FAILED"<<endl;
        }
        else
        {
            while(!fin.eof())
            {
                getline(fin,line);
                fout<<line<<endl;
            }
        }
    }
};
//class CPU  HAS A ALU(arithmetic logic unit) AND CU(control unit)
//class CPU
//{
//        ALU a;
//    public:
//        void setAlu()
//        {
//            a.setALU();
//        }
//};
int main()
{
   system("cls");
   system("color 70");
   cout<<"/n/n/n";
   cout<<"/t/t/t/t THIS IS AN REAL LIFE STIMULATION ON HOW THE PERIPHERAL DEVICE ACTUALLY INTERFACES WITH THE PROCESSOR :)"<<endl;
   system("cls");
    char choice;
    int option;
    CU *c;
        Keyboard k;
            do
            {
                cout<<"/t/t/t/t MENU "<<endl;
                cout<<"/t/t1.CREATE CONNECTION WITH KEYBOARD"<<endl;
                cout<<"/t/t2.CREATE CONNECTION WITH DESKTOP"<<endl;
                cout<<"/t/t3.CREATE CONNECTION WITH PENDRIVE"<<endl;
                cout<<"/t/t4.WORKING WITH KEYBOARD?"<<endl;
                cout<<"/t/t5.WORKING WITH DESKTOP?"<<endl;
                cout<<"/t/t6.WORKING WITH PENDRIVE?"<<endl;
                cin>>option;
                switch(option)
                {
                case 1:
                    {

                        assignAddress(&k);
                        break;
                    }
                case 2:
                    {

                        assignAddress(&d);
                        break;
                    }
                case 3:
                    {

                        assignAddress(&p);
                        break;
                    }
                case 4:
                    {
                        assignData(&k);
                        break;
                    }
                case 5:
                    {
                        assignData(&d);
                        break;
                    }
                case 6:
                    {
                        assignData(&p);
                        break;
                    }
                }
                cout<<"DO YOU WANT TO CONTINUE?";
                cin>>choice;
                system("cls");
                if(choice!='y' ||choice!='n')
                    throw("error");

            }while(choice=='y' || choice=='y');
            system("cls");
            cout<<"\n\n\n\n";
            cout<<"/t/t/t/t EXITING YOUR PAGE...."<<endl;

   return 0;
}
