#include<iostream>
#include<fstream>
using namespace std;

int main()
{

    ifstream file("File for delete item.txt");

    if(!file.is_open()){
        cout<<" The file is not exist or error"<<endl;
    }

    string aline;
    getline(file,aline);
    file.close();
   cout<<aline;

    ofstream file2("File for delete item.txt");
     if(!file2.is_open())
     {
         cout<<" The file is not exist or error"<<endl;
     }

    file2<<aline<<endl;
    file2<<"";

    file2.close();

}