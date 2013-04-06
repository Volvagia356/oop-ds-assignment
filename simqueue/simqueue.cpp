#include <iostream>
#include <cctype>
#include <limits>
#ifdef WINNT
#include <cstdlib>
#endif
#include "libqueue.hpp"
using namespace std;

void clear_screen();

int main() {

    queuesim queue(2);
    bool is_running=true;
    
    clear_screen();
    cout << "SIM-Queue" << endl;
    cout << "(C) 2012 Raymond Choo Juan Yong" << endl << endl;
    cout << "Press [ENTER] to start..." << flush;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    while(is_running) {
        clear_screen();
        queue.print_status();
        char selection;
        cout << endl << "Select an option: " << endl;
        cout << "- A customer [J]oins the queue" << endl;
        cout << "- Counter [1] takes the next customer" << endl;
        cout << "- Counter [2] takes the next customer" << endl;
        cout << "- [Q]uit" << endl;
        cout << ">";
        do {
            while (!(cin >> selection)) {}
            switch(toupper(selection)) {
                case 'J':
                    queue.add_customer();
                    break;
                case '1':
                    queue.take_customer(0);
                    break;
                case '2':
                    queue.take_customer(1);
                    break;
                case 'Q':
                    is_running=false;
                    break;
                default:
                    selection=0;
            }
        } while (selection==0);
    }
    return 0;
}

void clear_screen() {
#ifdef WINNT
    system("cls");
#endif
#ifdef unix
    cout << "\x1B[H\x1B[2J";
#endif
}