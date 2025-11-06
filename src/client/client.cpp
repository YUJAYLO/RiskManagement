#include "../../include/client/client.h"
#include "../../include/manager/dataManager.h"

#include <tuple>

Client::Client(const BrokerID& broker_id,
               const TradingAccount& trading_account)
   : _brokerID(broker_id),
     _tradingAccount(trading_account)
{
   std::string accountFlagStr;
   std::string tradingQuotaStr;
   std::string usedQuotaStr;
   std::tie(accountFlagStr, tradingQuotaStr, usedQuotaStr) =
       DataManager::fetchClientInfo(broker_id.toString(), trading_account.toString());

   _accountFlag = (accountFlagStr == "Y") ? accountFlag::OPENED :
                  (accountFlagStr == "E") ? accountFlag::CLOSED : accountFlag::NOT_OPENED;
   _tradingQuota = std::stof(tradingQuotaStr);
   _usedQuota =  std::stof(usedQuotaStr);

   std::vector<std::tuple<std::string, std::string, std::string>> inventoryData;
   inventoryData = DataManager::fetchClientInventory(broker_id.toString(), trading_account.toString());
   for (const auto& item : inventoryData) {
      std::string stockIDStr = std::get<0>(item);
      std::string quantityStr = std::get<1>(item);
      std::string averagePriceStr = std::get<2>(item);
      
      _inventory.add(InventoryItem(stockIDStr, quantityStr, averagePriceStr));
   }
}