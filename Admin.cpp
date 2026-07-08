#include "Admin.h"
#include "FileManager.h"
#include <iostream>
using namespace std;

void Admin::showMenu() {
    int choice;
    do {
        cout << "==========================================\n";
        cout << "|     ADMIN PANEL : Image Filter Studio  |\n";
        cout << "|========================================|\n";
        cout << "|  1. Manage Filter Catalog              | \n";
        cout << "|  2. Manage Customers                   |\n";
        cout << "|  3. View All Sessions                  |\n";
        cout << "|  4. Logout                             |\n";
        cout << "=========================================\n";
        cout << "Your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: manageFilters(); break;
            case 2: manageCustomers(); break;
            case 3: viewAllSessions(); break;
            case 4: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 4);
}

void Admin::manageFilters() {
    FileManager fm;
    int choice;
    do {
        cout << "\n=== Filter Catalog ===\n";
        fm.displayCatalog();
        cout << "Enter Filter ID to toggle (0 to go back): ";
        cin >> choice;
        if (choice != 0) fm.toggleFilter(choice);
    } while(choice != 0);
}

void Admin::manageCustomers() {
    FileManager fm;
    int choice;
    cout << "\n=== Customer Management ===\n";
    cout << "1. View All Customers\n";
    cout << "2. Search Customer\n";
    cout << "3. Block Customer\n";
    cout << "4. Delete Customer\n";
    cout << "Choice: ";
    cin >> choice;
    switch(choice) {
        case 1: fm.displayAllCustomers(); break;
        case 2: {
            string query;
            cout << "Enter CNIC or Name: ";
            cin >> query;
            fm.searchCustomer(query);
            break;
        }
        case 3: {
            string cnic;
            cout << "Enter CNIC to block: ";
            cin >> cnic;
            fm.blockCustomer(cnic);
            break;
        }
        case 4: {
            string cnic;
            cout << "Enter CNIC to delete: ";
            cin >> cnic;
            fm.deleteCustomer(cnic);
            break;
        }
    }
}

void Admin::viewAllSessions() {
    FileManager fm;
    fm.displayAllSessions();
}