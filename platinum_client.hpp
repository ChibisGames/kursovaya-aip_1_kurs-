#ifndef platinum_client_hpp
#define platinum_client_hpp

#include <string>
#include "client.hpp"
using namespace std;

class PlatinumClient : public Client{
public:
    PlatinumClient(string id, string name);
    double calculateCommission(double amount) const override;
    double getMaxTransactionLimit()const override;
    string getBenefits() const;
    ~PlatinumClient()override{}
};
#endif 
