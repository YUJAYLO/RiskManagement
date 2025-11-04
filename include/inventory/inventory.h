#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../common/include/stockID.h"
#include <unordered_map>

class InventoryItem {
    private:
        StockID _stockID; 
        int _totalShares; // Total shares held
        int _usedShares; // Shares currently committed or used

    public:
        InventoryItem(const StockID& stockID, int totalShares, int usedShares)
            : _stockID(stockID), _totalShares(totalShares), _usedShares(usedShares){};
        
        const StockID& getStockID() const { return _stockID; }
        int getTotalShares() const { return _totalShares; }
        int getUsedShares() const { return _usedShares; }
        int getAvailableShares() const { return _totalShares - _usedShares; }
        
    private:
        friend class Inventory;  
        
        // For Inventory to manage shares
        bool hasEnoughShares(int requiredShares) const;
        bool addShares(int shares);
        bool useShares(int shares);
        bool releaseShares(int shares);
};

class Inventory {
    private:
        std::unordered_map<std::string, InventoryItem> _inventoryStock; // key: stockID

    public:
        Inventory() = default;
        
        // Add a new inventory item
        void add(const InventoryItem& item);
        
        // Inventory management methods
        bool hasStock(const StockID& stockID) const;
        bool hasEnoughShares(const StockID& stockID, int requiredShares) const;
        bool addShares(const StockID& stockID, int shares);        // Add shares to inventory after buy
        bool useShares(const StockID& stockID, int shares);        // Commit shares for selling
        bool releaseShares(const StockID& stockID, int shares);    // Release committed shares after sell or cancel
        
        // Query methods(read-only)
        const InventoryItem* get(const StockID& stockID) const;
        void printInventory() const;
        
        // Clear inventory
        void clear() { _inventoryStock.clear(); }
};

#endif