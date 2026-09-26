#include "BigInt.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    void expectTrue(const std::string &name, bool condition)
    {
        if (!condition)
        {
            std::cerr << "FAILED: " << name << std::endl;
            std::exit(1);
        }
    }

    void test_output_basic_values()
    {
        std::ostringstream out;

        out << BigInt(0);
        expectTrue("0 prints as 0", out.str() == "0");

        out.str("");
        out.clear();
        out << BigInt(7);
        expectTrue("positive value prints correctly", out.str() == "7");

        out.str("");
        out.clear();
        out << BigInt(-7);
        expectTrue("negative value prints with minus sign", out.str() == "-7");

        out.str("");
        out.clear();
        out << BigInt("123456789");
        expectTrue("large positive value prints correctly", out.str() == "123456789");

        out.str("");
        out.clear();
        out << BigInt("-123456789");
        expectTrue("large negative value prints correctly", out.str() == "-123456789");
    }

    void test_output_normalization_cases()
    {
        std::ostringstream out;

        out << BigInt("0000");
        expectTrue("all-zero value prints as 0", out.str() == "0");

        out.str("");
        out.clear();
        out << BigInt("000123");
        expectTrue("leading zeros are removed on output", out.str() == "123");

        out.str("");
        out.clear();
        out << BigInt("-000123");
        expectTrue("negative leading zeros are removed on output", out.str() == "-123");
    }

    void test_input_basic_values()
    {
        std::istringstream in("123");
        BigInt value(0);
        in >> value;
        expectTrue("reads positive integer", value == BigInt("123"));

        std::istringstream in2("-42");
        BigInt value2(0);
        in2 >> value2;
        expectTrue("reads negative integer", value2 == BigInt("-42"));

        std::istringstream in3("000987");
        BigInt value3(0);
        in3 >> value3;
        expectTrue("reads positive integer with leading zeros", value3 == BigInt("987"));

        std::istringstream in4("-000987");
        BigInt value4(0);
        in4 >> value4;
        expectTrue("reads negative integer with leading zeros", value4 == BigInt("-987"));
    }

    void test_input_large_values()
    {
        std::istringstream in("98765432101234567890");
        BigInt value(0);
        in >> value;
        expectTrue("reads large positive integer", value == BigInt("98765432101234567890"));

        std::istringstream in2("-98765432101234567890");
        BigInt value2(0);
        in2 >> value2;
        expectTrue("reads large negative integer", value2 == BigInt("-98765432101234567890"));
    }

    void test_input_with_whitespace()
    {
        std::istringstream in("   123   -456   789");
        BigInt a(0), b(0), c(0);

        in >> a;
        in >> b;
        in >> c;

        expectTrue("first token reads correctly", a == BigInt("123"));
        expectTrue("second token reads correctly", b == BigInt("-456"));
        expectTrue("third token reads correctly", c == BigInt("789"));
    }

    void test_round_trip_consistency()
    {
        const BigInt original("12345678901234567890");
        std::ostringstream out;
        out << original;

        std::istringstream in(out.str());
        BigInt copy(0);
        in >> copy;
        expectTrue("positive round trip works", copy == original);

        const BigInt negativeOriginal("-12345678901234567890");
        std::ostringstream negOut;
        negOut << negativeOriginal;

        std::istringstream negIn(negOut.str());
        BigInt negCopy(0);
        negIn >> negCopy;
        expectTrue("negative round trip works", negCopy == negativeOriginal);
    }

} // namespace

void run_all_io_tests()
{
    test_output_basic_values();
    test_output_normalization_cases();
    test_input_basic_values();
    test_input_large_values();
    test_input_with_whitespace();
    test_round_trip_consistency();

    std::cout << "All IO operator tests passed." << std::endl;
}
