#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cstring>
#include <ctime>
using namespace std;

class Transaction {
    private:
        char type[30];
        double amt;
        int accNo;
        char dateTime[50];
    public:
        void setTransaction(const char t[], double amount, int an) {
            accNo=an;
            strcpy(type, t);
            amt=amount;
            time_t now = time(0);
            strcpy(dateTime, ctime(&now));
        }

        void saveTransaction() {
            ofstream fout("transactions.dat", ios::binary | ios::app);
            fout.write((char*)this, sizeof(*this));
            fout.close();
        }

        void showTransaction(int an) {
            ifstream fin("transactions.dat", ios::binary);
            Transaction t;

            cout<<"\n---TRANSACTION HISTORY---\n";
            while(fin.read((char*)&t, sizeof(t))) {
                if(t.accNo==an) {
                    cout<<"\nTransaction type : "<<t.type;
                    cout<<"\nAmount : "<<t.amt;
                    cout<<"\nDate & Time : "<<t.dateTime;
                    cout<<"\n--------------------\n";
                }
            }
            fin.close();
        }

};
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

            if(customerExist(cId)) {
                cout<<"\n[ERROR] Customer ID already exists.";
                return;
            }
            cout<<"\nEnter your Email ID : ";
            cin.getline(cEmail, 50);

            cout<<"\nEnter your contact number : ";
            cin.getline(cMno, 11);

            ofstream fout("customers.dat", ios::binary | ios::app);
            fout.write((char*)this, sizeof(*this));
            fout.close();

            cout<<"\n[SUCCESS] Customer created successfully.";
            
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
                cout<<"\n[ERROR] Customer ID not found.";
                return;
            }

            cout<<"\nEnter account holder name : ";
            cin.getline(cName, 50);

            cout<<"\nEnter your account number : ";
            cin>>accNo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(accountExist(accNo)) {
                cout<<"\n[ERROR] Account number already exists.";
                return;
            }

            cout<<"\nEnter initial balance : ";
            cin>>balance;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(balance<0) {
                cout<<"\n[ERROR] Balance cannot be negative.";
                return;
            }

            cout<<"\nSet 4 digits pin : ";
            cin>>pin;

            if(pin<1000 || pin>9999) {
                cout<<"\n[ERROR] PIN must contain exactly 4 digits.";
                return;
            }

            ofstream fout("accounts.dat", ios::binary | ios::app);
            fout.write((char*)this, sizeof(*this));
            fout.close();

            cout<<"\n[SUCCESS] Account created successfully.";
        }

        bool accountExist(int no) {
            ifstream fin("accounts.dat", ios::binary);
            Account a;
            while(fin.read((char*)&a, sizeof(a))) {
                if(a.accNo==no) {
                    fin.close();
                    return true;
                }
            }
            fin.close();
            return false;
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

        void depositMoney(double amt) {
            balance+=amt;

            updateAccount();

            Transaction t;
            t.setTransaction("Deposit", amt, accNo);
            t.saveTransaction();

            cout<<"\n[SUCCESS] Amount deposited successfully.";
        }

        void updateAccount() {
            ifstream fin("accounts.dat", ios::binary);
            ofstream fout("temp.dat", ios::binary);

            Account a;
            while(fin.read((char*)&a, sizeof(a))) {
                if(a.accNo==accNo) {
                    fout.write((char*)this, sizeof(*this));
                } else {
                    fout.write((char*)&a, sizeof(a));
                }
            }

            fin.close();
            fout.close();

            remove("accounts.dat");
            rename("temp.dat", "accounts.dat");
        }

        void checkBalance() {
            cout<<"\nYour current balance : "<<balance;
        }

        int getAccNo() {
            return accNo;
        }

        void withdrawMoney(double amt) {

            if(amt>balance) {
                cout<<"\n[ERROR] Insufficient balance.";
                return;
            }
            balance-=amt;
            updateAccount();

            Transaction t;
            t.setTransaction("Withdraw", amt, accNo);
            t.saveTransaction();

            cout<<"\n[SUCCESS] Amount withdrawn successfully.";
        }
        
        void transferMoney() {
            int recAcc;
            cout<<"\nEnter receiver account no : ";
            cin>>recAcc;

            if(recAcc==accNo) {
                cout<<"\n[ERROR] Cannot transfer money to the same account.";
                return;
            }

            double amt;
            cout<<"\nHow much amount you want to transfer : ";
            cin>>amt;

            if(amt<=0) {
                cout<<"\n[ERROR] Amount must be greater than 0.";
                return;
            } 
            if(amt>balance) {
                cout<<"\n[ERROR] Insufficient balance.";
                return;
            }

            ifstream fin("accounts.dat", ios::binary);
            ofstream fout("temp.dat", ios::binary);

            Account a;
            bool find=false;

            while(fin.read((char*)&a, sizeof(a))) {
                if(a.accNo==recAcc) {
                    a.balance+=amt;
                    find=true;
                }
                if(a.accNo==accNo) {
                    balance-=amt;
                    a.balance=balance;
                }
                fout.write((char*)&a, sizeof(a));
            }
            fin.close();
            fout.close();

            if(!find) {
                remove("temp.dat");
                cout<<"\n[ERROR] Receiver account not found.";
                return;
            }

            remove("accounts.dat");
            rename("temp.dat", "accounts.dat");

            Transaction t1, t2;

            t1.setTransaction("Transfer sent", amt, accNo);
            t1.saveTransaction();

            t2.setTransaction("Transfer received", amt, recAcc);
            t2.saveTransaction();
            
            cout<<"\n[SUCCESS] Money transferred successfully.";
            cout<<"\nCurrent balance : "<<balance;
        }

};
void customerMenu(Account &a) {
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
            {
                double amt;
                cout<<"\nHow much amount you want to deposit : ";
                cin>>amt;
                if(amt<=0) {
                    cout<<"\n[ERROR] Amount must be greater than 0.";
                } else {
                    a.depositMoney(amt);
                }
            }
            break;

            case 3:
            {
                double amt;
                cout<<"\nHow much amount you want to withdraw : ";
                cin>>amt;
                if(amt<=0) {
                    cout<<"\n[ERROR] Amount must be greater than 0.";
                } else {
                    a.withdrawMoney(amt);
                }
                break;
            }

            case 4:
            {
                a.transferMoney();
            }
            break;

            case 5:
                a.checkBalance();
            break;

            case 6:
            {   
                Transaction t;
                t.showTransaction(a.getAccNo());
                break;
            }

            case 7:
                cout<<"\n[INFO] Logged out successfully.";
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
                    cout<<"\n[SUCCESS] Login successful.";
                    customerMenu(a);

                } else {
                    cout<<"\n[ERROR] Invalid account number or PIN.";
                }
                break;
            }

            case 4:
                cout<<"\n[INFO] Thank you for using the Banking System.";
            break;

            default:
                cout<<"\nSelect valid choice..!!";
        }

    }while(ch!=4);
    
    return 0;
}