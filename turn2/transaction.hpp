#ifndef transaction_hpp
#define transaction_hpp

#include <string>
#include "entity.hpp"

using namespace std;

enum class Txtype{
    TRANSFER
};


class Transaction : public Entity{
private:
    string senderWalletId;
    string receiveWalletId;
    double amount;
    Txtype type;
    double commission;
public:
    Transaction(string id, string senderWalletId, string receiveWalletId, double amount, Txtype type, double commission);
    string getId() const override; // Changed to getId()
    string getDetailes() const;
    string getSenderWalletId() const;
    string getReceiveWalletId() const;
    double getAmount() const;
    Txtype getType() const;
    double getCommission()const;
    ~Transaction() override {}

};

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

class TransactionNode {
    public:
        Transaction* data;
        TransactionNode* prev;
        TransactionNode* next;
        TransactionNode(Transaction* data);
        ~TransactionNode();
};
#endif /* transaction_hpp */
