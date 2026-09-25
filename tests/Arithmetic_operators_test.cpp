#include "BigInt.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
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

    void test_zero_and_identity_cases()
    {
        const BigInt zero(0);
        const BigInt positiveOne("1");
        const BigInt positiveTen("10");
        const BigInt negativeOne("-1");

        expectTrue("0 + 0 == 0", (zero + zero) == zero);
        expectTrue("0 - 0 == 0", (zero - zero) == zero);
        expectTrue("0 * 10 == 0", (zero * positiveTen) == zero);
        expectTrue("0 / 1 == 0", (zero / positiveOne) == zero);
        expectTrue("1 + 0 == 1", (positiveOne + zero) == positiveOne);
        expectTrue("1 - 0 == 1", (positiveOne - zero) == positiveOne);
        expectTrue("0 + (-1) == -1", (zero + negativeOne) == negativeOne);
    }

    void test_small_positive_and_negative_operations()
    {
        const BigInt a("12");
        const BigInt b("7");
        const BigInt c("-5");
        const BigInt d("-3");

        expectTrue("12 + 7 == 19", (a + b) == BigInt("19"));
        expectTrue("12 - 7 == 5", (a - b) == BigInt("5"));
        expectTrue("12 * 7 == 84", (a * b) == BigInt("84"));
        expectTrue("12 / 7 == 1", (a / b) == BigInt("1"));
        expectTrue("12 % 7 == 5", (a % b) == BigInt("5"));

        expectTrue("-5 + -3 == -8", (c + d) == BigInt("-8"));
        expectTrue("-5 - (-3) == -2", (c - d) == BigInt("-2"));
        expectTrue("-5 * 3 == -15", (c * BigInt("3")) == BigInt("-15"));
        expectTrue("-15 / 3 == -5", (BigInt("-15") / BigInt("3")) == BigInt("-5"));
        expectTrue("-15 % 4 == -3", (BigInt("-15") % BigInt("4")) == BigInt("-3"));
    }

    void test_large_addition_and_subtraction()
    {
        const BigInt small("999999999999999999");
        const BigInt large("1000000000000000000");
        const BigInt huge("123456789012345678901234567890");
        const BigInt larger("123456789012345678901234567891");
        const BigInt hugeNegative("-123456789012345678901234567890");

        expectTrue("999... + 1 == 1000...", (small + BigInt("1")) == large);
        expectTrue("1000... - 1 == 999...", (large - BigInt("1")) == small);
        expectTrue("huge + 1 == larger", (huge + BigInt("1")) == larger);
        expectTrue("larger - huge == 1", (larger - huge) == BigInt("1"));
        expectTrue("large - (-huge) == huge + large", (large - hugeNegative) == (large + hugeNegative * BigInt("-1")));
        expectTrue("-huge + huge == 0", (hugeNegative + huge) == BigInt("0"));
    }

    void test_large_multiplication_and_division()
    {
        const BigInt a("123456789123456789");
        const BigInt b("987654321987654321");
        const BigInt c("1000000000000000000");
        const BigInt d("500000000000000000");

        expectTrue("123... * 10 == 1234...0", (a * BigInt("10")) == BigInt("1234567891234567890"));
        expectTrue("100000... / 2 == 500000...", (c / BigInt("2")) == d);
        expectTrue("100000... % 3 == 1", (c % BigInt("3")) == BigInt("1"));
        expectTrue("A * 0 == 0", (a * BigInt("0")) == BigInt("0"));
        expectTrue("(123... * 987...) == expected", (a * b) == BigInt("121932631356500531347203169112635269"));
    }

    void test_very_large_number_cases()
    {
        const BigInt v1("999999999999999999999999999999999999999999999999999");
        const BigInt v2("111111111111111111111111111111111111111111111111111");
        const BigInt v3("888888888888888888888888888888888888888888888888888");
        const BigInt v4("-888888888888888888888888888888888888888888888888888");

        expectTrue("very large + very large works", (v1 + v2) == BigInt("1111111111111111111111111111111111111111111111111110"));
        expectTrue("very large - very large == 888...", (v3 - v2) == BigInt("777777777777777777777777777777777777777777777777777"));
        expectTrue("negative very large * 2 == negative", (v4 * BigInt("2")) == BigInt("-1777777777777777777777777777777777777777777777777776"));
        expectTrue("very large * 0 == 0", (v1 * BigInt("0")) == BigInt("0"));
    }

    void test_division_by_zero_throws()
    {
        const BigInt zero(0);
        const BigInt one("1");

        bool threwDivision = false;
        try
        {
            (void)(one / zero);
        }
        catch (const std::runtime_error &)
        {
            threwDivision = true;
        }
        catch (...)
        {
            threwDivision = false;
        }

        expectTrue("division by zero throws runtime error", threwDivision);

        bool threwModulo = false;
        try
        {
            (void)(one % zero);
        }
        catch (const std::runtime_error &)
        {
            threwModulo = true;
        }
        catch (...)
        {
            threwModulo = false;
        }

        expectTrue("modulo by zero throws runtime error", threwModulo);
    }

} // namespace

void run_all_arithmetic_tests()
{
    test_zero_and_identity_cases();
    test_small_positive_and_negative_operations();
    test_large_addition_and_subtraction();
    test_large_multiplication_and_division();
    test_very_large_number_cases();
    test_division_by_zero_throws();

    std::cout << "All arithmetic operator tests passed." << std::endl;
}
