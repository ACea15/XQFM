// #include <iostream>
// #include <fstream>
// using namespace std;
// // Class to define the properties
// class Employee {
// public:
//     string Name;
//     int Employee_ID;
//     int Salary;
// };
// // int main(){
// //     Employee Emp_1;
// //     Emp_1.Name="John";
// //     Emp_1.Employee_ID=2121;
// //     Emp_1.Salary=11000;
// //     Wriring this data to Employee.txt
// //     ofstream file1;
// //     file1.open("Employee.txt", ios::app);
// //     file1.write((char*)&Emp_1,sizeof(Emp_1));
// //     file1.close();
// //     Reading data from EMployee.txt
// //     ifstream file2;
// //     file2.open("Employee.txt",ios::in);
// //     file2.seekg(0);
// //     file2.read((char*)&Emp_1,sizeof(Emp_1));
// //     printf("\nName :%s",Emp_1.Name.c_str());
// //     printf("\nEmployee ID :%d",Emp_1.Employee_ID);
// //     printf("\nSalary :%d",Emp_1.Salary);
// //     file2.close();
// //     return 0;
// // }
// int main(){
//     Employee Emp_1;
//     // Emp_1.Name="John";
//     // Emp_1.Employee_ID=2121;
//     // Emp_1.Salary=11000;

//     ifstream infile;

//     infile.open("Employee.txt");
//     //while (!infile.eof())
//     //{
//     infile >> Emp_1.Name
// 	   >> Emp_1.Employee_ID
// 	   >> Emp_1.Salary;
// 	//}
 
//     infile.close();
//     std::cout << "Name :" << Emp_1.Name;
//     std::cout << "Employee ID :" << Emp_1.Employee_ID;
//     std::cout << "Salary :" << Emp_1.Salary;
    
//     return 0;
// }

//C++ program to write and read object using read and write function.
#include <iostream>
#include <fstream>
 
using namespace std;
 
//class student to read and write student details
class student
{
    private:
        char name[30];
        int age;
    public:
        void getData(void)
        { cout<<"Enter name:"; cin.getline(name,30);
          cout<<"Enter age:"; cin>>age;
        }
 
        void showData(void)
        {
        cout<<"Name:"<<name<<",Age:"<<age<<endl;
        }
};
 
int main()
{
    student s;
     
    ofstream file;
 
    //open file in write mode
    // file.open("aaa.txt",ios::out);
    // if(!file)
    // {
    //   cout<<"Error in creating file.."<<endl;
    //   return 0;
    // }
    // cout<<"\nFile created successfully."<<endl;
 
    // //write into file
    // s.getData();    //read from user
    // file.write((char*)&s,sizeof(s));    //write into file
 
    // file.close();   //close the file
    // cout<<"\nFile saved and closed succesfully."<<endl;
 
    //re open file in input mode and read data
    //open file1
    ifstream file1;
    //again open file in read mode
    file1.open("aaa.txt",ios::in);
    if(!file1){
        cout<<"Error in opening file..";
        return 0;
    }
    //read data from file
    file1.read((char*)&s,sizeof(s));
 
    //display data on monitor
    s.showData();
    //close the file
    file1.close();
     
    return 0;
}
