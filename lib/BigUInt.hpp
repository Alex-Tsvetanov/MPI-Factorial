#ifndef __BIG_INTEGER_HPP__
#define __BIG_INTEGER_HPP__

#include <stdio.h> // sprintf
#include <string> // std::string
#include <string_view> // std::string_view

namespace BigUInt {
    using digit_t = unsigned int;
    using long_digit_t = unsigned long long;

    /**
     * @brief Number of 10-based digits in a digit.
     * @details Number of 10-based digits in a digit in this Big Unsigned Integer implementation.
     */
    constexpr unsigned int digit_length = 9;

    /**
     * @brief sprintf format string for the first digit of the number.
     * @details sprintf format string for the first digit of the number (no leading 0s) in this Big Unsigned Integer implementation.
     */
    constexpr std::string_view leading_digit_sprintf = "%u";

    /**
     * @brief sprintf format string for a digit.
     * @details sprintf format string for a digit (w/ leading 0s) in this Big Unsigned Integer implementation.
     */
    constexpr std::string_view digit_sprintf = "%09u";

    /**
     * @brief Numberic base.
     * @details Numberic base for this Big Unsigned Integer implementation.
     */
    constexpr digit_t base = 1'000'000'000;

    /**
     * @brief Number of digits in the numeric base.
     * @details Number of digits in the numeric base for this Big Unsigned Integer implementation.
     */
    constexpr unsigned long long max_number_of_digits = 1<<18;

    /**
     * @brief Number of reserved digits in the numeric base.
     * @details Number of reserved digits (in case of multiplication) in the numeric base for this Big Unsigned Integer implementation.
     */
    constexpr unsigned long long number_of_reserved_digits = max_number_of_digits << 1;

    /**
     * @brief Big Unsigned Integer class with a limit of 10^4718592-1.
    */
    struct BigUInt {
        /**
         * @brief Digits of the Big Unsigned Integer in reverse
         * @details Digits of the Big Unsigned Integer in the given numebric base in reverse
         */
        digit_t digits[number_of_reserved_digits];

        /**
         * @brief Number of digits in the numeric base.
         * @details Number of digits in the numeric base for this Big Unsigned Integer implementation.
         */
        unsigned long long number_of_digits;

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
        std::string to_string() const;
    };
}

#endif
