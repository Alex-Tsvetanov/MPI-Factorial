#include "./moka/moka.h"
#include <iostream>
#include "./output_check.hpp"
#include "./performance_check.hpp"

int main() {
    // unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);
    
    std::cout << "===============================  Testing  ===============================" << "\n";

    Moka::Report report;
	testCase_OutputCheck(report);
	testCase_PerformanceCheck(report);
    report.print();

    return 0;
}