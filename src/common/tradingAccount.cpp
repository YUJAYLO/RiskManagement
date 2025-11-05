#include "../../include/common/tradingAccount.h"

TradingAccount::TradingAccount(int accountNumber, const BrokerId& brokerId){
    if(!isValid(accountNumber))// Validate account number
        throw std::invalid_argument("Invalid account number");
}

bool TradingAccount::isValid(int accountNumber) const{
    // Account number must be 0-9999999 (7 digits max)
    return accountNumber >= 0 && accountNumber <= 9999999;
}

int TradingAccount::getCheckDigit() const {
    return (_accountNumber % 10);
}

int TradingAccount::generateCheckDigit(const BrokerId& brokerId) const {
    std::string brokerStr = brokerId.toString();
    int accountPrefix = _accountNumber / 10; // Exclude the last digit (check digit)

    std::string accountPrefixStr = std::to_string(accountPrefix);
    // Pad with leading zeros to ensure 6 digits
    while(accountPrefixStr.length() < 6){
        accountPrefixStr = "0" + accountPrefixStr;
    }

    int weights[] = {1, 3, 7};
    int sum = 0;
    int position = 0;

    // Process BrokerId
    // Mapping: 0-9 → 0-9, A-Z → 10-35, a-z → 36-61
    for (size_t i = 0; i < brokerStr.length(); i++) {
        char ch = brokerStr[i];
        int value;
        
        if(std::isdigit(ch)){
            value = ch - '0'; // 0-9 → 0-9
        } else if(std::isupper(ch)){
            value = ch - 'A' + 10; // A-Z → 10-35
        } else {
            // Must be lowercase (a-z) since BrokerId is validated as alphanumeric
            value = ch - 'a' + 36; // a-z → 36-61
        }
        
        // Multiply by weight and take modulo 10, then add to sum
        sum += (value * weights[position % 3]) % 10;
        position++;
    }

    // Process account prefix 
    for (size_t i = 0; i < accountPrefixStr.length(); i++) {
        int digit = accountPrefixStr[i] - '0';
        sum += (digit * weights[position % 3]) % 10;
        position++;
    }

    // Calculate check digit: (10 - sum % 10) % 10 (special case for sum % 10 == 0)
    int checkDigit = (10 - (sum % 10)) % 10;

    return checkDigit;
}

bool TradingAccount::validateCheckDigit(const BrokerId& brokerId) const {
    return getCheckDigit() == generateCheckDigit(brokerId);
}