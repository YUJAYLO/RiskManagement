#include "../../include/common/tradingAccount.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

TradingAccount::TradingAccount(const std::string& accountNumStr, const BrokerID& brokerId) {
    if(accountNumStr.length() != 7)// Check length
        throw std::invalid_argument("Account number must be exactly 7 digits long.");

    if(!isValid(std::stoi(accountNumStr)))// Validate account number
        throw std::invalid_argument("Invalid account number. Account number must be 0-9999999 (7 digits max)");
    _accountNumber = std::stoi(accountNumStr);

    if(validateCheckDigit(brokerId) == false)// Validate check digit
        throw std::invalid_argument("Invalid check digit for the given BrokerId and input accountNumStr.");
}

bool TradingAccount::isValid(int accountNumber) const{
    // Account number must be 0-9999999 (7 digits max)
    return accountNumber >= 0 && accountNumber <= 9999999;
}

int TradingAccount::getCheckDigit() const {
    return (_accountNumber % 10);
}

std::string TradingAccount::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(7) << _accountNumber;
    return oss.str();
}

int TradingAccount::generateCheckDigit(const BrokerID& brokerId) const {
    std::string broker = brokerId.toString();
    std::string account = this->toString();
    account.pop_back(); // 刪除原始檢查碼

    int checkDigit=0;
    int weight[] = {1, 3, 7};

    // Mapping: 0-9 → 0-9, A-Z → 10-35, a-z → 36-61
    // 計算券商代號
    for(int i=0; i<broker.size(); i++) {
        char c = broker[i];
        int val;

        if(isdigit(c)) {
            val = c - '0';
        } else if(isupper(c)) {
            val = c - 'A' + 10;
        } else {
            val = c - 'a' + 36;
        }

        checkDigit += (val* weight[i%3]) % 10;
    }
    // 計算交易帳號前6碼
    for(int i=0; i<account.size(); i++) {
        int val = account[i] - '0';

        checkDigit += (val* weight[i%3]) % 10;
    }
    checkDigit = (10 - checkDigit%10) % 10;
    // std::cout << "Generated Check Digit: " << checkDigit << std::endl;

    return checkDigit;
}

bool TradingAccount::validateCheckDigit(const BrokerID& brokerId) const {
    return getCheckDigit() == generateCheckDigit(brokerId);
}