#include "BigInt.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
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

    void expectString(const std::string &name, const BigInt &value, const std::string &expected)
    {
        std::ostringstream output;
        output << value;
        expectTrue(name, output.str() == expected);
    }

    void test_default_constructor()
    {
        const BigInt value;
        expectString("default constructor creates zero", value, "0");
    }

    void test_numeric_constructor_small_values()
    {
        expectString("numeric zero creates zero", BigInt(0), "0");
        expectString("positive single digit is preserved", BigInt(7), "7");
        expectString("negative single digit is preserved", BigInt(-7), "-7");
        expectString("positive multi-digit value is preserved", BigInt(12345), "12345");
        expectString("negative multi-digit value is preserved", BigInt(-12345), "-12345");
    }

    void test_numeric_constructor_large_and_boundary_values()
    {
        expectString("large positive value is preserved",
                     BigInt(1234567890123456789LL), "1234567890123456789");
        expectString("large negative value is preserved",
                     BigInt(-1234567890123456789LL), "-1234567890123456789");
        expectString("long long maximum is preserved",
                     BigInt(std::numeric_limits<long long>::max()), "9223372036854775807");
        expectString("largest-magnitude supported negative long long is preserved",
                     BigInt(std::numeric_limits<long long>::min() + 1),
                     "-9223372036854775807");
    }

    void test_string_constructor_values()
    {
        expectString("string zero creates zero", BigInt("0"), "0");
        expectString("positive single-digit string is preserved", BigInt("9"), "9");
        expectString("negative single-digit string is preserved", BigInt("-9"), "-9");
        expectString("large positive string is preserved",
                     BigInt("123456789012345678901234567890"),
                     "123456789012345678901234567890");
        expectString("large negative string is preserved",
                     BigInt("-987654321098765432109876543210"),
                     "-987654321098765432109876543210");
    }

    void test_string_constructor_normalization_and_zero_edges()
    {
        expectString("leading zeros are normalized", BigInt("000123"), "123");
        expectString("negative leading zeros are normalized", BigInt("-000123"), "-123");
        expectString("all-zero string is normalized", BigInt("000000"), "0");
        expectString("negative zero is normalized", BigInt("-0"), "0");
        expectString("negative zero with leading zeros is normalized", BigInt("-000000"), "0");
    }
} // namespace

void run_all_constructor_tests()
{
    test_default_constructor();
    test_numeric_constructor_small_values();
    test_numeric_constructor_large_and_boundary_values();
    test_string_constructor_values();
    test_string_constructor_normalization_and_zero_edges();

    std::cout << "All constructor tests passed." << std::endl;
}
