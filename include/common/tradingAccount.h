#ifndef TRADING_ACCOUNT_H
#define TRADING_ACCOUNT_H

#include <string>
#include "./brokerID.h" 

class TradingAccount {
private:
    int _accountNumber; 
    
    bool isValid(int accountNumber) const;
    
public:
    TradingAccount(int accountNumber, const BrokerId& brokerId);
    
    int getAccountNumber() const { return _accountNumber; }
    std::string toString() const { return std::to_string(_accountNumber); }
    
    int getCheckDigit() const;
    int generateCheckDigit(const BrokerId& brokerId) const;
    bool validateCheckDigit(const BrokerId& brokerId) const;
    
    static TradingAccount createWithBroker(int baseNumber, const BrokerId& brokerId);
};

#endif