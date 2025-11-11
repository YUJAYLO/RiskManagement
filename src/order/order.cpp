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
    const std::string& priceTypeStr,
    const std::string& forceFlagStr)
    : _brokerId(brokerIdStr)
    , _tradingAccount(accountNumStr, BrokerID(brokerIdStr))
    , _stockId(stockIdStr)
    , _price(priceStr)
    , _quantity(std::stoi(quantityStr))
    , _orderType((orderTypeStr == "B" || orderTypeStr == "Buy" || orderTypeStr == "BUY") 
                 ? OrderType::BUY : OrderType::SELL)
    , _priceType((priceTypeStr == "1") ? PriceType::Market : PriceType::Limit)
    , _forceFlag((forceFlagStr == "Y") ? ForceFlagType::FORCE : ForceFlagType::NO_FORCE)
{   
    // _quantity celing check
    if (_quantity <= 0 || _quantity > 9999 ) {
        throw std::invalid_argument("Quantity must be a positive integer not exceeding 9999.");
    }

    // 使用已經創建的 _stockId,避免重複創建 StockID
    StockInfo stockInfo(_stockId);
    // Checkpoint1: Price Type and Limit Check
    if (_priceType == PriceType::Limit) {
        if(!stockInfo.isBetweenLimit(_price)){
            throw std::invalid_argument("Limit price is out of bounds.");
        }
    }
    
    // Checkpoint2: Stock Stage Warning
    // 2025-11-05 YUJAY: Add force flag check
    if (_forceFlag == ForceFlagType::NO_FORCE) {
        char stage = stockInfo.getStage();
        if (stage == 'W' || stage == 'F') {
            std::cerr << "Warning: Stock is in " << stage << " stage. ";
        }
    }

    // Checkpoint3: Client data validation can be added here if Client class is accessible
    Client client(_brokerId, _tradingAccount);
    if (client.getAccountFlag() != 'Y') {
        throw std::invalid_argument("Trading account is not opened.");
    } 
    
    // Checkpoint4: Order Cost Calculation & tradingQuota Check
    if(_priceType == PriceType::Limit)
        _orderCost = stof(_price.toString())* _quantity;
    else
        _orderCost = stof(stockInfo.getLimitUpPrice().toString()) * _quantity;

    if ((_orderCost + client.getUsedQuota()) > client.getTradingQuota()) {
        throw std::invalid_argument("Order exceeds trading quota.");
    }

    // Checkpoint5: Inventory Check for Sell Orders
    if (_orderType == OrderType::SELL) {
        const Inventory inventory = client.getInventory();
        if (!inventory.hasStock(_stockId) || !inventory.hasEnoughShares(_stockId, _quantity)) {
            throw std::invalid_argument("Insufficient shares to sell.");
        }
    }

}