#pragma once

#include "moka/moka.h"
#include "../lib/factorial.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

void testCase_PerformanceCheck(Moka::Report& report) {
    Moka::Context output_tests ("Factorial", [](Moka::Context& it) {
        it.describe("check speed difference based on cores used", [](Moka::Context& it) {
            for (int cores = 1 ; cores <= 4 ; cores = cores << 1) {
                for (int i = 1 ; i <= 100 ; i ++) {
                    std::stringstream test_name;
                    test_name << i;
                    test_name << "! using " << cores << " cores";
                    const std::string N_factorial = test_name.str();
                    test_name << " to be executed in 1s";

                    it.should(test_name.str(), [N = i, processes = cores, N_factorial]() {
                        const auto start = std::chrono::high_resolution_clock::now();
                        const std::string output = factorial(N, processes).to_string();
                        const auto end = std::chrono::high_resolution_clock::now();
                        const double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                        must_be_less(time_taken, 0, N_factorial);
                    });
                }
            }
        });
    });
	output_tests.test(report);
}