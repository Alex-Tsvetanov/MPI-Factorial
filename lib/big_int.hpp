#ifndef __BIG_INTEGER_HPP__
#define __BIG_INTEGER_HPP__

#include <stdio.h> // sprintf
#include <string> // std::string

/**
 * @brief Big Unsigned Integer class with a limit of 10^288.
*/
class BigUInt {
public:
    using digit_t = unsigned int;
    using long_digit_t = unsigned long long;

    /**
     * @brief Number of 10-based digits in a digit.
     * @details Number of 10-based digits in a digit in this Big Unsigned Integer implementation.
     */
    static constexpr unsigned int digit_length = 9;
    
    /**
     * @brief sprintf format string for a digit.
     * @details sprintf format string for a digit in this Big Unsigned Integer implementation.
     */
    static constexpr std::string_view digit_sprintf = "%09d";

    /**
     * @brief Numberic base.
     * @details Numberic base for this Big Unsigned Integer implementation.
     */
    static constexpr digit_t base = 1'000'000'000ull;
     
    /**
     * @brief Number of digits in the numeric base.
     * @details Number of digits in the numeric base for this Big Unsigned Integer implementation.
     */
    static constexpr unsigned long long number_of_digits = 32;

    /**
     * @brief Number of reserved digits in the numeric base.
     * @details Number of reserved digits (in case of multiplication) in the numeric base for this Big Unsigned Integer implementation.
     */
    static constexpr unsigned long long number_of_reserved_digits = 64;

private:
    /**
     * @brief Digits of the Big Unsigned Integer in reverse
     * @details Digits of the Big Unsigned Integer in the given numebric base in reverse
     */
    digit_t digits[number_of_reserved_digits];

public:

    /**
     * @brief Default constructor
     * @details Set the value to 0.
     */
    BigUInt();
    
    /**
     * @brief Default destructor
     */
    ~BigUInt() = default;
    
    /**
     * @brief Explicit constructor Big Unsigned Integer.  
     * @details Sets the value to the given unsigned long long.
    */
    explicit BigUInt(digit_t);

    /**
     * @brief Assigns unsigned long long to Big Unsigned Integer.
     * 
     */
    BigUInt& operator= (digit_t);

    /**
     * @brief  Sums the current number with another Big Unsigned Integer.
     */
    BigUInt& operator += (const BigUInt&);
    
    /**
     * @brief Multiplies the current number with unsigned long long.
     * @details Multiplies the current number with 1-digit Big Unsigned Integer number.
     */
    BigUInt& operator *= (digit_t);

    /**
     * @brief Multiplies the current number with BigUInt.
     * @details Multiplies the current number with multi-digit Big Unsigned Integer number.
     */
    BigUInt& operator *= (const BigUInt&);

    /**
     * @brief Converts the nuber into string.
     */
    std::string to_string () const;
};

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

#endif
