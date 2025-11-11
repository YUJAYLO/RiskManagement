#include "../../include/common/stockID.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>

StockID::StockID() : _id("0050") {
    _id.resize(6, 0);
}
StockID::StockID(const StockID& other) : _id(other._id) {}
StockID::StockID(const std::string& id) : _id(id) {
    if(!isValid()) {
        throw std::invalid_argument(id + " => StockID must be consist of 4~6 character of alphanumber.");
    } else {
        _id.resize(6, ' ');
    }
}

StockID& StockID::operator=(const std::string& id) {
    StockID check(id); // 檢查指派的 StockID 是否合法
    _id = check._id;

    return *this;
}

std::string StockID::toString() const {
    return _id;
}

bool StockID::isValid() {
    if(_id.size() < 4 || _id.size() > 6) return false;

    // 處理補值
    while(_id.size() > 0 && _id.back() == ' ' ) _id.pop_back();

    return all_of(_id.begin(), _id.end(), [](unsigned char c){
        return isalnum(c);
    });
}

bool StockID::operator==(const StockID& other) const {
    return _id == other._id;
}

bool StockID::operator<(const StockID& other) const {
    return _id < other._id;
}