#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstring>
#include<limits>
using namespace std;

struct Element
{
    int num;
    string  name;
    float price;
    Element *next;
    Element *previous;

};

struct List
{
    int n;
    Element *head;
    Element *tail;
};

List * createEmpty()
{
    List* ls;
    ls = new List();

    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;

    return ls;
}
void insertBegin(List*ls, int newNum, string newName, float newPrice)
{
    Element *e;
    e = new Element();
    //update Element
    e->num = newNum;
    e->name = newName;
    e->price = newPrice;
    e->next = ls->head;
    e->previous = NULL;

    //Update the list(tail)
    if(ls->n==0)
    {
        ls->tail = e;
    }
    // Update the list(head)
    if(ls->n != 0)
    {
        ls->head->previous = e;
    }
    ls->head = e;
    ls->n = ls->n+1;
}
void insertLast(List* ls, int newNum, string newName, float newPrice)
{
    Element *e;

    if(ls->n ==0 )
    {
        insertBegin(ls,newNum,newName,newPrice );
    }
    else
    {
        e = new Element();
        e-> num = newNum;
        e-> name = newName;
        e-> price = newPrice;
        e-> next = NULL;
        e-> previous = ls->tail;

        ls->tail->next = e;
        ls->tail = e;
        ls->n = ls->n+1;
    }
}
void displayList(List *ls)
{
    Element *tmp;
    tmp = ls->head;
    cout<<" N\370\t\tName\t\tPrice($)"<<endl;
    while(tmp != NULL)
    {
        cout<<" "<<tmp->num<<"\t\t"<<tmp->name<<"\t\t"<<tmp->price<< endl;
        tmp = tmp->next;
    }
    cout<<endl;
}
void updateFile(List* ls)
{

    Element *tmp;
    //displayList(ls);
    tmp = ls->head;
    ofstream fileout;
    fileout.open("Coffee data.txt");
    fileout<<"Number,Name,Price\n";

    while(tmp != NULL)
    {
        fileout<<tmp->num<<",";
        fileout<<tmp->name<<",";
        fileout<<tmp->price<<endl;
        tmp = tmp->next;
    }
    fileout.close();
}

void searchDataAndModify(List *ls, int number)
{
    int choice;
    string newName;
    float newPrice;
    Element *temp;
    temp = ls->head;
    int counter=0;
    while(temp != NULL)
    {
        if(temp->num == number)
        {
            counter = counter+1;
            break;
        }
        temp = temp->next;
    }

    if(counter == 0)
    {
        cout<<" Not found!"<<endl;
    }
    else
    {
        cout<<endl;
        cout<<" \tChoose to modify! \n\t 1. Price \n\t 2. Coffee name \n\t 3. Both \n\t Choose: ";
        cin>> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(choice == 1)
        {
            cout<<"\t Enter the new price: ";
            cin>>newPrice;
            temp->price = newPrice;
            updateFile(ls);
        }
        else if(choice ==2)
        {
            cout<<"\t Enter new name: ";
            getline(cin,newName);
            temp->name = newName;
            updateFile(ls);
        }
        else if(choice ==3)
        {
            cout<<endl;
            cout<<"\t Enter new name: ";
            getline(cin,newName);
            cout<<"\t Enter the new price: ";
            cin>>newPrice;
            temp->price = newPrice;
            temp->name = newName;
            updateFile(ls);
        }
        cout<<"\n\n\t Success modify!!\n";
    }
}
void updateNumber(List* ls)
{
    Element* tmp = ls->head;

    for(int i=1 ; i<=ls->n ; i++)
    {
        tmp->num = i;
        tmp = tmp->next;
    }
}
void removeItem(List* ls, int index)
{
    if (index < 0 || index >= ls->n) {
            return;
        }
        Element *curr = ls->head;
        for (int i = 0; i <index; i++) 
        {
            curr = curr->next;
        }

        if (curr->previous != NULL) 
        {
            curr->previous->next = curr->next;
        } 
        else 
        {
            ls->head = curr->next;
        }

        if (curr->next != NULL) 
        {
            curr->next->previous = curr->previous;
        } else {
            ls->tail = curr->previous;
        }
        delete curr;
        ls->n = ls->n-1;
        updateNumber(ls);
        updateFile(ls);

}
int main()
{
    List *ls;
    ls = createEmpty();
    Element *tmp;


    int number,n;
    string name;
    float price;
    int choice;
    int choice2, choice3,choice4;
    string coffeeName;
    float coffeePrice;

    /////////////////////////////////////////////
    // Read from file
    ifstream coffee_data("Coffee data.txt");
    if(!coffee_data.is_open())
    {
        cout<<" Error opening file or file does not exist.\n";
        return 1 ;
    }

    string aline;
    getline(coffee_data, aline);
    int i=0;
    while(getline(coffee_data, aline))
    {
        if(aline == "")
        {
            break;
        }
        else{
                stringstream sstream(aline);
                vector<string> info_Parts;
                string tmp;
                while(getline(sstream, tmp,',')){
                    info_Parts.push_back(tmp);
                }


                number = stoi(info_Parts[0]);
                name = info_Parts[1];
                price = stof(info_Parts[2]);

                insertLast(ls, number, name, price);
        }
        i++;
    }
    coffee_data.close();
    //////////////////////////////

    while(1)
    {
        cout<<" Please Enter the number!\n 1. Display the Coffee data.\n 2. Update the Coffee data. \n 3. Delete Item in Coffee data.\n 4. Exit\n Choose: ";
        cin>>choice;
        if(choice == 1)
        {
            displayList(ls);
        }
        else if(choice == 2)
        {
            cout<<endl;
            cout<<" Please Enter Choice number!"<<endl;
            cout<<" 1. Add data to file.\n 2. Modify Coffee information\n choose: ";
            cin>> choice2;
            //ignore
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(choice2 == 1)
            {
                cout<<"\tName of new Coffee: ";
                //cin>>coffeeName;
                getline(cin,coffeeName);
                //cout<<endl;
                cout<<"\tInsert price: ";
                cin>>coffeePrice;
                number = ls->n+1;
                insertLast(ls, number, coffeeName, coffeePrice);
                updateFile(ls);
                cout<<endl<<"\tAdding coffee information successfully!!"<<endl<<endl;
            }
            else if(choice2 == 2)
            {
                displayList(ls);
                cout<<"\t What number you want to modify?\n\t Answer: ";
                cin>>n;
                searchDataAndModify(ls,n);

            }

        }
        else if(choice == 3)
        {
            //cout<<" The program is under maintenance"<<endl;
            displayList(ls);
            cout<<endl;
            cout<<" What item's number you want to delete?"<<endl<<" Choose: ";
            cin>>choice4;
            removeItem(ls, choice4-1);

        }
        else if(choice == 4)
        {
            cout<<endl;
            cout<<" Exit successfully!\n";
            break;
        }
    }
}
