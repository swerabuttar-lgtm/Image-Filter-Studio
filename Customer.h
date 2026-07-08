#pragma once
#include "User.h"
#include <string>
using namespace std;

class Customer : public User {
private:
    string gender;
    string phone;
    string city;
    bool isBlocked;

public:
    Customer(string cnic, string password, string fullName,
             string gender, string phone, string city, bool isBlocked = false)
        : User(cnic, password, fullName),
          gender(gender), phone(phone), city(city), isBlocked(isBlocked) {}

    void showMenu() override;

    string getGender() const { return gender; }
    string getPhone() const { return phone; }
    string getCity() const { return city; }
    bool getIsBlocked() const { return isBlocked; }
    void setIsBlocked(bool val) { isBlocked = val; }

    string toFileString() const {
        return cnic+"|"+password+"|"+fullName+"|"+gender+"|"+phone+"|"+city+"|"+(isBlocked?"1":"0");
    }
};