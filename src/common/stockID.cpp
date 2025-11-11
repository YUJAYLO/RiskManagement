#include "../../include/common/stockID.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <iostream>

StockID::StockID(const StockID& other) : _id(other._id) {}

StockID::StockID(const std::string& id) : _id(id) {
    if(!isValid()) {
        throw std::invalid_argument(id + " => StockID must be consist of 4~6 character of alphanumber.");
    }
}

std::string StockID::toString() const {
    // 移除尾部空白,回傳原始股票代碼
    std::string result = _id;
    size_t end = result.find_last_not_of(' ');
    if (end != std::string::npos) {
        result = result.substr(0, end + 1);
    }
    return result;
}

bool StockID::isValid() {
    if(_id.size() < 4 || _id.size() > 6) return false;

    // 處理補值
    while(_id.size() > 0 && _id.back() == ' ' ) _id.pop_back();

    return all_of(_id.begin(), _id.end(), [](unsigned char c){
        return isalnum(c);
    });
}

