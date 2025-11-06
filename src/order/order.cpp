#include "../../include/order/order.h"
#include "../../include/client/client.h"

#include <stdexcept>
#include <iostream>

Order::Order(
    const std::string& brokerIdStr,
    const std::string& accountNumStr,
    const std::string& stockIdStr,
    const std::string& priceStr,
    const std::string& quantityStr,
    const std::string& orderTypeStr,
    const std::string& priceTypeStr)
    : _brokerId(brokerIdStr)
    , _tradingAccount(accountNumStr, BrokerId(brokerIdStr))
    , _stockId(stockIdStr)
    , _stockInfo(stockIdStr)
    , _price(priceStr)
    , _quantity(std::stoi(quantityStr))
    , _orderType((orderTypeStr == "B" || orderTypeStr == "Buy" || orderTypeStr == "BUY") 
                 ? OrderType::BUY : OrderType::SELL)
    , _priceType((priceTypeStr == "1") ? PriceType::Market : PriceType::Limit)
    , _forceFlag(ForceFlagType::NO_FORCE)
{   
    // Checkpoint1: Price Type and Limit Check
    if (_priceType == PriceType::Limit) {
        if(!_stockInfo.isBetweenLimit()){
            throw std::invalid_argument("Limit price is out of bounds.");
        }
    }
    
    // Checkpoint2: Stock Stage Warning
    char stage = _stockInfo.getStage();
    if (stage == 'W' || stage == 'F') {
        std::cerr << "Warning: Stock is in " << stage << " stage. ";
    }

    // Checkpoint3: Client data validation can be added here if Client class is accessible
    Client _client(_brokerId, _tradingAccount);
    if (_client.getAccountFlag() != 'Y') {
        throw std::invalid_argument("Trading account is not opened.");
    
}