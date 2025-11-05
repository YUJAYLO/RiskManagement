#include "../../include/order/order.h"

Order::Order(
    const BrokerId& brokerId, 
    const TradingAccount& tradingAccount,
    const Stock& stock,
    double price,
    int quantity,
    OrderType orderType,
    PriceType priceType,
    const Timestamp& orderTime,
    const ForceFlagType& forceFlag): 
      _brokerId(brokerId),           
      _tradingAccount(tradingAccount),
      _stockID(stock.getStockID()),
      _price(price),
      _quantity(quantity),
      _orderType(orderType),
      _priceType(priceType),
      _orderTime(orderTime),
      _forceFlag(forceFlag)
    { 
        if (priceType == PriceType::Limit) {
            if (!stock.isBetweenLimit(price)) {
                throw std::invalid_argument("Limit price is out of stock limit range.");
            }
        }
}
