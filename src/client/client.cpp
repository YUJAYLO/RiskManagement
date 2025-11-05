#include "../../include/client/client.h"

Client::Client(const BrokerId& broker_id,
               const TradingAccount& trading_account,
               accountFlag accountFlag,
               int tradingQuota,
               int usedQuota,
               Inventory inventory
            )
            : _brokerID(broker_id),
            _tradingAccount(trading_account),
            accountFlag_(accountFlag),
            tradingQuota_(tradingQuota),
            usedQuota_(usedQuota),
            inventory_(inventory){}