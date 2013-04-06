#include <iostream>
#include <ctime>
#include "transaction.hpp"
#include "customer.hpp"
#include "database.hpp"
using namespace std;

extern Database* database;

Transaction::Transaction(Customer* c) {
    this->c=c;
}

void Transaction::purchaseTickets(int ticketCount) {
    for(int i=0;i<ticketCount;i++) {
        saleStruct* s=new saleStruct;
        for(int i=0;i<sizeof(saleStruct);i++) {
            ((char*)s)[i]=0;
        }
        s->memberID=c->getID();
        s->type=1;
        s->price=c->discountedPrice(1000);
        sales.push_back(s);
        c->addTicket();
    }
}

void Transaction::registerMember() {
    saleStruct* s=new saleStruct;
    for(int i=0;i<sizeof(saleStruct);i++) {
        ((char*)s)[i]=0;
    }
    s->memberID=c->getID();
    s->type=2;
    switch(c->getType()) {
        case 1:
            s->price=1000;
            break;
        case 2:
            s->price=5000;
            break;
    }
    sales.push_back(s);
    database->addMember(c);
}

void Transaction::checkout() {
    for(int i=0;i<sales.size();i++) {
        sales[i]->time=(int)time(NULL);
        database->addSale(sales[i]);
    }
    if(c->getType()>0) {
        database->updateMember(c->getID());
    }
}

int Transaction::getTotal() {
    int total=0;
    for(int i=0;i<sales.size();i++) {
        total+=sales[i]->price;
    }
    return total;
}