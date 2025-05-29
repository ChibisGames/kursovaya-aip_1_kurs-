#ifndef transaction_list_hpp
#define transaction_list_hpp

#include <string>
#include "TransactionNode.hpp"
using namespace std;

class TransactionList{
private:
    TransactionNode* head;
    TransactionNode* tail;
    int size;
public:
    TransactionList();
    ~TransactionList();
    void addTransaction(Transaction* tx);
    bool removeTransaction(const string& id);
    Transaction* getTransaction(const string& id) const;
    void displayTransaction()const;
    int getSize()const;
    TransactionNode* getHead()const{
        return head;
    }
};
#endif /* transaction_list_hpp */
