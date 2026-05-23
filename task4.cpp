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

        bool login(int an, int PIN) {
            Account a;

            ifstream fin("accounts.dat", ios::binary);
            while(fin.read((char*)&a, sizeof(a))) {
                if(a.accNo==an && a.pin==PIN) {
                    *this=a;
                    fin.close();
                    return true;
                }
            }
            fin.close();
            return false;
        }

        void accountDetails() {
            cout<<"\nAccount holder name : "<<cName;
            cout<<"\nAccount number : "<<accNo;
            cout<<"\nCustomer Id : "<<cId;
            cout<<"\nBalance : "<<balance;
            cout<<"\n4 digit PIN : "<<pin;
        }

};
void customerMenu(Account a) {
    int ch;
    do {
        cout<<"\n\n1. Account Details\n2. Deposit Money\n3. Withdraw Money\n4. Fund Transfer\n5. Check Balance\n6. Transaction History\n7. Logout";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        switch(ch) {
            case 1:
                a.accountDetails();
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            break;

            case 5:
            break;

            case 6:
            break;

            case 7:
                cout<<"\nLogout Successfully !!";
            break;

            default:
                cout<<"Select valid choice...";

        }
    }while(ch!=7);
}
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
            {
                int accNo, pin;
                cout<<"\nEnter your account no : ";
                cin>>accNo;

                cout<<"\nEnter your 4 digit pin : ";
                cin>>pin;

                Account a;

                if(a.login(accNo, pin)) {
                    cout<<"\nSuccessfully logged in into your account";
                    customerMenu(a);

                } else {
                    cout<<"\nInvalid account no or pin !!";
                }
                break;
            }

            case 4:
                cout<<"\nThank you..!! Visit again";
            break;

            default:
                cout<<"\nSelect valid choice..!!";
        }

    }while(ch!=4);
    return 0;
}