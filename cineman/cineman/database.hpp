#ifndef CINEMAN_DB
#define CINEMAN_DB
#include <iostream>
#include <fstream>
#include <vector>
#include "transaction.hpp"
#include "customer.hpp"

class Database{
private:
    std::fstream membersFile;
    std::fstream salesFile;
    std::vector<Customer*> members;
    std::vector<saleStruct*> sales;
    void initFile(const char*,std::fstream&);
    void loadMembers();
    void loadSales();
public:
    Database();
    ~Database();
    void addMember(Customer*);
    void addSale(saleStruct*);
    void updateMember(int);
    Customer* getMember(int);
    int getMemberCount();
    friend void transactionHistory();
    friend void memberList(int);
};

#endif