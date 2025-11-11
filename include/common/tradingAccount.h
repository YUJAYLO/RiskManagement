#ifndef TRADING_ACCOUNT_H
#define TRADING_ACCOUNT_H

#include <string>
#include "./brokerID.h" 

class TradingAccount {
    private:
        int _accountNumber; 
        
        int getCheckDigit() const;
        int generateCheckDigit(const BrokerID& brokerId) const;
        bool validateCheckDigit(const BrokerID& brokerId) const;
        bool isValid(int accountNumber) const;

    public:
        TradingAccount(const std::string& accountNumber, const BrokerID& brokerId); // Initial constructor

        // Getter Functions
        int getAccountNumber() const { return _accountNumber; }
        std::string toString() const;
};

#endif