#ifndef LIBQUEUE
#define LIBQUEUE
#include "queue.hpp"
using namespace std;

class queuesim {
    int counters;
    int customers;
    Queue<int> queue;
    Queue<int>* counter_served;
    int* counter_current;
public:
    queuesim(int counters=2);
    bool verify_counter(int counter);
    int add_customer();
    int take_customer(int counter);
    void print_status();
};
#endif