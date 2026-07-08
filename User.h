#pragma once
#include <string>
#include <iostream>
using namespace std;

// Abstract base class
class User {
protected:
    string cnic;
    string password;
    string fullName;

public:
    User(string cnic, string password, string fullName)
        : cnic(cnic), password(password), fullName(fullName) {
        cout << "[User] Created: " << fullName << endl;
    }

    // virtual destructor for proper cleanup in derived classes
    virtual ~User() {
        cout << "[User] Destroyed: " << fullName << endl;
    }

    // Pure virtual - must be implemented by Admin and Customer
    virtual void showMenu() = 0;

    string getCnic() const { return cnic; }
    string getPassword() const { return password; }
    string getFullName() const { return fullName; }
};