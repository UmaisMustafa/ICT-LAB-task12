#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Account {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;
    vector<string> transactionHistory;

public:
    Account(string accNum, string holderName, double bal) 
        : accountNumber(accNum), accountHolderName(holderName), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back("Deposited: " + to_string(amount) + ". New Balance: " + to_string(balance));
    }

    virtual bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        transactionHistory.push_back("Withdrew: " + to_string(amount) + ". New Balance: " + to_string(balance));
        return true;
    }

    void displayTransactionHistory() {
        cout << "Transaction History for " << accountHolderName << ":" << endl;
        for (const auto &t : transactionHistory) {
            cout << t << endl;
        }
    }

    virtual void displayDetails() {
        cout << "Account Number: " << accountNumber 
             << ", Account Holder: " << accountHolderName 
             << ", Balance: " << fixed << setprecision(2) << balance << endl;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string holderName, double bal, double rate) 
        : Account(accNum, holderName, bal), interestRate(rate) {}

    double calculateInterest() {
        return balance * interestRate / 100;
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(string accNum, string holderName, double bal, double limit) 
        : Account(accNum, holderName, bal), overdraftLimit(limit) {}

    bool withdraw(double amount) override {
        if (amount > balance + overdraftLimit) {
            cout << "Overdraft limit exceeded!" << endl;
            return false;
        }
        balance -= amount;
        transactionHistory.push_back("Withdrew: " + to_string(amount) + ". New Balance: " + to_string(balance));
        return true;
    }
};

int main() {
    SavingsAccount savings("SA123", "Alice", 1000, 5.0);
    CurrentAccount current("CA456", "Bob", 2000, 500);

    savings.deposit(500);
    savings.withdraw(300);

    current.deposit(1000);
    current.withdraw(2700);

    cout << "\nSavings Account Interest: " << savings.calculateInterest() << endl;

    cout << "\nSavings Account Details:" << endl;
    savings.displayDetails();
    savings.displayTransactionHistory();

    cout << "\nCurrent Account Details:" << endl;
    current.displayDetails();
    current.displayTransactionHistory();

    return 0;
}

