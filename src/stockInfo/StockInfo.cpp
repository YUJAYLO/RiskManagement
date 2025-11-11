#include "../../include/stockInfo/StockInfo.h"
#include "../../include/manager/dataManager.h"
#include "../../include/utils/StringUtils.h"

#include <cctype>
#include <stdexcept>
#include <tuple>
#include <iostream>

// Constructor from StockID object - avoids creating duplicate StockID
StockInfo::StockInfo(const StockID& stockID) : _id(stockID) {
    std::string stockName;
    std::string stockPrice;
    std::string stageStr;
    std::tie(stockName, stockPrice, stageStr) = DataManager::fetchStockData(_id.toString());

    _name = stockName;
    _referencePrice = Price(stockPrice);
    _limitUpPrice = Price::calculateLimitUpPrice(_referencePrice);
    _limitDownPrice = Price::calculateLimitDownPrice(_referencePrice);
    parseStageStr(stageStr);
}

std::string StockInfo::toString() const {
    return "StockInfo[ID: " + _id.toString() +
           ", Name: " + _name +
           ", Reference Price: " + _referencePrice.toString() +
           ", Limit Up Price: " + _limitUpPrice.toString() +
           ", Limit Down Price: " + _limitDownPrice.toString() +
           ", Stage: " + std::to_string(getStage()) + "]";
}

void StockInfo::parseStageStr(const std::string& stageStr) {
    // stageStr.trim()
    size_t start = stageStr.find_first_not_of(" \t\n\r");
    size_t end = stageStr.find_last_not_of(" \t\n\r");

    char ch;  // First character to check
    // If the string is all whitespace, treat it as empty
    if (start == std::string::npos || end == std::string::npos) {
        ch = 'N';
    } else ch = toupper(stageStr[start]);

    switch (ch) {
        case 'N':
            _stage = Stage::Normal;
            break;
        case 'W':
            _stage = Stage::Warning;
            break;
        case 'F':
            _stage = Stage::FutherDisposition;
            break;
        default:
            throw std::invalid_argument("Invalid stage string: " + stageStr);
    }
}

bool StockInfo::isBetweenLimit(const Price& price) const {
    return price >= _limitDownPrice && price <= _limitUpPrice;
}