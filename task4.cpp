#include <iostream>
#include <random>
using namespace std;

class Customer {
    private:
        string customerName, customerMobileNumber, customerEmail;
    
    public:
        void set_Cname(string name) {
            customerName=name;
        }
        void set_Mno(string number) {
            customerMobileNumber=number;
        }
        void set_Email(string email) {
            customerEmail=email;
        }
        string get_Cname() {
            return customerName;
        }
        string get_Mno() {
            return customerMobileNumber;
        }
        string get_Email() {
            return customerEmail;
        }

        void writeObject() {
            string file = customerName + ".txt";
            ofstream fout(file);
        }
};

class Account {
    private:
        long accountNo;
        double accountBalance;
        int PIN;
    
    public:
        Account() {
            accountBalance=0.0;
        }
        void set_AccNo(long number) {
            accountNo=number;
        }
        void set_Balance(double amount) {
            accountBalance=amount;
        }
        void set_PIN(int pin) {
            PIN=pin;
        }
        long get_AccNo() {
            return accountNo;
        }
        double get_Balance() {
            return accountBalance;
        }
        int get_PIN() {
            return PIN;
        }
};

class Transaction {
    
};
int main() {
    // Customer c1;
    // Account a1;
    // Transaction t1;

    cout<<"\n||| WELCOME TO BANKING SYSTEM |||\n";
    int ch;
    do {
        cout<<"\n1. Create Account\n2. Withdraw Money\n3. Deposite Money\n4. Check Balance\n5. Fund Transfer\n6. View Recent Transaction\n0. Exit\n";
        cout<<"Select operation : ";
        cin>>ch;

        if(ch==1) {
            string name;
            cout<<"Enter your name : ";
            cin>>name;

            string number;
            cout<<"Enter your contact number : ";
            cin>>number;

            string email;
            cout<<"Enter your email address : ";
            cin>>email;

            Customer c;
            c.set_Cname(name);
            c.set_Mno(number);
            c.set_Email(email);

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(11111, 99999);
            long accNo = dist(gen);

            int pin;
            cout<<"Enter 4 digit PIN : ";
            cin>>pin;

            Account a;
            a.set_AccNo(accNo);
            a.set_PIN(pin);

            c.writeObject();


        } else if(ch==2) {

        } else if(ch==3) {
            
        } else if(ch==4) {

        } else if(ch==5) {

        } else if(ch==6) {

        } else if(ch==0) {
            cout<<"\nExit\n";
        } else {
            cout<<"\nPlease select valid choice\n";
        }

    }while(ch!=0);

    return 0;
}