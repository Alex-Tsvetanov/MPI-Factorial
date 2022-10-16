#pragma once

#include "moka/moka.h"
#include "../lib/factorial.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void testCase_OutputCheck(Moka::Report& report) {
    Moka::Context output_tests ("Factorial", [](Moka::Context& it) {
        it.describe("answers with correct numbers", [](Moka::Context& it) {
            for (int i = 1 ; i <= 100 ; i ++) {
                std::stringstream test_name;
                test_name << i;
                std::ifstream correct_output_file(std::string("outs/") + (test_name.str() + ".out").c_str());
                const std::string correct_output( (std::istreambuf_iterator<char>(correct_output_file) ),
                                                (std::istreambuf_iterator<char>()) );
                test_name << "! be equal to " << correct_output;

                it.should(test_name.str() + " using 1 core", [N = i, correct_output]() {
                    const std::string output = factorial(N, 1).to_string();
                    must_be_equal(output.c_str(), correct_output.c_str(), "");
                });

                it.should(test_name.str() + " using 2 cores", [N = i, correct_output]() {
                    const std::string output = factorial(N, 2).to_string();
                    must_be_equal(output.c_str(), correct_output.c_str(), "");
                });

                it.should(test_name.str() + " using 4 cores", [N = i, correct_output]() {
                    const std::string output = factorial(N, 4).to_string();
                    must_be_equal(output.c_str(), correct_output.c_str(), "");
                });
            }
        });
    });
	output_tests.test(report);
}