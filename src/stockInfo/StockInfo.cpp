#include "../../include/stockInfo/StockInfo.h"

#include <cctype>
#include <stdexcept>

StockInfo::StockInfo(const std::string& stockId,
                     const std::string& stockName,
                     const std::string& stockPrice,
                     const std::string& stageStr)
    : _id(stockId),
      _name(stockName),
      _referencePrice(stockPrice)
{
    // 2025.11.04 YUJAY: remember to deal with stockName.trim().
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