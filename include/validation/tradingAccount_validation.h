#ifndef TRADING_ACCOUNT_VALIDATION_H
#define TRADING_ACCOUNT_VALIDATION_H

#include "../../common/include/tradingAccount.h"
#include "../../common/include/brokerID.h"

class TradingAccountIDValidation {
    private:
        bool _isValid;

    public:
        TradingAccountIDValidation(); // Default constructor
        
        // Validation method
        int getCheckDigit(const TradingAccount& tradingAccount) const;
        int generateCheckDigit(const BrokerId& brokerId, const TradingAccount& tradingAccount) const;
        bool validateCheckDigit(const BrokerId& brokerId, const TradingAccount& tradingAccount) const;
};

#endif