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

    void test_zero_identity_and_self_assignment_cases()
    {
        BigInt a(0);
        const BigInt zero(0);
        const BigInt one("1");
        const BigInt ten("10");
        const BigInt negativeOne("-1");

        a += zero;
        expectTrue("0 += 0 == 0", a == zero);

        a = one;
        a += zero;
        expectTrue("1 += 0 == 1", a == one);

        a = ten;
        a -= zero;
        expectTrue("10 -= 0 == 10", a == ten);

        a = one;
        a *= zero;
        expectTrue("1 *= 0 == 0", a == zero);

        a = zero;
        a /= one;
        expectTrue("0 /= 1 == 0", a == zero);

        a = one;
        a %= one;
        expectTrue("1 %= 1 == 0", a == zero);

        a = negativeOne;
        a += zero;
        expectTrue("-1 += 0 == -1", a == negativeOne);
    }

    void test_small_positive_and_negative_assignment_cases()
    {
        BigInt a("12");
        const BigInt b("7");
        const BigInt c("-5");
        const BigInt d("-3");

        a += b;
        expectTrue("12 += 7 == 19", a == BigInt("19"));

        a = BigInt("12");
        a -= b;
        expectTrue("12 -= 7 == 5", a == BigInt("5"));

        a = BigInt("12");
        a *= b;
        expectTrue("12 *= 7 == 84", a == BigInt("84"));

        a = BigInt("12");
        a /= b;
        expectTrue("12 /= 7 == 1", a == BigInt("1"));

        a = BigInt("12");
        a %= b;
        expectTrue("12 %= 7 == 5", a == BigInt("5"));

        a = c;
        a += d;
        expectTrue("-5 += -3 == -8", a == BigInt("-8"));

        a = c;
        a -= d;
        expectTrue("-5 -= -3 == -2", a == BigInt("-2"));

        a = c;
        a *= BigInt("3");
        expectTrue("-5 *= 3 == -15", a == BigInt("-15"));

        a = BigInt("-15");
        a /= BigInt("3");
        expectTrue("-15 /= 3 == -5", a == BigInt("-5"));

        a = BigInt("-15");
        a %= BigInt("4");
        expectTrue("-15 %= 4 == -3", a == BigInt("-3"));
    }

    void test_large_number_assignment_cases()
    {
        BigInt a("999999999999999999");
        const BigInt one("1");
        const BigInt large("1000000000000000000");
        const BigInt huge("123456789012345678901234567890");
        const BigInt larger("123456789012345678901234567891");

        a += one;
        expectTrue("999... += 1 == 1000...", a == large);

        a = large;
        a -= one;
        expectTrue("1000... -= 1 == 999...", a == BigInt("999999999999999999"));

        a = huge;
        a += one;
        expectTrue("huge += 1 == larger", a == larger);

        a = larger;
        a -= huge;
        expectTrue("larger -= huge == 1", a == BigInt("1"));

        a = BigInt("-123456789012345678901234567890");
        a *= BigInt("2");
        expectTrue("negative huge *= 2 == -246...", a == BigInt("-246913578024691357802469135780"));

        a = large;
        a /= BigInt("2");
        expectTrue("100000... /= 2 == 500000...", a == BigInt("500000000000000000"));
    }

    void test_mixed_sign_and_repeated_assignment_cases()
    {
        BigInt a("123");
        const BigInt ten("10");
        const BigInt negativeSeven("-7");

        a += negativeSeven;
        expectTrue("123 += -7 == 116", a == BigInt("116"));

        a -= ten;
        expectTrue("116 -= 10 == 106", a == BigInt("106"));

        a *= BigInt("-2");
        expectTrue("106 *= -2 == -212", a == BigInt("-212"));

        a /= BigInt("-2");
        expectTrue("-212 /= -2 == 106", a == BigInt("106"));

        a = BigInt("123");
        a %= ten;
        expectTrue("123 %= 10 == 3", a == BigInt("3"));

        a = BigInt("17");
        a %= BigInt("-3");
        expectTrue("17 %= -3 == 2", a == BigInt("2"));

        BigInt repeated("7");
        repeated += repeated;
        expectTrue("7 += 7 == 14", repeated == BigInt("14"));

        repeated *= repeated;
        expectTrue("14 *= 14 == 196", repeated == BigInt("196"));
    }

    void test_assignment_division_by_zero_throws()
    {
        BigInt a("10");
        const BigInt zero(0);

        bool threwDivide = false;
        try
        {
            a /= zero;
        }
        catch (const std::runtime_error &)
        {
            threwDivide = true;
        }
        catch (...)
        {
            threwDivide = false;
        }

        expectTrue("a /= 0 throws runtime_error", threwDivide);

        a = BigInt("10");
        bool threwModulo = false;
        try
        {
            a %= zero;
        }
        catch (const std::runtime_error &)
        {
            threwModulo = true;
        }
        catch (...)
        {
            threwModulo = false;
        }

        expectTrue("a %= 0 throws runtime_error", threwModulo);
    }

} // namespace

void run_all_arithmetic_assignment_tests()
{
    test_zero_identity_and_self_assignment_cases();
    test_small_positive_and_negative_assignment_cases();
    test_large_number_assignment_cases();
    test_mixed_sign_and_repeated_assignment_cases();
    test_assignment_division_by_zero_throws();

    std::cout << "All arithmetic assignment operator tests passed." << std::endl;
}
