#ifndef __BIG_INTEGER_FACTORIAL_HPP__
#define __BIG_INTEGER_FACTORIAL_HPP__
#include "./big_int.hpp" // BigUInt
#include <thread> // std::thread
#include <future> // std::mutex
#include <shared_mutex> // std::shared_mutex

/**
 * @brief Used to do multiplication of the threads before they are all completed.
*/
class _AccumulatedResult {
private:

    /**
     * @brief Internal mutex to lock the multiplication process.
    */
    std::mutex processing;
    
    /**
     * @brief Result of the multiplications.
    */
    BigUInt result;

    /**
     * @brief Number of multipliers to be multiplied.
    */
    size_t units;

    /**
     * @brief External mutex to be unlocked after processing.
    */
    std::shared_ptr<std::mutex> accumulating;
    
    /**
     * @brief Upon new multiplier incoming, multiplying the result with it.
    */
    void add(const BigUInt& thread_result) {
        processing.lock();
        result *= thread_result;
        units --;
        if (units == 0) accumulating->unlock();
        processing.unlock();
    } 

public:
    friend BigUInt factorial(unsigned int, unsigned int);
    
    _AccumulatedResult(std::shared_ptr<std::mutex> _accumulating, size_t _processes) : units(_processes), accumulating(_accumulating) {
        result = 1;
    }
};

/**
 * @brief Multiplies all i where i >= start, i <= N, and i%step = start
 * @param start The starting number for the multiplication 
 * @param step The step of increasing of the numbers for the multiplication 
 * @param N The biggest number in the multiplication
 * @return product of all i where i >= start, i <= N, and i%step = start
*/
BigUInt multiply (unsigned int start, unsigned int step, unsigned int N) {
    BigUInt result (1);
    for (unsigned int i = start ; i <= N ; i += step) {
        result *= i;
    }
    return result;
}

/**
 * @brief N! = factorial of N
 * @param N The function will return factorial of this number
 * @param processes The number of parallel processes that the function will run on 
 * @return N! aka factorial of N
*/
BigUInt factorial(const unsigned int N, unsigned int processes) {
    if (processes == 1) {
        BigUInt result (1);
        for (unsigned long long i = 2 ; i <= N ; i ++) {
            result *= i;
        }
        return result;
    }
    else {        
        std::shared_ptr<std::mutex> accumulating = std::make_shared<std::mutex>();
        accumulating->lock(); // locking the processing of the factorial

        std::shared_ptr<_AccumulatedResult> accumulated_result = std::make_shared<_AccumulatedResult>(accumulating, processes);
        
        for (unsigned int i = 1 ; i <= processes ; i ++) {
            std::thread([accumulated_result, i, &processes, &N] {
                accumulated_result->add(multiply(i, processes, N));
            }).detach(); // parallel thread started with the sub-multiplication
        }

        accumulating->lock(); // waiting for all the processing to be over

        return accumulated_result->result;
    }
}
#endif