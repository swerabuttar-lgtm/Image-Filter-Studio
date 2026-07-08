#pragma once
#include <iostream>
#include <string>
using namespace std;

class Image;  // forward declaration

class Filter {
protected:
    string name;
    string category;
    bool enabled;
public:
    Filter(string name, string category) : name(name), category(category), enabled(true) {
        cout << "[Filter] " << name << " created\n";
    }
    virtual ~Filter() {
        cout << "[Filter] " << name << " destroyed\n";
    }
    virtual void apply(Image& img) = 0;  // pure virtual
    string getName() const { return name; }
    string getCategory() const { return category; }
    bool isEnabled() const { return enabled; }
    void setEnabled(bool val) { enabled = val; }
    virtual string getDescription() const { return name; }
};