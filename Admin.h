#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin() : User("admin", "Admin123", "Administrator") {}
    void showMenu() override;
    void manageFilters();
    void manageCustomers();
    void viewAllSessions();
};