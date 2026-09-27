#include "BigInt.hpp"
#include <cstdlib>
#include <iostream>
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

    void test_unary_plus_and_minus_basic_cases()
    {
        const BigInt zero(0);
        const BigInt positive("123");
        const BigInt negative("-123");

        expectTrue("+0 == 0", (+zero) == zero);
        expectTrue("+123 == 123", (+positive) == positive);
        expectTrue("+(-123) == -123", (+negative) == negative);
        expectTrue("-0 == 0", (-zero) == zero);
        expectTrue("-123 == -123", (-positive) == negative);
        expectTrue("-(-123) == 123", (-negative) == positive);
    }

    void test_prefix_increment_and_decrement()
    {
        BigInt value(0);
        expectTrue("++0 == 1", (++value) == BigInt("1"));
        expectTrue("value is now 1", value == BigInt("1"));

        value = BigInt("1");
        expectTrue("--1 == 0", (--value) == BigInt("0"));
        expectTrue("value is now 0", value == BigInt("0"));

        value = BigInt("-1");
        expectTrue("++(-1) == 0", (++value) == BigInt("0"));
        expectTrue("value is now 0", value == BigInt("0"));

        value = BigInt("0");
        expectTrue("--0 == -1", (--value) == BigInt("-1"));
        expectTrue("value is now -1", value == BigInt("-1"));
    }

    void test_postfix_increment_and_decrement()
    {
        BigInt value("5");
        BigInt oldValue = value++;
        expectTrue("5++ returns old value 5", oldValue == BigInt("5"));
        expectTrue("5++ increments to 6", value == BigInt("6"));

        value = BigInt("-5");
        oldValue = value--;
        expectTrue("-5-- returns old value -5", oldValue == BigInt("-5"));
        expectTrue("-5-- decrements to -6", value == BigInt("-6"));

        value = BigInt("0");
        oldValue = value++;
        expectTrue("0++ returns 0", oldValue == BigInt("0"));
        expectTrue("0++ becomes 1", value == BigInt("1"));

        value = BigInt("0");
        oldValue = value--;
        expectTrue("0-- returns 0", oldValue == BigInt("0"));
        expectTrue("0-- becomes -1", value == BigInt("-1"));
    }

    void test_increment_and_decrement_large_values()
    {
        BigInt value("999999999999999999");
        expectTrue("++999... == 1000...", (++value) == BigInt("1000000000000000000"));

        value = BigInt("1000000000000000000");
        expectTrue("--1000... == 999...", (--value) == BigInt("999999999999999999"));

        value = BigInt("-999999999999999999");
        expectTrue("++(-999...) == -999... + 1", (++value) == BigInt("-999999999999999998"));

        value = BigInt("-999999999999999999");
        expectTrue("--(-999...) == -1000...", (--value) == BigInt("-1000000000000000000"));
    }

    void test_repeated_unary_operations()
    {
        BigInt value("7");
        ++(++value);
        expectTrue("two prefix increments from 7 -> 9", value == BigInt("9"));

        value = BigInt("9");
        --(--value);
        expectTrue("two prefix decrements from 9 -> 7", value == BigInt("7"));

        value = BigInt("2");
        value++;
        value++;
        expectTrue("two postfix increments from 2 -> 4", value == BigInt("4"));

        value = BigInt("-2");
        value--;
        value--;
        expectTrue("two postfix decrements from -2 -> -4", value == BigInt("-4"));
    }

    void test_unary_sign_boundary_and_zero_stability()
    {
        BigInt zero(0);
        BigInt negativeZero("-0");

        expectTrue("negative zero stays zero after unary plus", (+negativeZero) == zero);
        expectTrue("negative zero stays zero after unary minus", (-negativeZero) == zero);
        expectTrue("prefix increment on zero yields 1", (++zero) == BigInt("1"));
        expectTrue("prefix decrement on 1 yields 0", (--BigInt("1")) == BigInt("0"));
    }

} // namespace

void run_all_unary_tests()
{
    test_unary_plus_and_minus_basic_cases();
    test_prefix_increment_and_decrement();
    test_postfix_increment_and_decrement();
    test_increment_and_decrement_large_values();
    test_repeated_unary_operations();
    test_unary_sign_boundary_and_zero_stability();

    std::cout << "All unary operator tests passed." << std::endl;
}
