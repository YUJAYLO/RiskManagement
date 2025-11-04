#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../common/include/stockID.h"
#include <unordered_map>
#include <vector>

// 單一股票的庫存項目
class InventoryItem {
private:
    StockID _stockCode;
    int _totalShares;
    int _usedShares;

public:
    InventoryItem(const StockID& stockCode, int totalShares = 0, int usedShares = 0);
    
    // 基本存取方法
    const StockID& getStockCode() const { return _stockCode; }
    int getTotalShares() const { return _totalShares; }
    int getUsedShares() const { return _usedShares; }
    int getAvailableShares() const { return _totalShares - _usedShares; }
    
    // 庫存操作
    bool hasEnoughShares(int requiredShares) const;
    bool addShares(int shares);  // 買入增加庫存
    bool useShares(int shares);  // 賣出時使用庫存
    bool releaseShares(int shares);  // 委託取消時釋放庫存
    
    // 設定方法（用於從資料庫載入）
    void setTotalShares(int shares) { _totalShares = shares; }
    void setUsedShares(int shares) { _usedShares = shares; }
};

// 客戶的完整庫存（多檔股票）
class Inventory {
private:
    std::unordered_map<std::string, InventoryItem> _items; // key: stockCode

public:
    Inventory() = default;
    
    // 庫存項目管理
    void addItem(const InventoryItem& item);
    const InventoryItem* getItem(const StockID& stockCode) const;
    InventoryItem* getItem(const StockID& stockCode);
    
    // 庫存操作
    bool hasStock(const StockID& stockCode) const;
    bool hasEnoughShares(const StockID& stockCode, int requiredShares) const;
    bool useShares(const StockID& stockCode, int shares);
    bool releaseShares(const StockID& stockCode, int shares);
    
    // 查詢方法
    std::vector<InventoryItem> getAllItems() const;
    int getTotalStockCount() const { return _items.size(); }
    
    // 清空庫存
    void clear() { _items.clear(); }
};

#endif