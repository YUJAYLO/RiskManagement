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
    if( _price >= 1e9f || _price <= -1e9f ) {
        throw std::invalid_argument(priceStr + " => Price must be in (-100000, +100000).");
    }
}

Price& Price::operator=(const std::string& priceStr) {
    Price check(priceStr);
    _price = check._price;

    return *this;
}

bool Price::operator>=(const Price& other) const {
    return _price >= other._price;
}

bool Price::operator<=(const Price& other) const{
    return _price <= other._price;
}

std::string Price::toString() const {
    float val = _price* 1e-4f; // int* float => float

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << val;
    
    return oss.str();
}

// 取得常見的 tick（以 price * 1e4 單位回傳）
int Price::getTickInTenThousand(const Price& price) {
    int p = price._price; // price * 1e4
    // 範例區間（請核對交易所）：
    // [00.00, 10.00) => tick 0.01
    // [10.00, 50.00) => tick 0.05
    // [50.00, 100.00) => tick 0.1
    // [100.00, 500.00) => tick 0.5
    // [500.00, 1000.00) => tick 1.0
    // [1000.00, INTMAX) => tick 5.0

    if (p < 10 * 10000) return 100;         // 0.01 * 1e4
    if (p < 50 * 10000) return 500;         // 0.05
    if (p < 100 * 10000) return 1000;       // 0.1
    if (p < 500 * 10000) return 5000;       // 0.5
    if (p < 1000 * 10000) return 10000;     // 1.0
    return 50000;                           // 5.0
}

// 將 rawPrice（已是 *1e4 的整數）對齊到 tick
// roundUp = true => 向上取整（ceil 到 tick）
// roundUp = false => 向下取整（floor 到 tick）
int Price::alignToTick(int rawPrice, int tickInTenThousand, bool roundUp) {
    if (tickInTenThousand <= 0) return rawPrice;
    if (roundUp) {
        return ((rawPrice + tickInTenThousand - 1) / tickInTenThousand) * tickInTenThousand;
    } else {
        return (rawPrice / tickInTenThousand) * tickInTenThousand;
    }
}

// 漲停：先計算 11/10，再四捨五入，最後向上對齊到 tick（避免超過上限之外的小數）
Price Price::calculateLimitUpPrice(const Price& price) {
    Price limitUp;
    long long v = static_cast<long long>(price._price) * 11; // *11
    // 先除以 10 做四捨五入
    long long rounded = (v + 5) / 10;
    // 依 price 決定 tick，並向上對齊
    int tick = getTickInTenThousand(price);
    limitUp._price = static_cast<int>( alignToTick(static_cast<int>(rounded), tick, true) );
    return limitUp;
}

// 跌停：先計算 9/10，再四捨五入，最後向下對齊到 tick
Price Price::calculateLimitDownPrice(const Price& price) {
    Price limitDown;
    long long v = static_cast<long long>(price._price) * 9; // *9
    long long rounded = (v + 5) / 10;
    int tick = getTickInTenThousand(price);
    limitDown._price = static_cast<int>( alignToTick(static_cast<int>(rounded), tick, false) );
    return limitDown;
}