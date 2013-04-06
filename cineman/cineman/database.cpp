#include <iostream>
#include <cstdlib>
#include <cstring>
#include "database.hpp"
#include "transaction.hpp"
#include "customer.hpp"

using namespace std;

void Database::initFile(const char* filename, fstream& fs) {
    char magic[8]="CINEMAN";
    fs.open(filename,fstream::in);
    if(fs.fail()) {
        fs.close();
        fs.open(filename,fstream::out|fstream::binary);
        fs.write(magic,8);
        for(int i=0;i<4;i++) {fs.put(0);}
    }
    fs.close();
    fs.open(filename,fstream::in|fstream::out|fstream::binary);
    fs.seekg(0);
    char fmagic[8];
    fs.read(fmagic,8);
    if(strcmp(fmagic,magic)!=0) {
        cout << "Error: Invalid or corrupted database file!" << endl;
        exit(EXIT_FAILURE);
    }
}

Database::Database() {
    initFile("members.db",this->membersFile);
    initFile("sales.db",this->salesFile);
    loadMembers();
    loadSales();
}

Database::~Database() {
    membersFile.close();
    salesFile.close();
}

void Database::loadMembers() {
    int memberCount;
    membersFile.seekg(8);
    membersFile.read((char*)&memberCount,sizeof(int));
    for(int i=0;i<memberCount;i++) {
        char memberType;
        customerStruct cStruct;
        membersFile.read(&memberType,1);
        membersFile.read((char*)&cStruct,sizeof(customerStruct));
        Customer *c;
        switch(memberType) {
            case 1:
                c=new MemberGold(i,&cStruct);
                break;
            case 2:
                c=new MemberPlatinum(i,&cStruct);
                break;
            default:
                cout << "Error reading database: Unknown member type at ID: " << i << endl;
                exit(EXIT_FAILURE);
                break;
        }
        members.push_back((Customer*)c);
    }
}

void Database::loadSales() {
    int salesCount;
    salesFile.seekg(8);
    salesFile.read((char*)&salesCount,sizeof(int));
    for(int i=0;i<salesCount;i++) {
        cout << i << endl;
        saleStruct* sStruct=new saleStruct;
        salesFile.read((char*)sStruct,sizeof(saleStruct));
        sales.push_back(sStruct);
    }
}

void Database::addMember(Customer* c) {
    int newID=members.size()+1;
    members.push_back(c);
    customerStruct cStruct=c->getStruct();
    char memberType=c->getType();
    membersFile.seekp(8);
    membersFile.write((char*)&newID,sizeof(int));
    membersFile.seekp(0,ios_base::end);
    membersFile.write(&memberType,1);
    membersFile.write((char*)&cStruct,sizeof(customerStruct));
    membersFile.flush();
}

void Database::addSale(saleStruct* sStruct) {
    int newID=sales.size()+1;
    sales.push_back(sStruct);
    salesFile.seekp(8);
    salesFile.write((char*)&newID,sizeof(int));
    salesFile.seekp(0,ios_base::end);
    salesFile.write((char*)sStruct,sizeof(saleStruct));
    salesFile.flush();
}

void Database::updateMember(int id) {
    int offset=8+sizeof(int)+id*(sizeof(customerStruct)+1)+1;
    customerStruct cStruct=members[id]->getStruct();
    membersFile.seekp(offset);
    membersFile.write((char*)&cStruct,sizeof(customerStruct));
    membersFile.flush();
}

Customer* Database::getMember(int id) {
    if (id>=(int)members.size()) {
        return NULL;
    } else {;
        return members[id];
    }
}

int Database::getMemberCount() {
    return members.size();
}