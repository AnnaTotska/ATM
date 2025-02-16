#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Transaction {
    string type;
    double amount;
    double balanceAfter;
    string date;
};

class Account {
private:
    string accountHolder;
    string pin;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string name, string pinCode) : accountHolder(name), pin(pinCode), balance(0) {}


    void displayAccountDetails() {
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }

    void checkBalance() {
        cout << "Current balance: $" << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        recordTransaction("Deposit", amount);
        cout << "$" << amount << " deposited successfully." << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= amount;
            recordTransaction("Withdrawal", amount);
            cout << "$" << amount << " withdrawn successfully." << endl;
        }
    }

    void changePin(string newPin) {
        pin = newPin;
        cout << "PIN changed successfully." << endl;
    }

    void transactionHistory() {
        cout << "Transaction History:" << endl;
        for (const auto& t : transactions) {
            cout << t.date << " - " << t.type << ": $" << t.amount
                 << ", Balance After: $" << t.balanceAfter << endl;
        }
    }

    bool verifyPin(string inputPin) {
        return inputPin == pin;
    }

    void recordTransaction(string type, double amount) {
        time_t now = time(0);
        char* dt = ctime(&now);

        Transaction t;
        t.type = type;
        t.amount = amount;
        t.balanceAfter = balance;
        t.date = string(dt);
        transactions.push_back(t);
    }
};

Account* createAccount() {
    string name, pin;
    cout << "Enter Account Holder's Name: ";
    cin >> name;
    cout << "Set your PIN (4 digits): ";
    cin >> pin;
    Account* newAccount = new Account(name, pin);
    cout << "Account created successfully!" << endl;
    return newAccount;
}

void atmOperations(Account* account) {
    string enteredPin;
    int choice;
    bool isAuthenticated = false;

    while (!isAuthenticated) {
        cout << "Enter your PIN: ";
        cin >> enteredPin;
        if (account->verifyPin(enteredPin)) {
            isAuthenticated = true;
        } else {
            cout << "Incorrect PIN. Try again!" << endl;
        }
    }

    do {
        cout << "\nATM Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Change PIN\n";
        cout << "5. View Transaction History\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            account->checkBalance();
            break;
        case 2: {
            double depositAmount;
            cout << "Enter deposit amount: $";
            cin >> depositAmount;
            account->deposit(depositAmount);
            break;
        }
        case 3: {
            double withdrawAmount;
            cout << "Enter withdrawal amount: $";
            cin >> withdrawAmount;
            account->withdraw(withdrawAmount);
            break;
        }
        case 4: {
            string newPin;
            cout << "Enter new PIN (4 digits): ";
            cin >> newPin;
            account->changePin(newPin);
            break;
        }
        case 5:
            account->transactionHistory();
            break;
        case 6:
            cout << "Thank you for using the ATM. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 6);
}

int main() {
    Account* account = nullptr;
    int actionChoice;

    cout << "Welcome to the ATM!\n";
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Create a New Account\n";
        cout << "2. Use Existing Account\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> actionChoice;

        switch (actionChoice) {
        case 1:
            if (account != nullptr) {
                cout << "Account already exists. Use existing account.\n";
                break;
            }
            account = createAccount();
            break;
        case 2:
            if (account != nullptr) {
                atmOperations(account);
            } else {
                cout << "No account found. Please create an account first.\n";
            }
            break;
        case 3:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (actionChoice != 3);

    delete account; 
    return 0;
}
