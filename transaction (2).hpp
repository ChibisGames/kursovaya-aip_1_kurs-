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
#endif /* transaction_hpp */
