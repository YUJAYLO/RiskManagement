#include "../../include/common/brokerID.h"
#include "../../include/utils/StringUtils.h"

#include <stdexcept>

BrokerID::BrokerID(const std::string& id) : _id(id) {
    if(!isValid()){
        throw std::invalid_argument("Invalid Broker ID format");
    }
}

std::string BrokerID::toString() const {
    return _id;
}

bool BrokerID::isValid() const {
    if (_id.length() != 4)
        return false;

    return StringUtils::isAlphanumeric(_id);
}