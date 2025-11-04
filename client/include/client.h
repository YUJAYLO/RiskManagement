#ifndef CLIENT_H
#define CLIENT_H

#include "../../common/include/brokerID.h"
#include "../../common/include/tradingAccount.h"
#include "../../models/include/inventory.h"

#include <map>
#include <string>

class Client {
    private:
        BrokerId _brokerID;             // 券商代號
        TradingAccount _tradingAccount; // 交易帳號
        bool account_status_;           // 開戶旗標
        int trading_limit_;             // 買賣額度
        int used_limit_;                // 已使用額度
        Inventory inventory_;           // 庫存資料
        
    public:
        Client();

};

#endif