
#include "TransactionNode.hpp"

TransactionNode::TransactionNode(Transaction* data) : data(data), prev(nullptr), next(nullptr) {}

TransactionNode::~TransactionNode() {
    delete data;
    data = nullptr;
}
