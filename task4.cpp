#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;
class Customer {
    private:
        int cId;
        char cName[50];
        char cEmail[50];
        char cMno[11];
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

        bool customerExist(int ID) {
            Customer c;
            ifstream fin("customers.dat", ios::binary);
            while(fin.read((char*)&c, sizeof(c))) {
                if(c.cId==ID) {
                    fin.close();
                    return true;
                }
            }
            fin.close();
            return false;
        }

};

class Account {
    private:
        int pin;
        int accNo;
        double balance;
        int cId;
        char cName[50];

    public:
        void createAccount() {
            Customer c;

            cout<<"\nEnter customer ID : ";
            cin>>cId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(!c.customerExist(cId)) {
                cout<<"\nCustomer not exists";
                return;
            }

            cout<<"\nEnter account holder name : ";
            cin.getline(cName, 50);

            cout<<"\nEnter your account number : ";
            cin>>accNo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"\nEnter initial balance : ";
            cin>>balance;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"\nSet 4 digits pin : ";
            cin>>pin;

            ofstream fout("accounts.dat", ios::binary | ios::app);
            fout.write((char*)this, sizeof(*this));
            fout.close();

            cout<<"\nAccount created successfully !!";
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
            {
                Account a;
                a.createAccount();
                break;
            }

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