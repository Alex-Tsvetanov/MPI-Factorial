#include "./big_int.hpp"

BigUInt::BigUInt() {
    for (size_t i = 0 ; i < this->number_of_digits ; i ++)
        digits [i] = 0;
}
BigUInt::BigUInt (digit_t value) {
    for (size_t i = 0 ; i < this->number_of_digits ; i ++)
        digits [i] = 0;
    digits[0] = value;
}
BigUInt& BigUInt::operator = (digit_t value) {
    for (size_t i = 0 ; i < this->number_of_digits ; i ++)
        digits [i] = 0;
    digits[0] = value;
    return *this;
}
BigUInt& BigUInt::operator += (const BigUInt& value) {
    long_digit_t sum = 0;
    for (size_t i = 0 ; i < this->number_of_digits ; i ++) {
        sum = ((long_digit_t)this->digits[i]) + value.digits[i];
        if (sum >= base) {
            sum -= base;
            this->digits[i + 1] ++;
        }
        this->digits[i] = sum;
    }
    return *this;
}
BigUInt& BigUInt::operator *= (digit_t value) {
    BigUInt result (0);
    long_digit_t product = 1;
    for (size_t i = 0 ; i < this->number_of_digits ; i ++) {
        product = ((long_digit_t)result.digits[i]) + ((long_digit_t)this->digits[i]) * value;
        if (product >= base) {
            result.digits[i + 1] += product / base;
            product %= base;
        }
        result.digits[i] = product;
    }
    for (size_t i = 0 ; i < this->number_of_digits ; i ++) {
        this->digits[i] = result.digits[i];
    }
    return *this;
}    
BigUInt& BigUInt::operator *= (const BigUInt& value) {
    BigUInt result (0);
    long_digit_t product = 1;
    for (size_t i = 0 ; i < this->number_of_digits ; i ++) {
        if (value.digits[i] == 0) continue;
        for (size_t j = 0 ; j < this->number_of_digits ; j ++) {
            long_digit_t current_digit = result.digits[i + j];
            long_digit_t left_current_digit = this->digits[j];
            long_digit_t right_current_digit = value.digits[i];
            product = current_digit + left_current_digit * right_current_digit;
            if (product >= base) {
                result.digits[i + j + 1] += product / base;
                product %= base;
            }
            result.digits[i + j] = product;
        }
    }
    for (size_t i = 0 ; i < this->number_of_digits ; i ++) {
        this->digits[i] = result.digits[i];
    }
    return *this;
}

std::string BigUInt::to_string () const {
    char answer[number_of_reserved_digits * digit_length];
    size_t i;
    for (i = number_of_digits - 1 ; this->digits[i] == 0 && i > 0 ; i --) {}
    int len = sprintf(answer, "%u", this->digits[i]);
    if (i != 0)
        for (i -- ; i >= 0 ; i --) {
            len += sprintf(answer + len, digit_sprintf.data(), this->digits[i]);
            if (i == 0) break; 
        }
    return std::string(answer);
}