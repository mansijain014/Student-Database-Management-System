#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

int main()
{   FILE *fp, *ft;
    char another;
    int choice;
    struct Student
    {
        char fName[20], lName[20], course[100], sec, eNo[10];
    }s;
    char eNumber[10];
    long int recsize;
    fp = fopen("users.txt","rb+");
    if(fp == NULL){
        fp=fopen("users.txt","wb+");
        if(fp==NULL)
        cout<<"\nCannot open file.";
        return 0;
    }
    recsize=sizeof(s);
    do
    {
      cout<<"\nStudent Database Management System";
      cout<<"\n1.Add Records";
      cout<<"\n2.List Records";
      cout<<"\n3.Modify Records";
      cout<<"\n4.Delete Records";
      cout<<"\n5.Exit";
      cout<<"\nEnter your choice: ";
      cin>>choice;
      switch (choice)
      {
      case 1:fseek(fp,0,SEEK_END);
             another='Y';
             while (another=='Y'||another=='y')
             {
                 cout<<"\nEnter First Name: ";
                 cin>>s.fName;
                 cout<<"\nEnter Last Name: ";
                 cin>>s.lName;
                 cout<<"\nEnter Enrollment No.: ";
                 cin>>s.eNo;
                 cout<<"\nEnter Course: ";
                 cin>>s.course;
                 cout<<"\nEnter Section: ";
                 cin>>s.sec;
                 fwrite(&s,recsize,1,fp);
                 cout<<"\nAdd another record?? ";
                 cin>>another;
             }
             break;
      case 2:rewind(fp);
             cout<<"\n**Record List**";
             while (fread(&s,recsize,1,fp)==1)
             {
                 cout<<"\nName: "<<s.fName<<" "<<s.lName;
                 cout<<"\nEnrollment No: "<<s.eNo;
                 cout<<"\nCourse: "<<s.course;
                 cout<<"\nSection: "<<s.sec;
             }
             break;
      case 3:another='Y';
             while (another=='y'||another=='Y'){
                 cout<<"\nEnter the enrollment no. of the student: ";
                 cin>>eNumber;
                 rewind(fp);
                 while (fread(&s,recsize,1,fp)==1)
                 {
                   if(strcmp(eNumber,s.eNo)==0){
                       cout<<"\nEnter new first name: ";
                       cin>>s.fName;
                       cout<<"\nEnter new last name: ";
                       cin>>s.lName;
                       cout<<"\nEnter new enrollment number: ";
                       cin>>s.eNo;
                       cout<<"\nEnter new course: ";
                       cin>>s.course;
                       cout<<"\nEnter new section: ";
                       cin>>s.sec;
                       fseek(fp,-recsize,SEEK_CUR);
                       fwrite(&s,recsize,1,fp);
                       break;
                   } 
                   else
                    {
                        cout<<"\nRecord Not Found!";
                    }   
                 }
                    cout<<"\nModify another record?";
                    cin>>another;  
             }
             break;
      case 4:another='Y';
             while (another=='y'||another=='Y'){
                 cout<<"\nEnter the enrollment no. of the student: ";
                 cin>>s.eNo;
                 ft=fopen("temp.dat","wb+");
                 rewind(fp);
                 while (fread(&s,recsize,1,fp)==1)
                 {
                     if(strcmp(eNumber,s.eNo)==0){
                         fwrite(&s,recsize,1,ft);
                     }
                     fclose(fp);
                     fclose(ft);
                     remove("users.txt");
                     rename("temp.dat","users.txt");
                     fp = fopen("users.txt","rb+");
                 } 
                 cout<<"\nDelete another record? ";
                 cin>>another;
             }
             break;
      case 5:cout<<"\nExited.";
             break;                                             
      default:cout<<"\nWrong Choice Try Again!!";
              break;
      }
    } while (choice!=5);
    
    
    return 0;
}
