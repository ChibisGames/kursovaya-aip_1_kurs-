#include "transaction_list.hpp"
#include <iostream>
#include <string> 

using namespace std;

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
