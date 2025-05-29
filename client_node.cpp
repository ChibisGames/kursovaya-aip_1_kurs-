#include "client_node.hpp"
#include <utility> // For move

ClientNode::ClientNode(shared_ptr<Client> data)
: data(std::move(data)), left(nullptr), right(nullptr) {}

ClientNode::~ClientNode() {
    
}
