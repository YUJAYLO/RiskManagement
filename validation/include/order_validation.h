#ifndef ORDER_VALIDATION_H
#define ORDER_VALIDATION_H

class OrderValidation {
    private:
        bool _isValid;

    public:
        OrderValidation(); // Default constructor
        OrderValidation(bool isValid); // Initial constructor
        OrderValidation(const OrderValidation& other); // Copy constructor

        OrderValidation& operator=(const OrderValidation& other);

        bool isValid() const;
        void setValid(bool isValid);
};

#endif