#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;
class Customer {
    private:
        int cId;
        char cName[50], cEmail[50], cMno[11];
    public:
        void createCustomer() {
            cout<<"\nEnter your name : ";
            cin.getline(cName, 50);

            cout<<"\nEnter customer ID : ";
            cin>>cId;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"\nEnter your Email ID : ";
            cin.getline(cEmail, 50);

            cout<<"\nEnter your contact number : ";
            cin.getline(cMno, 11);

            ofstream fout("customers.dat", ios::binary | ios::app);
            fout.write((char*)this, sizeof(*this));
            fout.close();

            cout<<"\nCustomer created successfully !!";
        }

};
int main() {
    int ch;
    do {
        cout<<"\n1. Create Customer\n2. Create Account\n3. Login\n4. Exit";
        cout<<"\nSelect Operation : ";
        cin>>ch;
        cin.ignore();
        switch(ch) {
            case 1:
            {
                Customer c;
                c.createCustomer();
                break;
            }
            case 2:
            break;

            case 3:
            break;

            case 4:
                cout<<"\nThank you..!! Visit again";
            break;

            default:
                cout<<"\nSelect valid choice..!!";
        }

    }while(ch!=4);
    return 0;
}