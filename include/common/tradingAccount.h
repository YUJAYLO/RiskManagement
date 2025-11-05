#ifndef TRADING_ACCOUNT_H
#define TRADING_ACCOUNT_H

#include <string>
#include "./brokerID.h" 

class TradingAccount {
    private:
        int _accountNumber; 
        
        int getCheckDigit() const;
        int generateCheckDigit(const BrokerId& brokerId) const;
        bool validateCheckDigit(const BrokerId& brokerId) const;
        bool isValid(int accountNumber) const;

    public:
        TradingAccount(const std::string& accountNumber, const BrokerId& brokerId); // Initial constructor

        // Getter Functions
        int getAccountNumber() const { return _accountNumber; }
        std::string toString() const { return std::to_string(_accountNumber); }
};

#endif