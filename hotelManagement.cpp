#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
class hotel
{
	int roomno;
    char sname[20];
    char name[20];
    char gender;
    long long phoneno;
    char address[50];
public:void input()
    {
        ofstream out;
        out.open("customer111",ios::app|ios::out);
        cout<<"\n_______________________________________";
        cout<<"\n Enter surname  : ";cin>>sname;
        cout<<" Enter name : ";cin>>name;
        cout<<" Enter room number  : "; cin>>roomno;
        cout<<" Enter  gender ( M /F ) : "; 
		cin>>gender;
        cout<<" Enter custmor district: ";
        cin>>address;
		cout<<" Enter custmor mobile number : "; 
		cin>>phoneno;
        out<<"\n Name is   :"<<sname<<" "<<name<<"\n room no :" <<roomno<<" "<<"\n gender : "<<gender<<"\n address  :"<<address<<"\n phone number : "<<"," <<phoneno<<endl;
    }
    void output()
    {
        cout<<"\n Name : "<<sname<<" "<<name<<"\n Gender : "<<gender;
		cout<<"\n Room no : "<<roomno;
		cout<<"\n Address  of the student : "<<address ;
		cout<<"\n Mobile number of custmor : "<<phoneno<<"\n\n";
		cout<<"\n--------------------------------------------------";
    }
    int getroomno()
    {
        return roomno;
    }
};
hotel h;
void createf();
void addf();
void displayf();
void displayp();
void modifyf();
void deletef();
fstream out;
int main()
{
    int option;
    cout<<"\n**HOTEL MANAGEMENT SYSTEM***\n";
    while(1)
    {
	cout<<"\n1.CREATE A NEW CUSTOMER RECORD";
	cout<<"\n2. BOOKING A NEW CUSTOMER ROOM ";
	cout<<"\n3. DISPLAY ALL CUSTOMER RECORDS";
	cout<<"\n4. DISPLAY A PARTICULAR RECORD ";
	cout<<"\n5. MODIFY A PARTICULAR RECORD";
	cout<<"\n6. DELETE A PARTICULAR CUSTOMER RECORD ";
	cout<<"\n7. EXIT";
        cout<<" \n \n Enter your option : ";
        cin>>option;
        switch(option)
        {
        case 1:{createf();

                break;}
       case 2:{addf();

                break;}
        case 3:{displayf();

                break;}
        case 4:{displayp();

                break;}
        case 5:{modifyf();

                break;}
        case 6:{deletef();

                break;}
        case 7:{
                exit(0);}
        default:{cout<<" INVALID CHOICE";}
        }
}
}
void createf()
{
	char ch='y';
	out.open("customer1",ios::out| ios::binary);
	while(ch=='y' || ch =='Y')
	{   
	     h.input();
		out.write((char*)&h, sizeof(h));
		cout<<"\n PRESS Y TO CONTINUE OTHERWSE PRESS N TO STOP....[y/n] : ";
		cin>>ch;
	}
	out.close();
}
void addf()
{
    char ch='y';
	out.open("customer1",ios::out|ios::app| ios::binary);
	while(ch=='y' || ch =='Y')
	{   h.input();
		out.write((char*)&h, sizeof(h));
		cout<<" press y to continue and press n to stop.....[y/n] : ";
		cin>>ch;
	}
	out.close();
}
void displayf()
{
    out.open("customer1",ios::in|ios::binary);
        out.read((char *)&h,sizeof(h));
        while(!out.eof())
        {   h.output();
            out.read((char *)&h,sizeof(h));
        }
    out.close();
}
void displayp()
{     out.open("customer1",ios::in|ios::binary);
     int roomnumber;
     int s=0;
    cout<<" roomno ";
    cin>>roomnumber;
        while(out.read((char *)&h,sizeof(h)))
        {
           if(roomnumber==h.getroomno() )
           {
               s=1;
               h.output();
               break;
           }
        }
    if(s==0)
        cout<<" ROOM NUMBER NOT FOUND OR VACANT\n" ;
    out.close();
}
void modifyf()
{
    out.open("customer1",ios::in|ios::out|ios::binary);
    int roomnumber;
    char found='n';
    out.seekg(0);
    cout<<"\n ENTER THE ROOM NUMBER ,YOU WANT TO MODIFY THE DETAILS ";
    cin>>roomnumber;
while(!out.eof())
 {
   int l=out.tellg();
   out.read((char*)&h,sizeof(h));
   if(h.getroomno()==roomnumber)
   {
  h.input();
  found='y';
  out.seekg(l);
  out.write((char*)&h,sizeof(h));
  cout<<"\n THE CUSTOMER RECORD OF  "<<roomnumber<<" IS MODIFIED SUCCESSFULLY\n";
  break;
   }
 }
 if(found=='n') cout<<"\n THE ROOM NUMBER "<<roomnumber<<" IS NOT FOUND OR VACANT\n";
 out.close();
}
void deletef()
{
 int roomnumber;
 int f=0;
  ofstream out("temp",ios::binary);
  ifstream  in("customer1",ios::binary);
  cout<<" ENTER THE ROOM NUMBER,YOU WANT TO DELETE THE RECORD : ";
  cin>>roomnumber;
  while(in.read((char *)&h,sizeof(h)))
  {     if(roomnumber!=h.getroomno() )
        out.write((char *)&h,sizeof(h));
      else
        f=1;
  }
  if(f==1)
      cout<<"CUSTOMER RECORD DELETED SUCCESSFULLY\n";
  else
    cout<<" ROOM NUMBER NOT FOUND OR VACANT\n";
  in.close();out.close();
  remove("customer1");
  rename("temp","customer1");
}
