#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_CATALOG   = 10;

int FileManager::loadCustomers(CustomerRecord* arr, int maxSize) {
    ifstream file("customers.txt");
    int count = 0;
    string line;
    while (getline(file, line) && count < maxSize) {
        if (line.empty()) continue;
        stringstream ss(line);
        string blocked;
        getline(ss, arr[count].cnic,     '|');
        getline(ss, arr[count].password, '|');
        getline(ss, arr[count].fullName, '|');
        getline(ss, arr[count].gender,   '|');
        getline(ss, arr[count].phone,    '|');
        getline(ss, arr[count].city,     '|');
        getline(ss, blocked,             '|');
        arr[count].isBlocked = (blocked == "1");
        count++;
    }
    return count;
}

void FileManager::saveCustomers(CustomerRecord* arr, int count) {
    ofstream file("customers.txt");
    for (int i = 0; i < count; i++)
        file << arr[i].cnic<<"|"<<arr[i].password<<"|"<<arr[i].fullName<<"|"
             <<arr[i].gender<<"|"<<arr[i].phone<<"|"<<arr[i].city<<"|"
             <<(arr[i].isBlocked?"1":"0")<<"\n";
}

bool FileManager::registerCustomer(const CustomerRecord& c) {
    CustomerRecord arr[MAX_CUSTOMERS];
    int count = loadCustomers(arr, MAX_CUSTOMERS);
    for (int i = 0; i < count; i++)
        if (arr[i].cnic == c.cnic) { cout << "CNIC already exists!\n"; return false; }

    if (isBlocked(c.cnic)) { cout << "This CNIC is banned!\n"; return false; }

    ofstream file("customers.txt", ios::app);
    file << c.cnic<<"|"<<c.password<<"|"<<c.fullName<<"|"
         <<c.gender<<"|"<<c.phone<<"|"<<c.city<<"|0\n";
    cout << "Registration successful!\n";
    return true;
}

bool FileManager::loginCustomer(const string& cnic, const string& pass, CustomerRecord& out) {
    CustomerRecord arr[MAX_CUSTOMERS];
    int count = loadCustomers(arr, MAX_CUSTOMERS);
    for (int i = 0; i < count; i++)
        if (arr[i].cnic == cnic && arr[i].password == pass) {
            if (arr[i].isBlocked) { cout << "Account is blocked!\n"; return false; }
            out = arr[i];
            return true;
        }
    return false;
}

void FileManager::displayAllCustomers() {
    CustomerRecord arr[MAX_CUSTOMERS];
    int count = loadCustomers(arr, MAX_CUSTOMERS);
    cout << "\n--- All Customers ---\n";
    cout << "CNIC          | Name           | City     | Blocked\n";
    cout << "-----------------------------------------------------\n";
    for (int i = 0; i < count; i++)
        cout << arr[i].cnic<<" | "<<arr[i].fullName<<" | "
             <<arr[i].city<<" | "<<(arr[i].isBlocked?"YES":"NO")<<"\n";
}

void FileManager::searchCustomer(const string& query) {
    CustomerRecord arr[MAX_CUSTOMERS];
    int count = loadCustomers(arr, MAX_CUSTOMERS);
    cout << "\n--- Search Results ---\n";
    for (int i = 0; i < count; i++)
        if (arr[i].cnic == query || arr[i].fullName.find(query) != string::npos)
            cout << arr[i].cnic<<" | "<<arr[i].fullName<<" | "<<arr[i].city<<"\n";
}

void FileManager::blockCustomer(const string& cnic) {
    CustomerRecord arr[MAX_CUSTOMERS];
    int count = loadCustomers(arr, MAX_CUSTOMERS);
    for (int i = 0; i < count; i++)
        if (arr[i].cnic == cnic) { arr[i].isBlocked = true; break; }
    saveCustomers(arr, count);
    ofstream bf("blocked_cnics.txt", ios::app);
    bf << cnic << "\n";
    cout << "Customer blocked.\n";
}

void FileManager::deleteCustomer(const string& cnic) {
    CustomerRecord arr[MAX_CUSTOMERS];
    int count = loadCustomers(arr, MAX_CUSTOMERS);
    CustomerRecord updated[MAX_CUSTOMERS];
    int newCount = 0;
    for (int i = 0; i < count; i++)
        if (arr[i].cnic != cnic)
            updated[newCount++] = arr[i];
    saveCustomers(updated, newCount);
    cout << "Customer deleted.\n";
}

bool FileManager::isBlocked(const string& cnic) {
    ifstream bf("blocked_cnics.txt");
    string line;
    while (getline(bf, line))
        if (line == cnic) return true;
    return false;
}

void FileManager::initCatalog() {
    ofstream out("catalog.txt");
    out<<"01|Grayscale|Pixel Transform|1\n";
    out<<"02|Invert|Pixel Transform|1\n";
    out<<"03|Brightness Adjust|Pixel Transform|1\n";
    out<<"04|Contrast Stretch|Pixel Transform|1\n";
    out<<"05|Red Channel Only|Pixel Transform|1\n";
    out<<"06|Green Channel Only|Pixel Transform|1\n";
    out<<"07|Blue Channel Only|Pixel Transform|1\n";
    out<<"08|Box Blur|Spatial Filter|1\n";
    out<<"09|Flip Horizontal|Geometric|1\n";
    out<<"10|Flip Vertical|Geometric|1\n";
}

int FileManager::loadCatalog(CatalogRecord* arr, int maxSize) {
    ifstream file("catalog.txt");
    if (!file) { initCatalog(); file.open("catalog.txt"); }
    int count = 0;
    string line;
    while (getline(file, line) && count < maxSize) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, enabled;
        getline(ss, id,                  '|');
        getline(ss, arr[count].name,     '|');
        getline(ss, arr[count].category, '|');
        getline(ss, enabled,             '|');
        arr[count].id      = stoi(id);
        arr[count].enabled = (enabled == "1");
        count++;
    }
    return count;
}

void FileManager::saveCatalog(CatalogRecord* arr, int count) {
    ofstream file("catalog.txt");
    for (int i = 0; i < count; i++) {
        string id = (arr[i].id < 10 ? "0" : "") + to_string(arr[i].id);
        file << id<<"|"<<arr[i].name<<"|"<<arr[i].category<<"|"
             <<(arr[i].enabled?"1":"0")<<"\n";
    }
}

void FileManager::displayCatalog() {
    CatalogRecord arr[MAX_CATALOG];
    int count = loadCatalog(arr, MAX_CATALOG);
    cout << "\n--- Filter Catalog ---\n";
    for (int i = 0; i < count; i++) {
        string id = (arr[i].id < 10 ? "0" : "") + to_string(arr[i].id);
        cout << id<<". "<<arr[i].name<<" ["<<arr[i].category<<"] "
             <<(arr[i].enabled ? "Enabled" : "DISABLED")<<"\n";
    }
}

void FileManager::toggleFilter(int id) {
    CatalogRecord arr[MAX_CATALOG];
    int count = loadCatalog(arr, MAX_CATALOG);
    for (int i = 0; i < count; i++)
        if (arr[i].id == id) { arr[i].enabled = !arr[i].enabled; break; }
    saveCatalog(arr, count);
    cout << "Filter toggled.\n";
}

void FileManager::appendSession(const string& cnic, const string& timestamp,
                                 const string& filters, const string& file) {
    ofstream f("sessions.txt", ios::app);
    f << cnic<<"|"<<timestamp<<"|"<<filters<<"|"<<file<<"\n";
}

void FileManager::displayAllSessions() {
    ifstream file("sessions.txt");
    string line;
    cout << "\n--- All Sessions ---\n";
    while (getline(file, line))
        if (!line.empty()) cout << line << "\n";
}

void FileManager::displayCustomerSessions(const string& cnic) {
    ifstream file("sessions.txt");
    string line;
    cout << "\n--- Your Sessions ---\n";
    while (getline(file, line))
        if (!line.empty() && line.find(cnic) == 0)
            cout << line << "\n";
}