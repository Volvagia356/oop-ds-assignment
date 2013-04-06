#ifndef CINEMAN_TRANS
#define CINEMAN_TRANS
#include <vector>
#include "customer.hpp"

/*
 * Types:
 * 1. Ticket sale
 * 2. Member registration
 */

struct saleStruct {
    int memberID;
    char type;
    int price;
    int time;
};

class Transaction {
private:
    Customer* c;
    std::vector<saleStruct*> sales;
public:
    Transaction(Customer*);
    void purchaseTickets(int);
    void registerMember();
    void checkout();
    int getTotal();
};

#endif