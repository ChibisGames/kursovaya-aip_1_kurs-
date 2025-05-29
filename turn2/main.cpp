
#include <iostream>
#include <memory> // Required for make_shared, even if using namespace std;
#include "blockchain.hpp"
#include "blockchain.cpp"
#include "client.hpp"
#include "client.cpp"
#include "wallet.hpp"
#include "wallet.cpp"

using namespace std; 

int main() {
    Blockchain blockchain;

    // Load data from files
    blockchain.loadClientsFromFile("Clients.txt");
    blockchain.loadTransactionsFromFile("Blockchain_transactions.txt");

    
    if (!blockchain.findClient("gold1")) {
        auto newClient = make_shared<GoldClient>("gold1", "Alice");
        newClient->addWallet(make_shared<Wallet>("w1_alice", "gold1", 15000.0));
        blockchain.addClient(newClient);
    }

    if (!blockchain.findClient("plat1")) {
        auto newClient = make_shared<PlatinumClient>("plat1", "Bob");
        newClient->addWallet(make_shared<Wallet>("w1_bob", "plat1", 7500.0));
        blockchain.addClient(newClient);
    }

    // This block is slightly more robust for adding client and then their wallet
    shared_ptr<Client> charlieClient = blockchain.findClient("std1");
    if (charlieClient == nullptr) {
        charlieClient = make_shared<StandardClient>("std1", "Charlie");
        blockchain.addClient(charlieClient);
        // Now that the client is added, ensure we get the shared_ptr back for consistency
        charlieClient = blockchain.findClient("std1");
        if (charlieClient) { // Ensure it was actually added and found
            charlieClient->addWallet(make_shared<Wallet>("w1_charlie", "std1", 200.0));
        }
    }


    blockchain.displayClients();
    blockchain.displayTransactions();

    blockchain.processTransaction("gold1", "w1_alice", "plat1", "w1_bob", 1000.0);
    // This transaction targets "w2_alice" which likely doesn't exist, leading to an error.
    // Ensure "w2_alice" is added to the "gold1" client if you want this to succeed.
    // For demonstration, I'll keep it as is, but be aware of the potential error.
    blockchain.processTransaction("std1", "w1_charlie", "gold1", "w2_alice", 50.0);
    blockchain.processTransaction("gold1", "w1_alice", "plat1", "w1_bob", 12000.0); // Exceeds limit

    blockchain.displayClients();
    blockchain.displayTransactions();

    // Save data to files
    blockchain.saveClientsToFile("Clients.txt");
    blockchain.saveTransactionsToFile("Blockchain_transactions.txt");

    return 0;
}
