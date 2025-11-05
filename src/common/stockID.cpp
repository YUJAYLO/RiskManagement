#include "../../include/common/stockID.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>

StockId::StockId() : _id("0050") {
    _id.resize(6, 0);
}
StockId::StockId(const StockId& other) : _id(other._id) {}
StockId::StockId(const std::string& id) : _id(id) {
    if(!isValid()) {
        throw std::invalid_argument(id + " => StockId must be consist of 4~6 character of alphanumber.");
    } else {
        _id.resize(6, 0);
    }
}

StockId& StockId::operator=(const std::string& id) {
    StockId check(id); // 檢查指派的 StockId 是否合法
    _id = check._id;

    return *this;
}

std::string StockId::toString() const {
    return _id;
}

bool StockId::isValid() {
    if(_id.size() < 4 || _id.size() > 6) return false;

    // 處理補值
    while(_id.size() > 0 && _id.back() == 0 ) _id.pop_back();

    return all_of(_id.begin(), _id.end(), [](unsigned char c){
        return isalnum(c);
    });
}

bool StockId::operator==(const StockId& other) const {
    return _id == other._id;
}

bool StockId::operator<(const StockId& other) const {
    return _id < other._id;
}