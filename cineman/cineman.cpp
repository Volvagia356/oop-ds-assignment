#include <iostream>
#include "database.hpp"
#include "customer.hpp"
#include "ui.hpp"
#include "winsize.hpp"
using namespace std;

Database* database;

int main() {
    int columns=getColumns();
    if(columns<72) {
        cout << "Terminal too small. Please make sure it is at least 72 columns wide!" << endl;
        return -1;
    }
    database=new Database();
    while(true) {
        clearScreen();
        showLogo();
        mainMenu();
    }
}