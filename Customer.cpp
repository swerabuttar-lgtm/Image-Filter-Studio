#include "Customer.h"
#include "FilterSession.h"
#include "FileManager.h"
#include <iostream>
using namespace std;

void Customer::showMenu() {
    int choice;
    do {
        cout << "\n=======================================\n";
        cout << "|  Welcome, " << fullName << "!          |\n";
        cout << "|========================================|\n";
        cout << "|  1. Browse Filter Catalog              | \n";
        cout << "|  2. Start Filter Session               | \n";
        cout << "|  3. View My Session History            | \n";
        cout << "|  4. Logout                             | \n";
        cout << "=========================================\n";
        cout << "Your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                FileManager fm;
                fm.displayCatalog();
                break;
            }
            case 2: {
                FilterSession session(cnic);
                session.run();
                break;
            }
            case 3: {
                FileManager fm;
                fm.displayCustomerSessions(cnic);
                break;
            }
            case 4: cout << "Logging out...\n"; break;
            default: cout << "Invalid!\n";
        }
    } while(choice != 4);
}