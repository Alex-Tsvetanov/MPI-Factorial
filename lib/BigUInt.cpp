#include "./BigUInt.hpp"

namespace BigUInt {
    BigUInt::BigUInt() {
        for (size_t i = 0; i < max_number_of_digits; i++)
            digits[i] = 0;
    }
    BigUInt::BigUInt(digit_t value) {
        this->number_of_digits = 1;
        for (size_t i = 0; i < max_number_of_digits; i++)
            digits[i] = 0;
        digits[0] = value;
    }
    BigUInt& BigUInt::operator = (digit_t value) {
        this->number_of_digits = 1;
        for (size_t i = 0; i < max_number_of_digits; i++)
            digits[i] = 0;
        digits[0] = value;
        return *this;
    }
    BigUInt& BigUInt::operator += (const BigUInt& value) {
        long_digit_t sum = 0;
        for (size_t i = 0; i < this->number_of_digits; i++) {
            sum = ((long_digit_t)this->digits[i]) + value.digits[i];
            if (sum >= base) {
                sum -= base;
                this->digits[i + 1] ++;
                if (i == this->number_of_digits - 1) this->number_of_digits++;
            }
            this->digits[i] = sum;
        }
        return *this;
    }
    BigUInt& BigUInt::operator *= (digit_t value) {
        BigUInt result(0);
        long_digit_t product = 1;
        for (size_t i = 0; i < this->number_of_digits; i++) {
            product = ((long_digit_t)result.digits[i]) + ((long_digit_t)this->digits[i]) * value;
            if (product >= base) {
                result.digits[i + 1] += product / base;
                result.number_of_digits = (result.number_of_digits < i + 2) ? (i + 2) : result.number_of_digits;
                product %= base;
            }
            result.digits[i] = product;
            result.number_of_digits = (result.number_of_digits < i + 1) ? (i + 1) : result.number_of_digits;
        }
        for (size_t i = 0; i < result.number_of_digits; i++) {
            this->digits[i] = result.digits[i];
        }
        this->number_of_digits = result.number_of_digits;
        return *this;
    }
    BigUInt& BigUInt::operator *= (const BigUInt& value) {
        BigUInt result(0);
        long_digit_t product = 1;
        for (size_t i = 0; i < value.number_of_digits; i++) {
            if (value.digits[i] == 0) continue;
            for (size_t j = 0; j < this->number_of_digits; j++) {
                long_digit_t current_digit = result.digits[i + j];
                long_digit_t left_current_digit = this->digits[j];
                long_digit_t right_current_digit = value.digits[i];
                product = current_digit + left_current_digit * right_current_digit;
                if (product >= base) {
                    result.digits[i + j + 1] += product / base;
                    result.number_of_digits = (result.number_of_digits < i + j + 2) ? (i + j + 2) : result.number_of_digits;
                    product %= base;
                }
                result.digits[i + j] = product;
                result.number_of_digits = (result.number_of_digits < i + j + 1) ? (i + j + 1) : result.number_of_digits;
            }
        }
        for (size_t i = 0; i < result.number_of_digits; i++) {
            this->digits[i] = result.digits[i];
        }
        this->number_of_digits = result.number_of_digits;
        return *this;
    }

    std::string BigUInt::to_string() const {
        char* answer = new char[this->number_of_digits * digit_length];
        size_t i;
        for (i = this->number_of_digits - 1; this->digits[i] == 0 && i > 0; i--) {}
        int len = sprintf(answer, leading_digit_sprintf.data(), this->digits[i]);
        if (i != 0)
            for (i--; i >= 0; i--) {
                len += sprintf(answer + len, digit_sprintf.data(), this->digits[i]);
                if (i == 0) break;
            }
        std::string str_answer = std::string(answer);
        delete[] answer;
        return str_answer;
    }
}
