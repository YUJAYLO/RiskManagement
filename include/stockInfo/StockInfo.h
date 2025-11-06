#ifndef STOCK_INFO_H
#define STOCK_INFO_H

#include "../common/stockID.h"
#include "../common/Price.h"

#include <string>

class StockInfo {
public:
    enum class Stage : char { 
        Normal = ' ',
        Warning = 'W', 
        FutherDisposition = 'F'
    };

private:
    StockID _id;
    std::string _name;
    Price _referencePrice;   // 參考價
    Price _limitUpPrice;     // 漲停價
    Price _limitDownPrice;   // 跌停價
    Stage _stage;            // 股票狀態

    void parseStageStr(const std::string& stageStr);

public:
    StockInfo(const std::string& stockID); // initial constructor

    bool isBetweenLimit() const;
    inline char getStage() const { return static_cast<char>(_stage); }

    // Getter
    inline Price getPrice() const { return _referencePrice; }
    inline Price getLimitUpPrice() const { return _limitUpPrice; }
    inline Price getLimitDownPrice() const { return _limitDownPrice; }
    inline StockID getStockID() const { return _id; }

    std::string toString() const;
};

#endif