#ifndef __BIG_INTEGER_HPP__
#define __BIG_INTEGER_HPP__

#include <iostream> // std::ostream
#include <iomanip> // std::setw, std::setfill

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
     * @brief Prints the number to std::ostream.
     */
    friend std::ostream& operator << (std::ostream&, const BigUInt&);
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
        BigUInt row (0);
        for (size_t j = 0 ; j < this->number_of_digits ; j ++)
            row.digits[j] = this->digits[j];
        row *= value.digits[i];
        for (size_t j = this->number_of_digits ; j >= 0 ; j --) {
            row.digits[j + i] = row.digits[j];
            if (j == 0) break;
        }
        for (size_t j = 0 ; j < i ; j ++) row.digits [j] = 0;
        result += row;
    }
    for (size_t i = 0 ; i < this->number_of_digits ; i ++) {
        this->digits[i] = result.digits[i];
    }
    return *this;
}

std::ostream& operator << (std::ostream& out, const BigUInt& value) {
    size_t i;
    for (i = value.number_of_digits - 1 ; value.digits[i] == 0 && i > 0 ; i --) {}
    out << value.digits[i];
    if (i != 0)
        for (i -- ; i >= 0 ; i --) {
            out << std::setw(value.digit_length) << std::setfill('0') << value.digits[i];
            if (i == 0) break; 
        }
    return out;
}

#endif
