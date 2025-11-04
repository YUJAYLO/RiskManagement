#include "../include/client.h"

Client::Client(const BrokerId& broker_id,
               const TradingAccount& trading_account,
               bool account_status,
               int trading_quota,
               int used_quota,
               Inventory inventory
            )
            : _brokerID(broker_id),
            _tradingAccount(trading_account),
            account_status_(account_status),
            trading_quota_(trading_quota),
            used_quota_(used_quota),
            inventory_(inventory){}