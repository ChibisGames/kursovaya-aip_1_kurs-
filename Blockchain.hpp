//
//  Blockchain.hpp
//  курсовая
//
//  Created by Ваграм on 5/16/25.
//

#ifndef Blockchain_hpp
#define Blockchain_hpp

#include <string>
#include <fstream>
#include <memory>

#include "client_bst.hpp"
#include "transaction_list.hpp"
#include "client.hpp"
#include "wallet.hpp"
#include "transaction.hpp"
#include "gold_client.hpp"
#include "platinum_client.hpp"
#include "standard_client.hpp"



class Blockchain {
private:
    ClientBST clients;
    TransactionList transactions;

public:
    Blockchain();
    ~Blockchain();

    void addClient(shared_ptr<Client> client);
    shared_ptr<Client> findClient(const string& clientId) const;
    shared_ptr<Wallet> findWallet(const string& walletId, const Client* client) const;
    bool processTransaction(const string& senderClientId, const string& senderWalletId, const string& receiverClientId, const string& receiverWalletId, double amount);
    void displayClients() const;
    void displayTransactions() const;
    void saveClientsToFile(const string& filename) const;
    void loadClientsFromFile(const string& filename);
    void saveTransactionsToFile(const string& filename) const;
    void loadTransactionsFromFile(const string& filename);
    bool removeTransaction(const Transaction& tx);
};
#endif
