#ifndef CINEMAN_CUSTOMER
#define CINEMAN_CUSTOMER
struct customerStruct {
    char name[32];
    int ticketsBought;
};

class Customer {
private:
    virtual void initialize();
protected:
    int id;
    char name[32];
    double discount;
    int freeCount;
    int ticketsBought;
public:
    Customer(const char*);
    Customer(int,const customerStruct*);
    virtual int getType();
    int getID();
    int discountedPrice(int);
    void addTicket();
    customerStruct getStruct();
    friend void transactionHistory();
    friend void memberList(int);
    friend bool sortByName(Customer*, Customer*);
    friend bool sortByType(Customer*, Customer*);
};

class MemberGold:public Customer {
private:
    void initialize();
public:
    MemberGold(const char*);
    MemberGold(int,const customerStruct*);
    int getType();
};

class MemberPlatinum:public Customer {
private:
    void initialize();
public:
    MemberPlatinum(const char*);
    MemberPlatinum(int,const customerStruct*);
    int getType();
};
#endif