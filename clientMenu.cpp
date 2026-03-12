#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Part 1 A
const int NUM_BANKS = 4;
string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
double localFees[NUM_BANKS] = {25, 20, 30, 15};
double intlFees[NUM_BANKS] = {150, 125, 200, 100};
double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

// Part 1 B
const int NUM_DENOMINATIONS = 2;
int denominations[NUM_DENOMINATIONS] = {500, 1000};
int billCount[NUM_DENOMINATIONS] = {500, 500}; // Current count of each 


// Part 1 c
vector<string> cardNumbers;
vector<string> encodedPINs;     
vector<double> balances;        
vector<string> userBanks;        
vector<string> accountTypes;    

void addAccount(string card, string pin, double balance, string bank, string type) {

cardNumbers.push_back(card);
encodedPINs.push_back(pin);
balances.push_back(balance);
userBanks.push_back(bank);
accountTypes.push_back(type);

}


// Part 1 D
vector<string> transactionTypes;    
vector<double> transactionAmounts;
vector<double> transactionFees;
vector<int> transactionQuantities;  

void logTransaction(string type, double amount, double fee) {

    bool found = false;

    for (int i = 0; i < transactionTypes.size(); i++) {

        if (transactionTypes[i] == type) {

            transactionAmounts[i] += amount;
            transactionFees[i] += fee;
            transactionQuantities[i]++;
            found = true;
            break;

        }

    }
    
    if (!found) {

        transactionTypes.push_back(type);  
        transactionAmounts.push_back(amount);
        transactionFees.push_back(fee);
        transactionQuantities.push_back(1);
        
    }

}


// Functions
int login();
void clientMenu();
void adminMenu();


// encoding functions
string encodeString(string plain){
    return "encodedPIN: " + plain;
}

bool verifyPIN(string input, string stored){
    return encodeString(input) == stored;
}


// Main function
int main () {
    
    addAccount("1234567890123456", "encodedPIN: 1234", 10000, "BDO", "Local");
    logTransaction("Deposit", 5000, 0);
    
    login();
    
    return 0;
}



//where to do code
int login() {
    int role;

    cout << "======= WELCOME TO ATM SYSTEM =======" << endl;
    cout << "[1] Client Menu" << endl;
    cout << "[2] Admin Menu" << endl;
    cout << "Select Role: ";
    cin >> role;
    cout << "=====================================" << endl;

    if (role == 1){
        clientMenu();
    }
    else if (role == 2){
        adminMenu();
    }
    
    
    return 0;
}


void clientMenu () {

     string card, pin;

    cout << "\nInsert your Card Number: ";
    cin >> card;

    int accountIndex = -1;

        for(int i = 0; i < cardNumbers.size(); i++){
            if(cardNumbers[i] == card){
                accountIndex = i;
                break;
            }
        }

        if(accountIndex == -1){
            cout << "Your card number cannot be found.\n";
            return;
        }

        cout << "Enter your PIN number: ";
        cin >> pin;

        if(encodeString(pin) != encodedPINs[accountIndex]){
            cout << "Wrong PIN number.\n";
            return;
        }

    int choice;

    do{

            cout << "===== CLIENT MENU =====\n";
            cout << "\nBank: " << userBanks[accountIndex];
            cout << "\nAccount Type: " << accountTypes[accountIndex];
            cout << "\nCurrent Balance: PHP*******" << endl;

            cout << "\n1. Check Balance.\n";
            cout << "2. Withdraw.\n";
            cout << "3. Transfer.\n";
            cout << "4. View Transaction History.\n" << endl;

            cout << "5. Change your PIN number.\n";
            cout << "6. Logout\n" << endl;

            cout << "Enter your choice: ";
            cin >> choice;

                if(choice == 1){

                    cout << "===== BALANCE CHECK PANEL =====\n";
                    cout << "\nBalance: " << balances[accountIndex] << endl;

                    cout << "\nPress any key to continue another transaction: ";
                    string temp;
                    cin >> temp;

                }

                if(choice == 2){

                    cout << "===== WITHDRAWAL PANEL =====\n" << endl;

                int wdrawAmount1, wdrawAmount2, amount = 0;

                    cout << "1. 500Php";
                    cout << "      2. 1000Php\n";
                    cout << "3. 5,000Php";
                    cout << "    4. 10,000Php\n";
                    cout << "   5. Enter an Amount." << endl;
                    cout << "\nEnter your choice (1-5): ";
                    cin >> wdrawAmount1;

                        if(wdrawAmount1 == 1){
                            amount = 500;
                        }
                        else if(wdrawAmount1 == 2){
                            amount = 1000;
                        }
                        else if(wdrawAmount1 == 3){
                            amount = 5000;
                        }
                        else if(wdrawAmount1 == 4){
                            amount = 10000;
                        }
                        else if(wdrawAmount1 == 5){
                            cout << "\nEnter amount to Withdraw: ";
                            cin >> wdrawAmount2;
                            amount = wdrawAmount2;
                        }

                    if(amount > balances[accountIndex]){
                        cout << "\nSorry, but you do not have enough Balance.\n";
                        continue;
                    }

                    balances[accountIndex] -= amount;
                    logTransaction("Withdrawal", amount, 0);

                        cout << "Please Wait..." << endl;
                        cout << "\nCollect your cash: PHP " << amount << endl;

                        cout << "\nPress any key to continue: ";
                        string temp;
                        cin >> temp;

                }

                if(choice == 3){

                    string receiver;
                    double amount;

                        cout << "===== TRANSFER PANEL =====\n";

                        cout << "Enter receipient card number: ";
                        cin >> receiver;

                        int receiverIndex = -1;

                        for(int i = 0; i < cardNumbers.size(); i++){
                            if(cardNumbers[i] == receiver){
                                receiverIndex = i;
                                break;
                            }
                        }

                        if(receiverIndex == -1){
                            cout << "Sorry, Recipient not found.\n";
                            continue;
                        }

                        cout << "Enter amount to transfer: ";
                        cin >> amount;

                        if(amount > balances[accountIndex]){
                            cout << "Insufficient balance.\n";
                            continue;
                        }

                        balances[accountIndex] -= amount;
                        balances[receiverIndex] += amount;

                        logTransaction("Transfer", amount, 0);
                        cout << "\nTransfered successfully.\n";
                }

                if(choice == 4){

                        cout << "===== VIEWING TRANSACTION HISTORY =====" << endl;

                        if(transactionTypes.empty()){
                            cout << "Oops, you do not have transactions yet.\n";
                        }

                        for(int i = 0; i < transactionTypes.size(); i++){
                            cout << transactionTypes[i] << " | Amount: " << transactionAmounts[i] << " | Fee: " << transactionFees[i] << " | Count: " << transactionQuantities[i] << endl;
                        }

                        cout << "\nPress any key to continue: ";
                        string temp;
                        cin >> temp;
                    
                }

                if(choice == 5){

                    string oldPIN, newPIN;

                    cout << "Enter your current PIN number: ";
                    cin >> oldPIN;

                    if(encodeString(oldPIN) != encodedPINs[accountIndex]){
                        cout << "Incorrect PIN.\n";
                        continue;
                    }

                    cout << "Enter your NEW PIN number: ";
                    cin >> newPIN;

                    encodedPINs[accountIndex] = encodeString(newPIN);

                    cout << "\nSuccessfully changed your PIN number.\n";

                }

    }while(choice != 6);

    cout << "Logging you out...\n";

}



void adminMenu () {
    
}
