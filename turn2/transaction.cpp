#include "transaction.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std; 

Transaction::Transaction(string id, string senderWalletId, string receiveWalletId, double amount, Txtype type, double commission)
    : Entity(id), senderWalletId(senderWalletId), receiveWalletId(receiveWalletId), amount(amount), type(type), commission(commission) {}

string Transaction::getId() const {
    return id;
}

string Transaction::getDetailes() const{
    stringstream ss;
    ss << "Transaction ID: " << id << ", From Wallet: " << senderWalletId
    << ", To Wallet: " << receiveWalletId << ", Amount: " << fixed << setprecision(2) << amount
    << ", Type: TRANSFER, Commission: " << fixed << setprecision(2) << commission;
    return ss.str();
}

string Transaction::getSenderWalletId()const{
    return senderWalletId;
}
string Transaction::getReceiveWalletId()const{
    return receiveWalletId;
}


double Transaction::getAmount() const {
    return amount;
}

Txtype Transaction::getType() const {
    return type;
}

double Transaction::getCommission() const {
    return commission;
}


// Transaktion List
TransactionList::TransactionList() : head(nullptr), tail(nullptr), size(0) {}
TransactionList::~TransactionList(){
    TransactionNode* current = head;
    while (current != nullptr){
        TransactionNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void TransactionList::addTransaction(Transaction *tx){
    TransactionNode* newNode = new TransactionNode(tx);
    if (!head){
        head = tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}


bool TransactionList::removeTransaction(const string& id) {
    TransactionNode* current = head;
    while (current != nullptr) {
        if (current->data && current->data->getId() == id) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

Transaction* TransactionList::getTransaction(const string &id)const{
    TransactionNode* current = head;
    while (current != nullptr){
        if(current->data && current->data->getId() == id){
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}
void TransactionList::displayTransaction() const {
    TransactionNode* current = head;
    cout << "--- Transactions ---" << endl;
    while (current != nullptr) {
        if (current->data) {
            cout << current->data->getDetailes() << endl;
        }
        current = current->next;
    }
    cout << "--------------------" << endl;
}
int TransactionList::getSize() const {
    return size;
}

// Transaction Node
TransactionNode::TransactionNode(Transaction* data) : data(data), prev(nullptr), next(nullptr) {}

TransactionNode::~TransactionNode() {
    delete data;
    data = nullptr;
}