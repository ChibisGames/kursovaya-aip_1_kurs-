#include "platinum_client.hpp"
#include <string> 

using namespace std;
PlatinumClient::PlatinumClient(string id,string name):Client(id , name){}

double PlatinumClient::calculateCommission(double amount)const{
    return amount * 0.02; //коммиссия два процента
}

double PlatinumClient::getMaxTransactionLimit()const{
    return 5000.0;
}

string PlatinumClient::getBenefits()const{
    return "бонусные награды, умеренная комиссия";
}
