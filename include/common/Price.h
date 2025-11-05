#ifndef PRICE_H
#define PRICE_H

#include <string>

class Price {
private:
    int _price; // 實際值* 10000

    // 新增：取得 tick (以 1e-4 為單位)，以及對齊輔助
    static int getTickInTenThousand(const Price& price); // e.g. 0.01 => 100
    static int alignToTick(int rawPrice, int tickInTenThousand, bool roundUp);

public:
    Price();                        // Default constructor
    Price(const Price& other);      // Copy constructor
    Price(const std::string& priceStr);  // Initial constructor

    Price& operator=(const std::string& priceStr);
    bool operator>=(const Price& other) const;
    bool operator<=(const Price& other) const;

    static Price calculateLimitUpPrice(const Price& price);
    static Price calculateLimitDownPrice(const Price& price);

    std::string toString() const;
};

#endif