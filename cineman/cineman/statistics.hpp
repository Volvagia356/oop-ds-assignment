#ifndef CINEMAN_STATISTICS
#define CINEMAN_STATISTICS
#include "customer.hpp"

int getIntLength(int);
char* getPaddedString(const char*, int, char);

bool sortByName(Customer*, Customer*);
bool sortByType(Customer*, Customer*);

void transactionHistory();
void memberList(int);

#endif