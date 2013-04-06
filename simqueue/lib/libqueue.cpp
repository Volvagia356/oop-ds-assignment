#include <iostream>
#include "libqueue.hpp"
#include "queue.hpp"
using namespace std;

queuesim::queuesim(int counters) {
    this->counters=counters;
    this->counter_served=new Queue<int>[counters];
    this->counter_current=new int[counters]();
    this->customers=0;
}

bool queuesim::verify_counter(int counter) {
    if (counter<this->counters && counter>=0) {
        return true;
    } else {
        return false;
    }
}

int queuesim::add_customer() {
    this->queue.push_back(++customers);
    return customers;
}

int queuesim::take_customer(int counter){
    if (!this->verify_counter(counter) || this->queue.size()<1) {return -1;}
    if (this->counter_current[counter]>0) {
        this->counter_served[counter].push_back(this->counter_current[counter]);
    }
    this->counter_current[counter]=this->queue.front();
    this->queue.pop_front();
    return this->counter_current[counter];
}

void queuesim::print_status() {
    cout << "Current status of queue simulation:" << endl;
    cout << "Customers in queue: ";
    if (this->queue.size()>0) {
        for(queue.reset();!queue.atEnd();queue.next()) {
            cout << this->queue.current() << " ";
        }
    } else {
        cout << "None";
    }
    cout << endl;
    for(int i=0;i<this->counters;i++) {
        cout << "Customers already served by counter " << i+1 << ": ";
        if (this->counter_served[i].size()>0) {
            for (this->counter_served[i].reset();!this->counter_served[i].atEnd();this->counter_served[i].next()) {
                cout << this->counter_served[i].current() << " ";
            }
        } else {
            cout << "None";
        }
        cout << endl;
    }
    for(int i=0;i<this->counters;i++) {
        cout << "Current customer served by counter " << i+1 << ": ";
        if (this->counter_current[i]>0) {
            cout << this->counter_current[i];
        } else {
            cout << "None";
        }
        cout << endl;
    }
}