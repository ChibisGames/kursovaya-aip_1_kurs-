#include <iostream>
#include <memory>
#include <limits>
#include "Blockchain.hpp"
#include "gold_client.hpp"
#include "platinum_client.hpp"
#include "standard_client.hpp"
#include "wallet.hpp"

using namespace std;

void addNewClient(Blockchain& blockchain) {
    string clientId, clientName;
    char clientType;
    double initialBalance;

    cout << "\n--- Adding New Client ---" << endl;

    // Ввод ID клиента с проверкой на существование
    while (true) {
        cout << "Enter client ID: ";
        cin >> clientId;
        if (blockchain.findClient(clientId)) {
            cout << "Error: Client with ID '" << clientId << "' already exists. Try another ID." << endl;
        } else {
            break;
        }
    }

    // Ввод имени клиента
    cout << "Enter client name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, clientName);

    // Выбор типа клиента
    while (true) {
        cout << "Select client type (G - Gold, P - Platinum, S - Standard): ";
        cin >> clientType;
        clientType = toupper(clientType);
        if (clientType == 'G' || clientType == 'P' || clientType == 'S') {
            break;
        }
        cout << "Invalid client type. Please try again." << endl;
    }

    // Ввод начального баланса
    cout << "Enter initial wallet balance: ";
    while (!(cin >> initialBalance) || initialBalance < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount. Please enter a positive number: ";
    }

    // Создание клиента и кошелька
    shared_ptr<Client> newClient;
    string walletId = "w1_" + clientId;

    switch (clientType) {
        case 'G':
            newClient = make_shared<GoldClient>(clientId, clientName);
            break;
        case 'P':
            newClient = make_shared<PlatinumClient>(clientId, clientName);
            break;
        case 'S':
            newClient = make_shared<StandardClient>(clientId, clientName);
            break;
    }

    newClient->addWallet(make_shared<Wallet>(walletId, clientId, initialBalance));
    blockchain.addClient(newClient);

    cout << "Client '" << clientName << "' (ID: " << clientId << ") added successfully!" << endl;
}

void displayMenu() {
    cout << "\n--- Blockchain Client Management ---" << endl;
    cout << "1. Add new client" << endl;
    cout << "2. Display all clients" << endl;
    cout << "3. Display all transactions" << endl;
    cout << "4. Process a transaction" << endl;
    cout << "5. Save and exit" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Enter your choice (1-5): ";
}

int main() {
    Blockchain blockchain;

    // Загрузка данных из файлов
    blockchain.loadClientsFromFile("Clients.txt");
    blockchain.loadTransactionsFromFile("Blockchain_transactions.txt");

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: // Добавление нового клиента
                addNewClient(blockchain);
                break;
                
            case 2: // Просмотр всех клиентов
                blockchain.displayClients();
                break;
                
            case 3: // Просмотр всех транзакций
                blockchain.displayTransactions();
                break;
                
            case 4: { // Обработка транзакции
                string senderId, senderWallet, receiverId, receiverWallet;
                double amount;
                
                cout << "\n--- Process Transaction ---" << endl;
                cout << "Enter sender client ID: ";
                cin >> senderId;
                cout << "Enter sender wallet ID: ";
                cin >> senderWallet;
                cout << "Enter receiver client ID: ";
                cin >> receiverId;
                cout << "Enter receiver wallet ID: ";
                cin >> receiverWallet;
                cout << "Enter amount: ";
                cin >> amount;
                
                blockchain.processTransaction(senderId, senderWallet, receiverId, receiverWallet, amount);
                break;
            }
                
            case 5: // Сохранение и выход
                blockchain.saveClientsToFile("Clients.txt");
                blockchain.saveTransactionsToFile("Blockchain_transactions.txt");
                running = false;
                cout << "Data saved. Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}