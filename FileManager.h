#pragma once
#include <string>
using namespace std;

struct CustomerRecord {
    string cnic, password, fullName, gender, phone, city;
    bool isBlocked;
};

struct CatalogRecord {
    int id;
    string name, category;
    bool enabled;
};

class FileManager {
public:
    // Customer operations
    int loadCustomers(CustomerRecord* arr, int maxSize);
    void saveCustomers(CustomerRecord* arr, int count);
    bool registerCustomer(const CustomerRecord& c);
    bool loginCustomer(const string& cnic, const string& pass, CustomerRecord& out);
    void displayAllCustomers();
    void searchCustomer(const string& query);
    void blockCustomer(const string& cnic);
    void deleteCustomer(const string& cnic);
    bool isBlocked(const string& cnic);

    // Catalog operations
    void initCatalog();
    int loadCatalog(CatalogRecord* arr, int maxSize);
    void saveCatalog(CatalogRecord* arr, int count);
    void displayCatalog();
    void toggleFilter(int id);

    // Session operations
    void appendSession(const string& cnic, const string& timestamp,
                       const string& filters, const string& file);
    void displayAllSessions();
    void displayCustomerSessions(const string& cnic);
};