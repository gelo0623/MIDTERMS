#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

    void clearScreen(){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void typeText(string text){
        for(char c : text){
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

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


// Admin
vector<string> adminUsers = {""};


// Part 1 c i move raw sabi sa part 5




void addAccount(vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,     
vector<string>& userBanks,        
vector<string>& accountTypes,
string card, string pin, double balance, string bank, string type) {

cardNumbers.push_back(card);
encodedPINs.push_back(pin);
balances.push_back(balance);
userBanks.push_back(bank);
accountTypes.push_back(type);

}


// Part 1 D i move raw sabi sa part 5

void logTransaction(vector<string>& transactionTypes,    
vector<double>& transactionAmounts,
vector<double>& transactionFees,
vector<int>& transactionQuantities,
const string& cardNum, const string& type, double amount, double fee) {

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
    
    // PART 7 BONUS 
    ofstream file("transaction.csv", ios::app); 
    if (file.is_open()){
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        
        file << (timeinfo->tm_mon + 1) << "/" << timeinfo->tm_mday << "/" << (timeinfo->tm_year + 1900) << "," << timeinfo->tm_hour << ":" << timeinfo->tm_min << "," << cardNum << "," << type << "," << amount << "," << fee << endl;
        file.close();
    }
    else {
        cerr << "Error: Could not open transaction.csv" << endl;
    }

}

// I HATTE PART 5, sinisira code namin TwT


// Overloading function
void logTransaction(vector<string>& transactionTypes,    
vector<double>& transactionAmounts,
vector<double>& transactionFees,
vector<int>& transactionQuantities,
const string& cardNum, const string& type, double amount) {
    
    logTransaction(transactionTypes, transactionAmounts, transactionFees,
    transactionQuantities, cardNum, type, amount, 0);
}


// Functions PART 5 
int login(vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,     
vector<string>& userBanks,        
vector<string>& accountTypes,    
vector<string>& transactionTypes,    
vector<double>& transactionAmounts,
vector<double>& transactionFees,
vector<int>& transactionQuantities);


void clientMenu(vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,        
vector<string>& userBanks,        
vector<string>& accountTypes,    
vector<string>& transactionTypes,    
vector<double>& transactionAmounts,
vector<double>& transactionFees,
vector<int>& transactionQuantities);


void adminMenu(vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,        
vector<string>& userBanks,        
vector<string>& accountTypes);

vector<string> admin = {"Mark Angelo C. Panis | Benedict B. Eborde | Lee Mhiguel Ferrer"};
vector<string> adminUser = {"admin"};
string adminPasscode = "6767";

// =======PART 6========= //

// Recursive function to calculate number of bills for a given amount
void calculateBills(double amount, int& bills1000, int& bills500) {
    if (amount >= 1000){
        bills1000++; //idk why 5000 sayo sir
        calculateBills(amount - 1000, bills1000, bills500);
    }

    else if (amount >= 500) {
        bills500++;
        calculateBills(amount - 500, bills1000, bills500);
    }

}



// DATE AND FRICKING TIME 
void displayDateTime() {
    time_t now = time(0);
    tm* timeinfo = localtime(&now); 

    cout << "Date: " << (timeinfo->tm_mon + 1) << "/" << timeinfo->tm_mday << "/" << (timeinfo->tm_year + 1900);
    cout << " Time: " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl;
}




// encoding functions
string encodeString(string plain){
    return "encodedPIN: " + plain;
}

bool verifyPIN(string input, string stored){
    return encodeString(input) == stored;
}


// Main function
int main () {
    
    vector<string> cardNumbers;
    vector<string> encodedPINs;     
    vector<double> balances;        
    vector<string> userBanks;        
    vector<string> accountTypes;    
    vector<string> transactionTypes;    
    vector<double> transactionAmounts;
    vector<double> transactionFees;
    vector<int> transactionQuantities;

    addAccount(cardNumbers, encodedPINs, balances, userBanks, accountTypes, "1234567890123456", "encodedPIN: 1234", 10000, "BDO", "Local");
    logTransaction(transactionTypes, transactionAmounts, transactionFees,
    transactionQuantities, cardNumbers[0], "Deposit", 5000, 0);
    
    login(cardNumbers, encodedPINs, balances, userBanks, accountTypes,
    transactionTypes, transactionAmounts, transactionFees, transactionQuantities);


    // Part 6 Fstream clear shinanigans Vector Clear
    cardNumbers.clear();
    encodedPINs.clear();
    balances.clear();
    userBanks.clear();
    accountTypes.clear(); 
    transactionTypes.clear();
    transactionAmounts.clear();
    transactionFees.clear();
    transactionQuantities.clear();
    
    return 0;
}



//where to do code
int login(vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,     
vector<string>& userBanks,        
vector<string>& accountTypes,    
vector<string>& transactionTypes,    
vector<double>& transactionAmounts,
vector<double>& transactionFees,
vector<int>& transactionQuantities){
    
    int role;
    clearScreen();

    do{
        clearScreen();
        cout << "====================================" << endl;
        cout << "====================================" << endl;
        typeText("===       ABM BANK MACHINE       ===\n");
        typeText("===         -------------        ===\n");
        typeText("===          ATM MACHINE         ===\n");
        cout << "====================================" << endl;
        cout << "====================================" << endl;
        
        typeText("\n======= WELCOME TO ABM ATM SYSTEM =======");
        cout << "\n[1] Client Menu";
        cout << "    [2] Admin Menu\n";
        cout << "\n            [3] Exit" << endl;
        cout << "\nSelect Role: ";
        cin >> role;

        if (role == 1){
            clientMenu(cardNumbers, encodedPINs, balances,
            userBanks,accountTypes, transactionTypes, transactionAmounts,
            transactionFees, transactionQuantities);
        }
        else if (role == 2){
            string pass;

            cout << "\nEnter Admin Password: ";
            cin >> pass;

            if(pass == adminPasscode){
                adminMenu(cardNumbers, encodedPINs,
                balances, userBanks, accountTypes);
            }
            else{
                cout << "\nWrong Password.\n";

                cout << "\nPress any key to continue: ";
                string temp;
                cin >> temp;
            }
        }
        else if (role == 3){
            clearScreen();
            typeText("Thank You for using our ATM Machine.\n");
            typeText("\nCreated by: Panis, Eborde, Ferrer.");
            typeText("\n()==============[]==================================>>>>");
            
            cout << R"( ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣮⡾⣫⠛⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤⡄⡄⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣮⡿⠋⡌⢁⡀⠼⠖⠒⠒⠒⠒⠂⠢⠤⠄⠄⠀⠀⠀⠄⠄⣀⡀⠀⠀⠀⠀⠀⠀⠀⡇⠇⡇⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡴⠒⢶⣿⢟⠕⠜⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠢⣄⠀⠀⠀⠀⠇⠀⡈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠋⢀⣴⠟⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀⠀⢸⢻⠖⠒⠒⠦⡀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢤⠣⣤⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡳⡀⠀⠀⢸⢸⡇⠀⠀⠀⠘⣆⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠘⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣤⡀⠃⠹⡆⢰⢸⢸⠘⠀⠀⠀⠀⠘⡄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡗⣄⡄⣇⢺⢺⢸⠳⣄⠀⠀⠀⠀⢹⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠋⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⢀⢳⠀⠀⠀⠀⠀⠀⠀⠀⣞⢏⠿⠶⡴⣏⠙⢧⠀⠀⠀⠀⠀⠘⣷⠿⢿⡾⣸⢸⡸⣿⣿⡄⠀⠀⠀⠀⢧⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢇⠂⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⣆⡀⣯⡡⠀⠀⠀⠀⠀⠀⣻⣥⣢⣴⣽⣟⣠⡼⠀⠀⠀⠀⠀⠀⡿⠒⢠⣸⢿⣿⣟⠉⠈⡇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡮⢾⠀⠀⠀⠀⠀⠀⠀⡔⢹⡀⠀⠀⠹⢁⡇⠙⠶⣂⠀⠀⠠⡏⡂⠀⣡⣿⣿⣷⣞⢿⠷⡀⢠⡀⠀⠀⣿⠀⠈⢻⣾⣿⢿⠀⠀⡇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⢺⢧⠀⠀⠀⡜⡄⡜⠀⠀⢃⠀⠀⢀⡞⣻⠀⠀⠈⠓⢄⡈⠳⠤⠾⡝⠛⠿⣨⣿⠃⢙⡟⠰⢣⠀⠀⠘⣟⣆⡜⡏⡟⣾⠀⠀⣇⡄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⢸⣞⠦⡀⡰⠃⣷⠃⠀⠀⠘⢇⠀⠀⢧⣏⠀⠀⠀⠀⠀⠙⢦⡀⠀⢧⢀⠄⣸⠋⠉⠉⠀⠀⠈⠇⠀⢼⣿⡟⠃⠉⣤⡟⠁⠀⣿⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢻⡏⡠⠟⡇⠀⠉⠀⠀⠄⡄⠘⡎⣆⠸⡸⡀⠀⠀⠀⠀⠀⠀⠈⠢⣌⠉⠛⠁⢀⣠⠄⡴⠛⡆⡀⢠⣿⠇⠀⢀⢼⣾⣿⡀⠀⢹⣇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⡇⠀⣧⠓⠀⡇⠀⠀⣰⠢⠐⠹⣄⠘⢆⠀⠁⢣⡄⠀⠀⠀⠀⠀⠀⣠⠈⠙⢄⡀⠘⣧⣸⣶⣷⡏⣷⣾⣿⣆⡀⢸⣿⣿⠏⠀⠀⢸⣿⡀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⠀⢀⣯⡀⠀⣅⠀⠰⣯⣤⣀⠀⠈⠓⠄⠣⡀⠈⢳⡆⠀⢀⣀⣤⠞⠁⠀⠀⠀⠙⢾⡦⠽⣛⣋⡟⢉⣿⣿⠟⢠⢾⡿⢿⠀⠀⠀⢸⣿⡃⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠁⠀⣼⣼⡦⠀⠘⠀⠀⡟⠈⠻⢷⣦⡀⠀⠀⠈⠲⢔⣣⠀⠀⠁⠀⠀⣀⣀⣤⣴⡆⠈⠙⣦⣌⠉⠀⣸⣿⣷⣶⠋⠀⠀⠘⣆⡀⠀⠈⣿⣧⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣰⠃⠀⢰⣿⣿⣿⣄⠀⢃⠀⡇⠀⣄⣤⣿⠿⠒⠀⠀⠀⠀⠉⠀⠀⣤⣶⣿⠿⠛⠛⠉⠀⠀⢰⣿⣿⣿⡖⢸⣟⠉⠛⠀⢀⠀⠀⢺⡟⠀⠀⢿⣿⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⢰⡟⣿⣿⣿⣿⣧⠸⡎⡇⣟⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⢷⣶⣄⣀⠀⠀⣾⠛⢨⣿⡷⠼⠁⠀⠀⢠⣼⣤⢠⡿⠁⠀⠀⢸⣿⣇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢰⠏⠀⢀⣿⣿⣿⣿⣿⣿⣿⣧⡼⣿⠈⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣨⣽⡛⠀⣸⣿⢢⣾⣿⣿⡆⠀⢀⣀⣱⢍⢷⠏⠁⠀⠀⠀⠘⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⢠⡿⡄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣿⣍⠀⠀⠀⣤⣀⠀⣀⣀⢀⣀⡀⠀⠀⠀⢏⡀⣀⣽⢶⣿⣿⣿⣿⣿⠇⠀⠀⠘⠋⠉⡰⠊⠀⠀⠀⠀⠀⠀⢻⡝⣇⠀⠀
⠀⠀⠀⠀⢰⣯⣿⢀⣞⢁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⡏⣯⡖⢦⡼⠊⠉⠙⠛⣿⠛⠁⠀⠀⢀⢈⣉⡭⠖⢻⣿⣿⣟⣛⣷⣤⠤⠖⠘⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⢸⡴⢽⠀⠀
⠀⠀⠀⣰⣟⢯⢣⠿⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢸⢹⣕⣀⣼⠎⠀⢀⠀⠀⠀⠘⣷⠞⠻⢿⣿⣧⣄⠀⠀⠛⠋⠀⠉⠛⠺⠿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⡇⠀
⠀⠀⣰⠟⡻⢣⡯⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡿⣥⣾⠊⢷⢛⣀⣼⠞⠿⠷⡆⠀⠠⣹⣿⣦⣼⣿⣿⡿⢿⠷⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⢹⠀
⠀⠀⢃⡴⢡⢏⡀⠰⢟⣿⣿⣿⣿⣿⣿⡟⢼⣱⢳⣏⠀⣸⣾⡋⡁⠀⠀⠀⠉⣇⢠⣼⠟⠋⠻⣭⡻⣬⠋⠀⠘⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠘⡆
⠀⠀⡺⣡⡿⠁⠀⠀⣸⣿⣿⣿⣿⣿⣿⠇⣾⣾⣾⡝⠀⢸⣿⣿⣿⣶⣶⣶⣾⣿⠟⠀⠀⠀⠰⢻⢣⣿⣦⠀⠀⣼⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⡇
⠀⡀⢡⠟⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⡀⣿⣧⡳⣝⢀⣸⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⢠⢧⣿⣿⣿⣦⣤⣼⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠀⠀⠀
⠈⠀⠿⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⠿⠉⠃⣻⡧⠙⢬⡻⠿⠿⣿⣷⣿⣿⡿⣿⢟⡹⢦⣠⠔⣋⠼⠸⣿⣿⣿⣿⣷⣾⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀
⠀⠈⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⡏⠀⠀⠀⢼⣳⡈⠙⠿⢁⣽⣿⣿⣿⠟⠁⠳⣜⡲⢚⠵⠊⠁⠀⠔⠹⠻⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⡿⠁⠀⠀⠀⠀⣾⢫⢧⣀⣬⠟⢋⣗⡶⠏⠹⢦⡀⢺⣿⠟⠒⠤⣀⠀⠀⢤⣤⣼⣿⠻⣽⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⣸⣿⣸⠀⡰⠋⠀⡜⢹⡇⣀⣰⠞⠁⣸⣏⠀⠀⠀⠀⠉⠒⠻⢿⣿⠿⠖⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⡇⡿⠋⠀⠀⣠⣜⣾⣏⣉⣿⣶⡾⢟⡋⠀⠀⠀⠀⠀⠀⠀⠈⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⢺⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣹⡇⠷⣯⣷⢤⣿⣿⣽⣿⢿⣿⢿⠿⣻⣜⣧⡀⢀⣀⣠⣴⣶⣾⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠇⠀⠀⠀
            
            )";
            
            
            return 3;
        }
        else {
            clearScreen();
            cout << "Invalid Choice!";
        }

    }
    while(role != 3);

    return role;

}


void clientMenu (vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,        
vector<string>& userBanks,        
vector<string>& accountTypes,    
vector<string>& transactionTypes,    
vector<double>& transactionAmounts,
vector<double>& transactionFees,
vector<int>& transactionQuantities) {

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
            clearScreen();
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
            clearScreen();
            cout << "===== CLIENT MENU =====" << endl;
            cout << "Bank: " << userBanks[accountIndex] << endl;
            cout << "Account Type: " << accountTypes[accountIndex] << endl;
            cout << "Current Balance: " << balances[accountIndex] << endl;
            
            displayDateTime();
            
            cout << "\n1. Check Balance." << endl;
            cout << "2. Withdraw." << endl;
            cout << "3. Transfer." << endl;
            cout << "4. View Transaction History." << endl;
            cout << "5. Change your PIN number." << endl;
            cout << "6. Logout" << endl;
            cout << "======================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

                if(choice == 1){
                    clearScreen();
                    cout << "===== BALANCE CHECK PANEL =====\n";
                    cout << "\nBalance: " << balances[accountIndex] << endl;
                    
                

                    cout << "\nPress any key to continue another transaction: ";
                    string temp;
                    cin >> temp;

                }

                if(choice == 2){
                    clearScreen();
            
            cout << "===== WITHDRAWAL PANEL =====\n" << endl;
            
            int wdrawAmount1, wdrawAmount2, amount = 0;
            
            cout << "[1.] 500Php";
            cout << "      [2.] 1000Php\n";
            cout << "[3.] 5,000Php";
            cout << "    [4.] 10,000Php\n";
            cout << "   [5.] Enter an Amount." << endl;
            cout << "\nEnter your choice (1-5): ";
            cin >> wdrawAmount1;
            
            
            
            if(wdrawAmount1 == 1) amount = 500;
            else if(wdrawAmount1 == 2) amount = 1000;
            else if(wdrawAmount1 == 3) amount = 5000;
            else if(wdrawAmount1 == 4) amount = 10000;
            else if(wdrawAmount1 == 5){
                
                cout << "\nEnter amount to Withdraw: ";
                cin >> wdrawAmount2;
                
                amount = wdrawAmount2;
    }
    
    if(amount % 500 != 0){
        clearScreen();
        cout << "\nInvalid  Amount. Amount must be divisible by 500";
        continue;
    }

    // Determine bank index fee and daily limit
    int bankIndex = -1;
    for(int i = 0; i < NUM_BANKS; i++){
        if(userBanks[accountIndex] == bankNames[i]){
            bankIndex = i;
            break;
        }
    }
    
    if(bankIndex == -1){
        cout << "\nBank not recognized.\n";
        continue;
    }
    
    double fee = 0;
    if(accountTypes[accountIndex] == "Local") fee = localFees[bankIndex];
    else fee = intlFees[bankIndex];

    double totalDeduction = amount + fee;

    // Check balance
    if(totalDeduction > balances[accountIndex]){
        cout << "\nInsufficient balance including fees.\n";
        continue;
    }

    // Check daily limit
    if(amount > dailyLimits[bankIndex]){
        cout << "\nWithdrawal exceeds daily limit of " << dailyLimits[bankIndex] << " PHP.\n";
        continue;
    }

    // Check ATM cash availability
    int totalCashAvailable = 0;
    for(int i = 0; i < NUM_DENOMINATIONS; i++) totalCashAvailable += denominations[i] * billCount[i];
    if(amount > totalCashAvailable){
        cout << "\nATM does not have sufficient cash.\n";
        continue;
    }

    // Deduct amount and fee
    balances[accountIndex] -= totalDeduction;
    logTransaction(transactionTypes, transactionAmounts, transactionFees,
    transactionQuantities, cardNumbers[accountIndex], "Withdrawal", amount, fee);

        clearScreen();
    cout << "Please Wait..." << endl;
    cout << "\nCollect your cash: PHP " << amount << endl;
    cout << "Fee deducted: PHP " << fee << endl;

    // deduction shinanigans apply here
    int bills1000 = 0;
    int bills500 = 0;

    calculateBills(amount, bills1000, bills500);
    cout << "1000 Bills: " << bills1000 << endl;
    cout << "500 Bills: " << bills500 <<  endl;

    displayDateTime();

    cout << "\nPress any key to continue: ";
    string temp;
    cin >> temp;
}



    if(choice == 3){
    clearScreen();

    string receiver;
    double amount;

    cout << "===== TRANSFER PANEL =====\n";
    cout << "\nEnter receipient card number: ";
    cin >> receiver;

    int receiverIndex = -1;
    for(int i = 0; i < cardNumbers.size(); i++){
        if(cardNumbers[i] == receiver){
            receiverIndex = i;
            break;
        }
    }

    if(receiverIndex == -1){
        cout << "\nSorry, Recipient not found.\n";
        continue;
    }

    cout << "\nEnter amount to transfer: ";
    cin >> amount;

    // Determine fee: local vs international
    int senderBankIndex = -1;
    int receiverBankIndex = -1;
    for(int i = 0; i < NUM_BANKS; i++){
        if(userBanks[accountIndex] == bankNames[i]) senderBankIndex = i;
        if(userBanks[receiverIndex] == bankNames[i]) receiverBankIndex = i;
    }

    double fee = 0;
    if(senderBankIndex != -1 && receiverBankIndex != -1){
        if(senderBankIndex == receiverBankIndex) fee = localFees[senderBankIndex];
        else fee = intlFees[senderBankIndex];
    }

    double totalDeduction = amount + fee;
    if(totalDeduction > balances[accountIndex]){
        cout << "\nInsufficient balance including transfer fee.\n";
        continue;
    }

    balances[accountIndex] -= totalDeduction;
    balances[receiverIndex] += amount;
    logTransaction(transactionTypes, transactionAmounts,
    transactionFees, transactionQuantities, cardNumbers[accountIndex], "Transfer", amount, fee);

    time_t now = time(0);
    clearScreen();
    cout << "Transfer successful!\n";
    cout << "Amount: PHP " << amount << endl;
    cout << "Fee: PHP " << fee << endl;
    cout << "Transaction time: " << ctime(&now);

    cout << "\nPress any key to continue: ";
    string temp;
    cin >> temp;
}

                if(choice == 4){
                    clearScreen();
                        cout << "===== VIEWING TRANSACTION HISTORY =====" << endl;

                        if(transactionTypes.empty()){
                            clearScreen();
                            cout << "Oops, you do not have transactions yet.\n";
                        }

                        for(int i = 0; i < transactionTypes.size(); i++){
                            cout << "\n" << transactionTypes[i] << " | Amount: " << transactionAmounts[i] << " | Fee: " << transactionFees[i] << " | Count: " << transactionQuantities[i] << endl;
                        }

                        cout << "\nPress any key to continue: ";
                        string temp;
                        cin >> temp;
                    
                }

                if(choice == 5){
                    clearScreen();
                    string oldPIN, newPIN;

                    cout << "===== CHANGING PIN NUMBER =====\n";
                    cout << "\nEnter your current PIN number: ";
                    cin >> oldPIN;

                    if(!verifyPIN(oldPIN, encodedPINs[accountIndex])){
                        cout << "\nIncorrect PIN.\n";

                        cout << "\nPress any key to continue: ";
                        string temp;
                        cin >> temp;
                        continue;
                    }

                    cout << "Enter your NEW PIN number: ";
                    cin >> newPIN;

                    encodedPINs[accountIndex] = encodeString(newPIN);

                    cout << "\nSuccessfully changed your PIN number.\n";

                    cout << "\nPress any key to continue: ";
                    string temp;
                    cin >> temp;
                }

    }while(choice != 6);
        clearScreen();
        cout << "Logging you out...\n";

        cout << "\nPress any key to continue: ";
        string temp;
        cin >> temp;

    return;
}



void adminMenu (vector<string>& cardNumbers,
vector<string>& encodedPINs,     
vector<double>& balances,        
vector<string>& userBanks,        
vector<string>& accountTypes) {
    int choice;
    
    do {
        clearScreen();
        cout << "======== ADMIN MENU ========" << endl;
        cout << "\n[1] Add Account" << endl;
        cout << "[2] View Accounts" << endl;
        cout << "[3] Delete/Deactivate Account" << endl;
        cout << "[4] ATM Cash Refill" << endl;
        cout << "[5] ATM Status" << endl;
        cout << "[6] Change Admin Passcode" << endl;
        cout << "[7] View list of Admin Users" << endl;
        cout << "[8] Reset Account Password" << endl;
        cout << "[9] Exit" << endl;
        cout << "============================" << endl;
        cout << "\nSelect Choice: ";
        cin >> choice;
        
        
        if (choice == 1) {
            clearScreen();
            string card, pin, bank, type;
            double balance;
            
            cout << "Enter Card Number: ";
            cin >> card;
            
            cout << "Enter Pin Number: ";
            cin >> pin;
            
            cout << "Enter Bank: ";
            cin >> bank;
            
            cout << "Enter Balance Amount: ";
            cin >> balance;
            
            cout << "Enter Account Type: ";
            cin >> type;
            
            addAccount(cardNumbers, encodedPINs,
            balances, userBanks, accountTypes,
            card, encodeString(pin), balance, bank, type);
            
            cout << "\nAccount Added Successfully.\n";
            
            
        }
        
        else if (choice == 2){
            clearScreen();
            cout << "======== View Accounts ========" << endl;
            
            if(cardNumbers.empty()) {
                cout << "\nNo accounts available.\n";
            }
            else {
                for(int i = 0; i < cardNumbers.size(); i++){
                    cout << "\nAccount " << i + 1 << endl;
                    cout << "Card Number: " << cardNumbers[i] << endl;
                    cout << "Bank: " << userBanks[i] << endl;
                    cout << "Account Type: " << accountTypes[i] << endl;
                    cout << "Balance: " << balances[i] << endl;
                    cout << "--------------------------" << endl;
                }
            }
            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;
            
        }
        
        else if(choice == 3){
            clearScreen();

            string card;
            cout << "Enter Card Number to delete/deactivate: ";
            cin >> card;

            bool found = false;
            for(int i = 0; i < cardNumbers.size(); i++){
                if(cardNumbers[i] == card){
                    cardNumbers.erase(cardNumbers.begin() + i);
                    encodedPINs.erase(encodedPINs.begin() + i);
                    balances.erase(balances.begin() + i);
                    userBanks.erase(userBanks.begin() + i);
                    accountTypes.erase(accountTypes.begin() + i);

                    cout << "Account deleted/deactivated successfully.\n";
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Account not found. Try another number\n";

            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;
        }
        
        else if (choice == 4){
            clearScreen();

            time_t now = time(0);
            tm* localTime = localtime(&now);

            if(localTime->tm_hour != 8 || localTime->tm_min > 15) {
                cout << "Refill allowed only from 8:00 AM to 8:15 AM.\n";
            }
            else{
                cout << "======== ATM CASH REFILL ========\n";
                for(int i = 0; i < NUM_DENOMINATIONS; i++){
                    int addBills;
                    cout << "Enter number of " << denominations[i] << " Php bills to add: ";
                    cin >> addBills;
                    billCount[i] += addBills;
                }
                cout << "ATM Cash Refilled Successfully.\n";
            }
            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;
            
            
        }
        
        else if (choice == 5){
            clearScreen();

            cout << "======== ATM STATUS ========\n";
            double totalCash = 0;
            for(int i = 0; i < NUM_DENOMINATIONS; i++){
                cout << "Denomination: " << denominations[i] << " | Bills: " << billCount[i] << " | Subtotal: " << denominations[i] * billCount[i] << endl;
                totalCash += denominations[i] * billCount[i];
            }
            cout << "Total Cash in ATM: PHP " << totalCash << endl;
            
            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;
            
        }

        else if (choice == 6) {
            clearScreen();

            string currentPass, newPass;

            cout << "Enter Admin Passcode: ";
            cin >> currentPass;

            if (currentPass != adminPasscode){
                cout << "Incorrect Passcode" << endl;
            }

            else {
                cout << "Enter New Admin Passcode: ";
                cin >> newPass;
                adminPasscode = newPass;


                cout << "Admin Passcode Changed Successfully!" << endl;
            }
            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;
        }

        else if (choice == 7){
            clearScreen();

            cout << "========= LIST OF ADMIN USERS =========" << endl;
            for(const auto admin : admin){
                cout << admin << endl;
            }
            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;
        }

        else if (choice == 8){
            clearScreen();

            string card;
            cout << "Enter Card Number of Accout to Reset PIN: ";
            cin >> card;

            int accountIndex = -1;
            for (int i = 0; i < cardNumbers.size(); i++){
                if(cardNumbers[i] == card){
                    accountIndex = i;
                    break;
                }
            }
            if (accountIndex == -1){
                cout << "Account Not Found" << endl;
            }

            else {
                string newPIN;
                cout << "Enter New PIN: ";
                cin >> newPIN;
                encodedPINs[accountIndex] = encodeString(newPIN);
                cout << "Account PIN  has been reset Successfully!" << endl;
            }
            cout << "\nPress any key to continue: ";
            string temp;
            cin >> temp;

        }


    
    } while (choice != 9);

        cout << "Exiting..." << endl;
}
