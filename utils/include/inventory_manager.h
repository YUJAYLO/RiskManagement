#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "../../models/include/inventory.h"
#include "../../common/include/brokerID.h"
#include "../../common/include/tradingAccount.h"
#include <unordered_map>
#include <string>

class InventoryManager {
    private:

        std::unordered_map<std::string, Inventory> _clientInventories;
        
        std::string generateClientKey(const BrokerId& brokerId, const TradingAccount& account) const;
        
    public:
        InventoryManager() = default;
        
        bool loadInventoryData(const std::string& filename);
        bool loadInventoryFromDatabase(); // TODO
        
        const Inventory* getClientInventory(const BrokerId& brokerId, const TradingAccount& account) const;
        Inventory* getClientInventory(const BrokerId& brokerId, const TradingAccount& account);
        
        // 庫存操作
        bool hasEnoughShares(const BrokerId& brokerId, const TradingAccount& account, 
                            const StockID& stockCode, int requiredShares) const;
        
        bool useShares(const BrokerId& brokerId, const TradingAccount& account, 
                    const StockID& stockCode, int shares);
        
        bool releaseShares(const BrokerId& brokerId, const TradingAccount& account, 
                        const StockID& stockCode, int shares);
        
        // 新增客戶庫存
        void addClientInventory(const BrokerId& brokerId, const TradingAccount& account, 
                            const Inventory& inventory);
        
        bool saveInventoryToDatabase() const; // 未來可擴展
                
        void clear();
};

#endif