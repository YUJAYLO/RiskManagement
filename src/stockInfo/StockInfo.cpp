#include "../../include/stockInfo/StockInfo.h"
#include "../../include/manager/stockDataManager.h"

#include <cctype>
#include <stdexcept>
#include <tuple>

StockInfo::StockInfo(const std::string& stockId) : _id(stockId) {
    std::string stockName;
    std::string stockPrice;
    std::string stageStr;
    tie(stockName, stockPrice, stageStr) = StockDataManager::fetchData(stockId);

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
           ", Stage: " + convertStageToString() + "]";
}

void StockInfo::parseStageStr(const std::string& stageStr) {
    // stageStr.trim()
    size_t start = stageStr.find_first_not_of(" \t\n\r");
    size_t end = stageStr.find_last_not_of(" \t\n\r");

    char ch;  // First character to check
    // If the string is all whitespace, treat it as empty
    if (start == std::string::npos || end == std::string::npos) {
        ch = '\0';
    } else ch = toupper(stageStr[start]);

    switch (ch) {
        case '\0':
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

std::string StockInfo::convertStageToString() const {
    switch (_stage) {
        case Stage::Warning:
            return "W";
        case Stage::FutherDisposition:
            return "F";
        default:
            return "";
    }
}

bool StockInfo::isBetweenLimit() const {
    return _referencePrice >= _limitDownPrice && _referencePrice <= _limitUpPrice;
}