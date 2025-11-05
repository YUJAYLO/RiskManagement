#ifndef STOCK_INFO_H
#define STOCK_INFO_H

#include "../common/stockID.h"
#include "../common/Price.h"

class StockInfo {
public:
    enum class Stage { Normal, Warning, FutherDisposition};

private:
    StockId _id;
    std::string _name;
    Price _referencePrice;   // 參考價
    Price _limitUpPrice;     // 漲停價
    Price _limitDownPrice;   // 跌停價
    Stage _stage;      // 股票狀態

    void parseStageStr(const std::string& stageStr);

public:
    StockInfo(const std::string& stockId); // initial constructor

    bool isBetweenLimit() const;
    std::string convertStageToString() const; // helper function

    // Getter
    Price getPrice() const { return _referencePrice; }
    StockId getStockID() const { return _id; }

    std::string toString() const;
};

#endif