#include "FilterSession.h"
#include "GrayscaleFilter.h"
#include "InvertFilter.h"
#include "BrightnessFilter.h"
#include "ContrastFilter.h"
#include "RedChannelFilter.h"
#include "GreenChannelFilter.h"
#include "BlueChannelFilter.h"
#include "BoxBlurFilter.h"
#include "FlipHorizontalFilter.h"
#include "FlipVerticalFilter.h"
#include "FileManager.h"
#include <iostream>
#include <ctime>
using namespace std;

FilterSession::FilterSession(string cnic) : customerCnic(cnic), image(nullptr), filterCount(0) {
    for (int i = 0; i < MAX_FILTERS; i++) pipeline[i] = nullptr;
    cout << "[Session] Started for " << cnic << endl;
}

FilterSession::~FilterSession() {
    if (image) delete image;
    for (int i = 0; i < filterCount; i++)
        if (pipeline[i]) delete pipeline[i];
    cout << "[Session] Ended" << endl;
}

FilterSession& FilterSession::addFilter(Filter* f) {
    if (filterCount < MAX_FILTERS) {
        pipeline[filterCount++] = f;
    }
    return *this;
}

void FilterSession::run() {
    loadImage();
    if (!image) return;
    buildPipeline();
    if (filterCount == 0) { cout << "No filters selected.\n"; return; }
    applyPipeline();
    saveResult();
}

void FilterSession::loadImage() {
    int choice;
    cout << "\n=== Load Image ===\n";
    cout << "1. Load from JPG/PNG file\n";
    cout << "2. Generate test pattern\n";
    cout << "Choice: ";
    cin >> choice;

    image = new Image(64, 32);

    if (choice == 1) {
        string path;
        cout << "Enter image path: ";
        cin >> path;
        if (!image->loadFromFile(path)) {
            cout << "Failed! Using test pattern.\n";
            image->fillTestPattern();
        }
    } else {
        image->fillTestPattern();
        cout << "Test pattern generated.\n";
    }
    image->displayASCII();
}

void FilterSession::buildPipeline() {
    FileManager fm;
    cout << "\n=== Build Filter Pipeline ===\n";
    fm.displayCatalog();
    CatalogRecord catalog[10]; 
    int catCount = fm.loadCatalog(catalog, 10);

    int id;
    do {
        cout << "Enter filter ID (0 to finish): ";
        cin >> id;
        Filter* f = nullptr;
        switch(id) {
            case 1:  
                if(!catalog[0].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                } 
                f = new GrayscaleFilter(); 
                break;
            case 2:
                if(!catalog[1].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }  
                f = new InvertFilter(); 
                break;
            case 3: 
                if(!catalog[2].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                int amt;
                cout << "Brightness amount (-100 to 100): ";
                cin >> amt;
                if(amt < -100 ){
                    amt = -100;
                }
                if(amt > 100){
                    amt = 100;
                }
                f = new BrightnessFilter(amt);
                break;
            
            case 4:  
            if(!catalog[3].enabled){
                cout << "Filter is disabled!\n";
                break;
            } 
                f = new ContrastFilter(); 
                break;
            case 5: 
                if(!catalog[4].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                f = new RedChannelFilter();     
                break;
            case 6: 
                if(!catalog[5].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                f = new GreenChannelFilter();    
                break;
            case 7: 
                if(!catalog[6].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                f = new BlueChannelFilter();     
                break;
            case 8:  
                if(!catalog[7].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                f = new BoxBlurFilter();         
                break;
            case 9:  
                if(!catalog[8].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                f = new FlipHorizontalFilter();
                break;
            case 10: 
                if(!catalog[9].enabled){
                    cout << "Filter is disabled!\n";
                    break;
                }
                f = new FlipVerticalFilter();    
                break;
            case 0:  break;
            default: cout << "Invalid ID!\n";
        }
        if (f) {
            addFilter(f);
            cout << "Added: " << f->getName() << "\n";
            cout << "Pipeline: [ ";
            for (int i = 0; i < filterCount; i++)
                cout << pipeline[i]->getName() << " ";
            cout << "]\n";
        }
    } while(id != 0);
}

void FilterSession::applyPipeline() {
    cout << "\n=== Applying Pipeline ===\n";
    for (int i = 0; i < filterCount; i++) {
        cout << "Applying " << (i+1) << "/" << filterCount
             << ": " << pipeline[i]->getName() << "...\n";
        pipeline[i]->apply(*image);
        image->displayASCII();
    }
    cout << "All " << filterCount << " filters applied.\n";
}

void FilterSession::saveResult() {
    char ans;
    cout << "Save result? (y/n): ";
    cin >> ans;
    if (ans != 'y') return;

    time_t now = time(0);
    tm* t = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", t);
    string filename = customerCnic + "_" + timestamp + ".png";

    image->saveToFile(filename);

    // Build filters string
    string filtersStr = "";
    for (int i = 0; i < filterCount; i++) {
        if (i > 0) filtersStr += ">";
        filtersStr += pipeline[i]->getName();
    }

    FileManager fm;
    fm.appendSession(customerCnic, timestamp, filtersStr, filename);
    cout << "Session recorded!\n";
    cout << "Open " << filename << " in any image viewer.\n";
}