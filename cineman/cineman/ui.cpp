#include <iostream>
#include <limits>
#include <cstdlib>
#include "ui.hpp"
#include "customer.hpp"
#include "transaction.hpp"
#include "database.hpp"
#include "statistics.hpp"
using namespace std;

extern Database* database;

void clearScreen() {
#ifdef WINNT
    system("cls");
#endif
#ifdef unix
    cout << "\x1B[H\x1B[2J";
#endif
}

void pause() {
    cout << "Press [ENTER] to continue" << endl;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

int getInt() {
    unsigned int n;
    cin >> n;
    if(cin) {
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return n;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return -1;
    }
}

double getDouble() {
    double n;
    cin >> n;
    if(cin) {
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return n;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return -1;
    }
}

void showLogo() {
    cout << "   _______                                " << endl
         << "  / ____(_)___  ___  ____ ___  ____ _____ " << endl
         << " / /   / / __ \\/ _ \\/ __ `__ \\/ __ `/ __ \\" << endl
         << "/ /___/ / / / /  __/ / / / / / /_/ / / / /" << endl
         << "\\____/_/_/ /_/\\___/_/ /_/ /_/\\__,_/_/ /_/ " << endl
         << "         Cinema Management System         " << endl
         << "     (C) 2012, Raymond Choo Juan Yong     " << endl << endl;
}

void mainMenu() {
    cout << "Main Menu:" << endl
         << "1. Ticketing" << endl
         << "2. Member registration" << endl
         << "3. Statistics" << endl
         << "4. Quit" << endl << endl;
    bool success;
    do {
        success=true;
        cout << "Selection: ";
        int n=getInt();
        switch(n) {
            case 1:
                ticketing();
                break;
            case 2:
                memberRegistration();
                break;
            case 3:
                statistics();
                break;
            case 4:
                clearScreen();
                exit(EXIT_SUCCESS);
                break;
            default:
                cout << "Invalid input!" << endl;
                success=false;
        }
    } while (!success);
}

void ticketing() {
    Customer* c;
    clearScreen();
    cout << "Ticket Purchase" << endl
         << "Type of customer?" << endl
         << "1. Member" << endl
         << "2. Non-member" << endl
         << "3. Cancel" << endl << endl;
    bool success;
    do {
        success=true;
        cout << "Selection: ";
        int n=getInt();
        switch(n) {
            case 1:
                int id;
                do {
                    do {
                        cout << "Enter member ID: ";
                        id=getInt();
                        if(id<0) {cout << "Invalid input!" << endl;}
                    } while (id<0);
                    c=database->getMember(id);
                    if(!c) {cout << "Invalid member ID!" << endl;}
                } while(!c);
                break;
            case 2:
                c=new Customer("");
                break;
            case 3:
                return;
                break;
            default:
                cout << "Invalid input!" << endl;
                success=false;
        }
    } while (!success);
    int ticketCount;
    do {
        cout << "Enter number of tickets (0 to cancel): ";
        ticketCount=getInt();
        if(ticketCount<0) {cout << "Invalid number of tickets!" << endl;}
        if(ticketCount==0) {return;}
    } while(ticketCount<0);
    Transaction* t=new Transaction(c);
    t->purchaseTickets(ticketCount);
    checkout(t);
    delete t;
    t=NULL;
}

void checkout (Transaction* t) {
    cout << "Total payment: " << (double)t->getTotal()/100 << endl;
    int cash;
    do {
        cout << "Cash payment: ";
        cash=getDouble()*100;
        if(cash<t->getTotal()) {cout << "Invalid payment!" << endl;}
    } while (cash<t->getTotal());
    cout << "Change: " << (double)(cash-t->getTotal())/100 << endl;
    t->checkout();
    pause();
}

void memberRegistration() {
    clearScreen();
    cout << "Member Registration" << endl
         << "Register what kind of member?" << endl
         << "1. Gold Member" << endl
         << "2. Platinum Member" << endl
         << "3. Cancel" << endl << endl;
    int memberType;
    Customer* c;
    bool success;
    do {
        success=true;
        cout << "Selection: ";
        memberType=getInt();
        if(memberType==1 || memberType==2) {
            char name[256];
            do {
                cout << "Enter name: ";
                cin.getline(name,32);
                if(!cin) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                if(name[0]==0) {cout << "Invalid name!" << endl;}
            } while(name[0]==0);
            switch(memberType) {
                case 1:
                    c=new MemberGold(name);
                    break;
                case 2:
                    c=new MemberPlatinum(name);
                    break;
            }
        } else if(memberType==3) {
            return;
        } else {
            success=false;
        }
    } while(!success);
    Transaction* t=new Transaction(c);
    t->registerMember();
    cout << "The member ID is " << c->getID() << endl;
    checkout(t);
    delete t;
    t=NULL;
}

void statistics() {
    while(true) {
        clearScreen();
        cout << "Statistics" << endl
             << "1. Transaction history" << endl
             << "2. Member list" << endl
             << "3. Return" << endl << endl;
        bool success;
        do {
            success=true;
            int selection;
            cout << "Selection: ";
            selection=getInt();
            switch(selection) {
                case 1:
                    clearScreen();
                    transactionHistory();
                    pause();
                    break;
                case 2:
                    sorting();
                    break;
                case 3:
                    return;
                    break;
                default:
                    cout << "Invalid selection!" << endl;
                    success=false;
                    break;
            }
        } while(!success);
    }
}

void sorting() {
    while(true) {
        clearScreen();
        int type;
        cout << "Sorting" << endl
             << "1. Sort by name" << endl
             << "2. Sort by type" << endl
             << "3. Return" << endl << endl;
        bool success;
        do {
            success=true;
            cout << "Selection: ";
            type=getInt();
            switch(type) {
                case 1:
                case 2:
                    clearScreen();
                    memberList(type);
                    pause();
                    break;
                case 3:
                    return;
                    break;
                default:
                    success=false;
                    cout << "Invalid selection!" << endl;
                    break;
            }
        } while(!success);
    }
}