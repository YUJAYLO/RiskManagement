#include "../../include/common/Price.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

Price::Price() : _price(638000) {} // 0050 價格
Price::Price(const Price& other) : _price(other._price) {}
Price::Price(const std::string& priceStr) {
    float val;
    try {
        size_t pos;
        val = stof(priceStr, &pos)* 1e4f; // 只有字串頭為非數值 (^\D) 才會 throw error

        if (pos < priceStr.length()) {
            throw std::invalid_argument("error");
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument(priceStr + " => Price must be consist of numeric character.");
    }
    _price = static_cast<int>(val);
}

Price& Price::operator=(const std::string& priceStr) {
    Price check(priceStr);
    _price = check._price;

    return *this;
}

std::string Price::toString() const {
    float val = _price* 1e-4f; // int* float => float

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << val;
    
    return oss.str();
}