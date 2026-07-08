#include <iostream>
#include <string>
#include <cctype>
#include "Image.h"
#include "Admin.h"
#include "Customer.h"
#include "FileManager.h"
using namespace std;

// Validation functions
bool validCnic(const string& c) {
    if (c.length() != 13) return false;
    for (char ch : c) if (!isdigit(ch)) return false;
    return true;
}

bool validPassword(const string& p) {
    if (p.length() != 9) return false;
    bool hasUpper = false, hasDigit = false;
    for (char ch : p) {
        if (isupper(ch)) hasUpper = true;
        if (isdigit(ch)) hasDigit = true;
    }
    return hasUpper && hasDigit;
}

void registerCustomer() {
    FileManager fm;
    CustomerRecord c;
    cout << "\n=== Register ===\n";

    do {
        cout << "CNIC (13 digits): ";
        cin >> c.cnic;
        if (!validCnic(c.cnic)) cout << "Invalid CNIC!\n";
    } while (!validCnic(c.cnic));

    if (fm.isBlocked(c.cnic)) {
        cout << "This CNIC is banned!\n"; return;
    }

    do {
        cout << "Password (9 chars, 1 uppercase, 1 digit): ";
        cin >> c.password;
        if (!validPassword(c.password)) cout << "Invalid password!\n";
    } while (!validPassword(c.password));

    string confirm;
    cout << "Confirm Password: ";
    cin >> confirm;
    if (confirm != c.password) { cout << "Passwords don't match!\n"; return; }

    cin.ignore();
    cout << "Full Name: ";
    getline(cin, c.fullName);
    cout << "Gender (M/F/Other): ";
    cin >> c.gender;
    cout << "Phone: ";
    cin >> c.phone;
    cout << "City: ";
    cin >> c.city;
    c.isBlocked = false;

    fm.registerCustomer(c);
}

void customerLogin() {
    FileManager fm;
    string cnic, pass;
    int attempts = 0;

    while (attempts < 3) {
        cout << "\n=== Customer Login ===\n";
        cout << "CNIC: ";
        cin >> cnic;
        cout << "Password: ";
        cin >> pass;

        CustomerRecord rec;
        if (fm.loginCustomer(cnic, pass, rec)) {
            cout << "Welcome, " << rec.fullName << "!\n";
            Customer customer(rec.cnic, rec.password, rec.fullName,
                              rec.gender, rec.phone, rec.city, rec.isBlocked);
            customer.showMenu();
            return;
        } else {
            attempts++;
            cout << "Wrong credentials! Attempts left: " << (3-attempts) << "\n";
        }
    }
    cout << "Too many failed attempts. Returning to main menu.\n";
}

int main() {
    int choice;
    do {
        cout << "============================================"<< endl;
        cout << "|         IMAGE FILTER STUDIO              |\n";
        cout << "|==========================================|\n";
        cout << "|  1. Admin Login                          |\n";
        cout << "|  2. Customer Login                       |\n";
        cout << "|  3. New Customer? Register here          |\n";
        cout << "|  4. Exit                                 |\n";
        cout << "============================================\n";
        cout << "Your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                string pass;
                cout << "Admin Password: ";
                cin >> pass;
                if (pass == "Admin123") {
                    Admin admin;
                    admin.showMenu();
                } else {
                    cout << "Wrong password!\n";
                }
                break;
            }
            case 2: customerLogin(); break;
            case 3: registerCustomer(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 4);
    return 0;
}