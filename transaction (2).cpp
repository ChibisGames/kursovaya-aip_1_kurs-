#include "transaction (2).hpp"
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
