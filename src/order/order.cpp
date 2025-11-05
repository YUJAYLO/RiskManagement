#include "../../include/order/order.h"
#include <stdexcept>

Order::Order(
    const std::string& brokerIdStr,
    const std::string& accountNumStr,
    const std::string& stockIdStr,
    const std::string& priceStr,
    const std::string& quantityStr,
    const std::string& orderTypeStr,
    const std::string& priceTypeStr,
    const std::string& orderTimeStr,
    const std::string& forceFlagStr)
    : _brokerId(brokerIdStr)
    , _tradingAccount(accountNumStr, BrokerId(brokerIdStr))
    , _stockId(stockIdStr)
    , _stockInfo(stockIdStr)
    , _price(priceStr)
    , _quantity(std::stoi(quantityStr))
    , _orderType((orderTypeStr == "B" || orderTypeStr == "Buy" || orderTypeStr == "BUY") 
                 ? OrderType::BUY : OrderType::SELL)
    , _priceType((priceTypeStr == "1") ? PriceType::Market : PriceType::Limit)
    , _forceFlag((forceFlagStr == "Y") ? ForceFlagType::FORCE : ForceFlagType::NO_FORCE)
    , _orderTime(orderTimeStr)
{   
    // 檢核1: 限價委託單檢核委託價格是否在漲跌幅內
    if (_priceType == PriceType::Limit) {

    }
    
    // 檢核2: 強迫旗標與股票狀態檢查
    if (_forceFlag == ForceFlagType::NO_FORCE) {

    }
}