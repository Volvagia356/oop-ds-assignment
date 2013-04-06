#include <iostream>
#include <cstring>
#include "customer.hpp"
#include "database.hpp"
using namespace std;

extern Database* database;

//Constructors
Customer::Customer(const char* name) {
    this->initialize();
    if (name[0]==0) {
        this->id=-1;
    } else {
        this->id=database->getMemberCount();
    }
    this->ticketsBought=0;
    strncpy(this->name,name,32);
    this->name[31]=0;
}

Customer::Customer(int id,const customerStruct* customer) {
    this->initialize();
    this->id=id;
    this->ticketsBought=customer->ticketsBought;
    strncpy(this->name,customer->name,32);
    this->name[31]=0;
}

MemberGold::MemberGold(const char* name): Customer(name) {this->initialize();}
MemberGold::MemberGold(int id,const customerStruct* customer): Customer(id,customer) {this->initialize();}

MemberPlatinum::MemberPlatinum(const char* name): Customer(name) {this->initialize();}
MemberPlatinum::MemberPlatinum(int id,const customerStruct* customer): Customer(id,customer) {this->initialize();}

//Initialization parameters for different types of customers
void Customer::initialize() {
    this->discount=1;
    this->freeCount=-1;
}

void MemberGold::initialize() {
    this->discount=0.9;
    this->freeCount=-1;
}

void MemberPlatinum::initialize() {
    this->discount=0.8;
    this->freeCount=5;
}

//getType
int Customer::getType() {return 0;}
int MemberGold::getType() {return 1;}
int MemberPlatinum::getType() {return 2;}

//Methods
int Customer::getID() {return id;}

int Customer::discountedPrice(int price) {
    if((this->ticketsBought+1)%this->freeCount==0 && this->freeCount>-1) {return 0;}
    else {return price*this->discount;}
}

void Customer::addTicket() {
    this->ticketsBought++;
}

customerStruct Customer::getStruct() {
    customerStruct customer;
    for(int i=0;i<sizeof(customerStruct);i++) {
        ((char*)&customer)[i]=0;
    }
    customer.ticketsBought=this->ticketsBought;
    strncpy(customer.name,this->name,32);
    customer.name[31]=0;
    return customer;
}