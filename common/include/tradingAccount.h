#ifndef TRADING_ACCOUNT_H
#define TRADING_ACCOUNT_H

#include <string>
#include "brokerID.h" 

class TradingAccount {
    private:
        int _accountNumber; 

        bool isValid(int accountNumber) const;

    public:
        TradingAccount(); // Default constructor
        // TradingAccount(int accountNumber); // Initial constructor
        // TradingAccount(const TradingAccount& other); // Copy constructor


        
        int getAccountNumber() const;
        int generateCheckDigit(const BrokerId& brokerId) const;
        bool validateCheckDigit(const BrokerId& brokerId) const;
};

#endif // TRADING_ACCOUNT_H