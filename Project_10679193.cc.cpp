#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
void Administrator();
void Staff();
void Student();
void bye();
void ViewRecords();
void AddStaff();
void AddStudent();
void DismissStaff();
void DismissStudent();
void AssignGrade();
void AssignCourse();
void RemoveCourse();
string password  ;

int main()
{
    int role;
    while(1)
    {
    role = 0;
    cout<<"\n                       SCHOOL MANAGEMENT SYSTEM                        "<<endl;
    cout<<"Welcome!"<<"\nThis system uses files to store data of students and staffs"<<endl;
    cout<<"There are three roles here"<<endl<<"--->"<<endl;
    cout<<"1. Administrator"<<endl<<"2. Staff"<<endl<<"3. Student"<<endl;
    cout<<"Whats your role?\nEnter the number corresponding to your role or press 0 to exit: ";
    cin>>role;
    switch(role)
    {
        case 1: Administrator();
                break;
        case 2: Staff();
                break;
        case 3: Student();
                break;
        case 0: bye();
        default: cout<<"\nOops that role doesn't match anyone, please try again"<<endl;        
    }
    }
    return 0;
}

void Administrator()
{
    int choice;
    while(1)
    {
    choice = 0;
    cout<<"----------------------------------------------------------------\n";
    cout<< "Enter password for administrator " << endl;
    cin >> password ;
    cout<<"\n\nWelcome  Administrator, what would you like to do today?"<<endl<<"--->"<<endl;
    cout<<"1. View student academic records"<<endl;
    cout<<"2. Add a Staff"<<endl;
    cout<<"3. Add a Student"<<endl;
    cout<<"4. Dismiss a Staff"<<endl;
    cout<<"5. Dismiss a Student"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"\nYour choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1: ViewRecords();
                break;
        case 2: AddStaff();
                break;
        case 3: AddStudent();
                break;
        case 4: DismissStaff();
                break;
        case 5: DismissStudent();
                break;
        case 0: bye();

        default: cout<<"Invalid input, please try again"<<endl;
    }
    }
}

void Staff()
{
    int choice;
    while(1)
    {
    choice = 0;
    cout<<"----------------------------------------------------------------\n";
    cout<<"\n\nWelcome Staff, what would you like to do today?"<<endl<<"--->"<<endl;
    cout<<"1. View student academic records"<<endl;
    cout<<"2. Grade a student"<<endl;
    cout<<"3. Assign a course to a student"<<endl;
    cout<<"4. Remove a course for a student"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"\nYour choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1: ViewRecords();
                break;
        case 2: AssignGrade();
                break;
        case 3: AssignCourse();
                break;
        case 4: RemoveCourse();
                break;
        case 0: bye();

        default: cout<<"Invalid input, please try again"<<endl;
    }
    }
}

void Student()
{
    int choice = 0;
    cout<<"\n\nWelcome Student, what would you like to do today?"<<endl<<"--->"<<endl;
    cout<<"1. Subscibe to a new course"<<endl;
    cout<<"2. Unsubscibe from a course"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"\nYour choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1: AssignCourse();
                break;
        case 2: RemoveCourse();
                break;
        case 0: bye();

        default: cout<<"Invalid input, please try again"<<endl;
    }
}

void ViewRecords()
{
    char name[20], name_cpy[20];
    string readname;
    int count;
    cout<<"\nEnter the name of the student: ";
    cin>>name;
    strcpy(name_cpy, name);
    fstream file;
    file.open(strcat(name, ".txt"));
    if(!file)
    {
    cout<<"Student with this name doesnt exist, please add the student first"<<endl;
    return;
    }
    
    if(file.is_open())
    {
    while(!getline(file, readname).eof())
    
        cout<<readname<<endl;;
    }
    else
    cout<<"Unable to open file"<<endl;
    file.close();
}

void AddStaff()
{
    char name[20], name_cpy[20], choice;
    int age;
    bool val;
    strcpy(name_cpy, name);
    fstream file("teachers.txt");
    if(file.good())
    val = 1;
    file.close();
    file.open("teachers.txt", fstream :: app);
    if(!val)
    file<<"Name\t\tAge"<<endl;
    do
    {
        cout<<"Enter name (use _ for representing spaces): ";
        cin>>name;
        cout<<"Enter age: ";
        cin>>age;
        file<<name<<"\t\t"<<age<<endl;
        cout<<"Enter y to continue adding names or n to stop: ";
        cin>>choice;
    }while(choice != 'n');
}

void AddStudent()
{
    char name[20], name_cpy[20], course_name[20], grade, choice;
    int age;
    cout<<"Enter student name (use _ for representing spaces): ";
    cin>>name;
    strcpy(name_cpy, name);
    cout<<"\nEnter age: ";
    cin>>age;
    fstream file;
    file.open(strcat(name_cpy, ".txt"), fstream :: out);
    file<<"Name: "<<name<<endl;
    file<<"Age: "<<age<<endl;
    file<<"Course\t\tGrade"<<endl;
    do
    {
        cout<<"\nEnter course name (use _ for representing spaces): ";
        cin>>course_name;
        cout<<"\nEnter grade: "<<endl;
        cin>>grade;
        grade = toupper(grade);
        file<<course_name<<"\t\t"<<grade<<endl;
        cout<<"Press y to enter more courses or n to return: ";
        cin>>choice;
    }while(choice != 'n');
    file.close();
}

void DismissStaff()
{
    string readline, name;
    cout<<"Enter staff name (use _ for representing spaces): ";
    cin>>name;
    fstream file("teachers.txt", fstream :: in | fstream :: out);
    ofstream temp("temp.txt");
    while(getline(file, readline))
    {
        if(readline.find(name))
        temp<<readline<<endl;
    }
    file.close();
    remove("teachers.txt");
    temp.close();
    rename("temp.txt", "teachers.txt");
}

void DismissStudent()
{
    char name[20];
    cout<<"Enter student name (use _ for representing spaces): ";
    cin>>name;
    if(remove(strcat(name, ".txt")) != 0)
    cout<<"Student not found, please add student first"<<endl;
    else
    cout<<"Student Dismissed!"<<endl;
}

void AssignCourse()
{
    char name[20], name_cpy[20];
    char course_name[20], grade;
    cout<<"Enter student name (use _ for representing spaces): ";
    cin>>name;
    strcpy(name_cpy, name);
    fstream file(strcat(name, ".txt"));
    if(!file.good())
    {
        cout<<"Student doesn't exist, please add"<<endl;
        file.close();
        return;
    }
    file.close();
    cout<<"Enter course name";
    cin>>course_name;
    cout<<"Enter grade";
    cin>>grade;
    grade = toupper(grade);
    file.open(name, fstream :: app);
    file<<course_name<<"\t\t"<<grade<<endl;
    cout<<"Done Adding!"<<endl;
}

void AssignGrade()
{
    char name[20], name_cpy[20], grade;
    string course_name, readline;
    cout<<"Enter student name (use _ for representing spaces): ";
    cin>>name;
    strcpy(name_cpy, name);
    fstream file(strcat(name, ".txt"), fstream :: in | fstream :: out);
    if(!file.good())
    {
        cout<<"Student doesn't exist, please add"<<endl;
        file.close();
        return;
    }

    cout<<"Enter course name (use _ for representing spaces): "<<endl;
    cin>>course_name;
    while(file.eof())
    {
        getline(file, readline);
        if(!readline.find(course_name))
        {
            cout<<"Student doesn't have this course"<<endl;
            file.close();
            return;
        }
    }
    cout<<"Enter grade: ";
    cin>>grade;
    grade = toupper(grade);
    ofstream temp("temp.txt");
    while(getline(file, readline))
    {
        if(readline.find(course_name))
        temp<<readline<<endl;
        else
        temp<<course_name<<"\t\t"<<grade<<endl;
    }
    file.close();
    remove(name);
    temp.close();
    rename("temp.txt", name);
    cout<<"Done Grading!"<<endl;
}

void RemoveCourse()
{
    char name[20], name_cpy[20];
    string course_name, readline;
    cout<<"Enter student name (use _ for representing spaces): ";
    cin>>name;
    strcpy(name_cpy, name);
    fstream file(strcat(name, ".txt"));
    if(!file.good())
    {
        cout<<"Student doesn't exist, please add"<<endl;
        file.close();
        return;
    }
    file.close();
    cout<<"Enter course name";
    cin>>course_name;
    file.open(name, fstream :: in | fstream :: out);
    ofstream temp("temp.txt");
    while(getline(file, readline))
    {
        if(readline.find(course_name))
        temp<<readline<<endl;
    }
    file.close();
    remove(name);
    temp.close();
    rename("temp.txt", name);
    cout<<"Done Removing!"<<endl;
}

void bye()
{
    cout<<"\n\n              See you soon            "<<endl;
    exit(0);
}
