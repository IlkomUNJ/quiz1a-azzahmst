#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum PrimaryPrompt { LOGIN, REGISTER, EXIT, ADMIN_LOGIN };
enum RegisterPrompt { CREATE_BUYER, CREATE_SELLER, BACK };

struct User {
    string username;
    string password;
    string role;
};
vector<User> users;
bool loggedIn = false;
bool isAdmin = false;
string currentUser;
int main() {
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;
    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN: {
                cout << "Login selected." << endl;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                bool found = false;
                string role;
                for (auto &u : users) {
                    if (u.username == username && u.password == password) {
                        found = true;
                        role = u.role;
                        break;
                    }
                }
                if (found) {
                    loggedIn = true;
                    isAdmin = false;
                    currentUser = username;
                    cout << "Login success as " << role << ": " << currentUser << endl;

                    if (role == "Buyer") {
                        int buyerChoice = 0;
                        while (buyerChoice != 7 && buyerChoice != 8) {
                            cout << "\n--- Buyer Menu ---\n";
                            cout << "1. Check Account Status\n";
                            cout << "2. Upgrade Account to Seller\n";
                            cout << "3. Create Banking Account / Banking Functions\n";
                            cout << "4. Browse Store Functionality\n";
                            cout << "5. Order Functionality\n";
                            cout << "6. Payment Functionality\n";
                            cout << "7. Logout\n";
                            cout << "8. Delete Account\n";
                            cout << "Select option: "; cin >> buyerChoice;
                            switch (buyerChoice) {
                                case 7:
                                    cout << "Logout Buyer Success\n"; 
                                    loggedIn = false; currentUser=""; 
                                    break;
                                case 8:
                                    cout << "Delete Account Success\n";
                                    loggedIn = false; currentUser="";
                                    break;
                                default:
                                    break;
                            }
                        }
                    } else if (role == "Seller") {
                        int sellerChoice = 0;
                        while (sellerChoice != 13 && sellerChoice != 14) {
                            cout << "\n--- Seller Menu ---\n";
                            cout << "9. Check Inventory\n";
                            cout << "10. Add Item to Inventory\n";
                            cout << "11. Remove Item from Inventory\n";
                            cout << "12. View Orders\n";
                            cout << "13. Exit to Main Menu\n";
                            cout << "14. Exit Program\n";
                            cout << "Select option: "; cin >> sellerChoice;
                            switch (sellerChoice) {
                                case 13:
                                    cout << "Exit to Main Menu\n";
                                    loggedIn = false; currentUser = "";
                                    break;
                                case 14:
                                    cout << "Exit Program\n";
                                    exit(0);
                                default:
                                    break;
                            }
                        }
                    }
                } else {
                    cout << "Invalid username/password\n";
                }
                break;
            }
            case REGISTER: {
                regPrompt = CREATE_BUYER;
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER: {
                            cout << "Create Buyer Account selected." << endl;
                            string uname, pass;
                            cout << "Choose Username: "; cin >> uname;
                            cout << "Choose Password: "; cin >> pass;
                            bool exists = false;
                            for (auto &u : users) {
                                if (u.username == uname) { exists = true; break; }
                            }
                            if (exists) cout << "Username already exists\n";
                            else {
                                users.push_back({uname, pass, "Buyer"});
                                cout << "Buyer account registered\n";
                            }
                            break;
                        }
                        case CREATE_SELLER: {
                            cout << "Create Seller Account selected." << endl;
                            string uname, pass;
                            cout << "Choose Username: "; cin >> uname;
                            cout << "Choose Password: "; cin >> pass;
                            bool exists = false;
                            for (auto &u : users) {
                                if (u.username == uname) { exists = true; break; }
                            }
                            if (exists) cout << "Username already exists\n";
                            else {
                                users.push_back({uname, pass, "Seller"});
                                cout << "Seller account registered\n";
                            }
                            break;
                        }
                        case BACK:
                            cout << "Back selected\n";
                            break;
                        default:
                            cout << "Invalid\n";
                            break;
                    }
                }
                break;
            }
            case EXIT:
                cout << "Exit Success\n";
                break;
            case ADMIN_LOGIN: {
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    loggedIn = true;
                    isAdmin = true;
                    currentUser = username;
                    cout << "Login as Admin\n";
                    int adminChoice = 0;
                    while (adminChoice != 3) { 
                        cout << "\n--- Admin Menu ---\n";
                        cout << "1. Account Management\n";
                        cout << "2. System Report\n";
                        cout << "3. Logout Admin\n";
                        cout << "Select option: "; cin >> adminChoice;
                        switch(adminChoice) {
                            case 1: {
                                int accChoice = 0;
                                while(accChoice != 7) { 
                                    cout << "\n--- Account Management ---\n";
                                    cout << "1. View All Buyers\n";
                                    cout << "2. View All Sellers\n";
                                    cout << "3. View All Details\n";
                                    cout << "4. Search Buyer/Seller\n";
                                    cout << "5. Create new Buyer/Seller/Bank Account\n";
                                    cout << "6. Remove Buyer/Seller\n";
                                    cout << "7. Back\n";
                                    cout << "Select option: "; cin >> accChoice;
                                    switch(accChoice){
                                        case 1:
                                            cout << "\n=== All Buyers ===\n";
                                            for(auto &u: users){
                                                if(u.role=="Buyer") cout << "Username: " << u.username << endl;
                                            }
                                            break;
                                        case 2:
                                            cout << "\n=== All Sellers ===\n";
                                            for(auto &u: users){
                                                if(u.role=="Seller") cout << "Username: " << u.username << endl;
                                            }
                                            break;
                                        case 7:
                                            cout << "Back to Admin Menu\n"; 
                                            break;
                                        default: 
                                            break; // diem saja
                                    }
                                }
                                break;
                            }
                            case 2: {
                                cout << "\n--- System Report ---\n";
                                int buyers=0, sellers=0, banks=0;
                                for(auto &u:users){
                                    if(u.role=="Buyer") buyers++;
                                    else if(u.role=="Seller") sellers++;
                                }
                                cout << "Total Buyers: " << buyers << endl;
                                cout << "Total Sellers: " << sellers << endl;
                                cout << "Total Banking Accounts: " << banks << " (dummy)\n";
                                break;
                            }
                            case 3:
                                cout << "Logout Admin\n";
                                loggedIn=false; isAdmin=false; currentUser="";
                                break;
                            default:
                                break;
                        }
                    }
                } else {
                    cout << "Invalid admin credentials\n";
                }
                break;
            }
            default:
                cout << "Invalid\n";
                break;
        }
        cout << endl;
    }
    return 0;
}