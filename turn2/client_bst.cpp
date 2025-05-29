#include "client_bst.hpp"
#include <iostream>
#include <utility> // For move
using namespace std;


ClientBST::ClientBST() : root(nullptr) {}

ClientBST::~ClientBST() {
    destroyTree(root);
}

void ClientBST::destroyTree(ClientNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void ClientBST::insert(shared_ptr<Client> client) {
    insert(root, std::move(client));
}

void ClientBST::insert(ClientNode*& node, shared_ptr<Client> client) {
    if (!node) {
        node = new ClientNode(std::move(client));
        return;
    }

    if (client->getTotalBalance() < node->data->getTotalBalance()) {
        insert(node->left, std::move(client));
    } else {
        insert(node->right, std::move(client));
    }
}

bool ClientBST::remove(const string& id) {
    return remove(root, id);
}

bool ClientBST::remove(ClientNode*& node, const string& id) {
    if (!node) return false;

    if (id < node->data->getId()) {
        return remove(node->left, id);
    } else if (id > node->data->getId()) {
        return remove(node->right, id);
    } else {
        ClientNode* temp = node;

        if (!node->left) {
            node = node->right;
        } else if (!node->right) {
            node = node->left;
        } else {
            ClientNode* minRight = findMin(node->right);
            node->data = minRight->data;
            remove(node->right, minRight->data->getId());
            temp = nullptr;
        }

        delete temp;
        return true;
    }
}

ClientNode* ClientBST::findMin(ClientNode* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

void ClientBST::displayInOrder() const {
    displayInOrder(root);
}

void ClientBST::displayInOrder(ClientNode* node) const {
    if (node) {
        displayInOrder(node->left);
        if (node->data) {
            cout << "ID: " << node->data->getId()
                      << ", Name: " << node->data->getName()
                      << ", Balance: " << node->data->getTotalBalance() << endl;
        }
        displayInOrder(node->right);
    }
}

vector<shared_ptr<Client>> ClientBST::getAllClients() const {
    vector<shared_ptr<Client>> clients;
    inOrderTraversal(root, clients);
    return clients;
}

void ClientBST::inOrderTraversal(ClientNode* node, vector<shared_ptr<Client>>& clients) const {
    if (!node) return;
    inOrderTraversal(node->left, clients);
    if (node->data) {
        clients.push_back(node->data);
    }
    inOrderTraversal(node->right, clients);
}

shared_ptr<Client> ClientBST::find(const string& id) const {
    return find(root, id);
}

shared_ptr<Client> ClientBST::find(ClientNode* node, const string& id) const {
    if (!node) return nullptr;
    if (!node->data) return nullptr;

    if (id == node->data->getId()) {
        return node->data;
    } else if (id < node->data->getId()) {
        return find(node->left, id);
    } else {
        return find(node->right, id);
    }
}
