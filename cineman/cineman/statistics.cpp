#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <vector>
#include <algorithm>
#include "winsize.hpp"
#include "database.hpp"
#include "customer.hpp"
#include "transaction.hpp"
#include "statistics.hpp"
using namespace std;

extern Database* database;

//Misc. Functions
int getIntLength(int n) {
    int x=1,i=0;
    do {i++; x*=10;} while(n>=x);
    return i;
}

char* getPaddedString(const char* str, int outSize, char padding=' ') {
    char* outStr;
    outStr=new char[outSize+1];
    for(int i=0;i<outSize;i++) {
        outStr[i]=padding;
    }
    outStr[outSize]=0;
    int size=strlen(str);
    for (int i=0;i<size && i<outSize;i++) {
        outStr[i]=str[i];
    }
    return outStr;
}

//Sorting Functions
bool sortByName(Customer* c1, Customer* c2) {
    string name1(c1->name);
    string name2(c2->name);
    if(name1<name2) {return true;}
    else {return false;}
}

bool sortByType(Customer* c1, Customer* c2) {
    if(c1->getType()<c2->getType()) {return true;}
    else {return false;}
}

//UI Functions
void transactionHistory(){
    int columns=getColumns();
    char* memberStr=getPaddedString("Member",columns-41);
    char* memberBorder=getPaddedString("",columns-41,'-');
    cout << "+-------------------+------------+" << memberBorder << "+-----+";
    cout << "|Time               |Type        |" << memberStr << "|Price|";
    
    for(int i=0;i<database->sales.size();i++) {
        saleStruct* s=database->sales[i];
        //Time
        char timeStr[20];
        tm* timestruct;
        time_t tmptime=s->time;
        timestruct=localtime(&tmptime);
        strftime(timeStr,20,"%Y/%m/%d %H:%M:%S",timestruct);
        //Type
        char* type;
        switch(s->type) {
            case 1:
                type=getPaddedString("Ticket",12);
                break;
            case 2:
                type=getPaddedString("Registration",12);
                break;
        }
        //Member name
        char* memberName;
        if(s->memberID>=0) {
            memberName=getPaddedString(database->members[s->memberID]->name,columns-41);
        } else {
            memberName=getPaddedString("-",columns-41);
        }
        //Price
        int price=s->price/100;
        char* pricePadding;
        pricePadding=getPaddedString("",5-getIntLength(price));
        //Output
        cout << "+-------------------+------------+" << memberBorder << "+-----+";
        cout << "|" << timeStr << "|" << type << "|" << memberName << "|" << pricePadding << price << "|";
        //Cleanup
        delete type;
        delete memberName;
        delete pricePadding;
    }
    
    cout << "+-------------------+------------+" << memberBorder << "+-----+" << endl;
    
    delete memberStr;
    delete memberBorder;
    memberStr=NULL;
    memberBorder=NULL;
}

/*
 * Argument for 'type':
 * 1. Sort by name
 * 2. Sort by type
 */

void memberList(int type) {
    int columns=getColumns();
    char* memberStr=getPaddedString("Member",columns-19);
    char* memberBorder=getPaddedString("",columns-19,'-');
    cout << "+" << memberBorder << "+--------+-------+";
    cout << "|" << memberStr << "|Type    |Tickets|";
    
    vector<Customer*> membersTemp=database->members;
    switch(type) {
        case 1:
            sort(membersTemp.begin(),membersTemp.end(),sortByName);
            break;
        case 2:
            sort(membersTemp.begin(),membersTemp.end(),sortByType);
            break;
    }
    
    for(int i=0;i<membersTemp.size();i++) {
        Customer* c=membersTemp[i];
        //Member name
        char* memberName=getPaddedString(c->name,columns-19);
        //Member type
        char* memberType;
        switch(c->getType()) {
            case 1:
                memberType=getPaddedString("Gold",8);
                break;
            case 2:
                memberType=getPaddedString("Platinum",8);
                break;
        }
        //Tickets
        char* ticketPadding=getPaddedString("",7-getIntLength(c->ticketsBought));
        //Output
        cout << "+" << memberBorder << "+--------+-------+";
        cout << "|" << memberName << "|" << memberType << "|" << ticketPadding << c->ticketsBought << "|";
        //Cleanup
        delete memberName;
        delete memberType;
        delete ticketPadding;
    }
    cout << "+" << memberBorder << "+--------+-------+" << endl;
    delete memberStr;
    delete memberBorder;
}