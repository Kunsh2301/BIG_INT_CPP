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

    void test_zero_and_basic_sign_cases()
    {
        const BigInt zero(0);
        const BigInt positiveOne("1");
        const BigInt positiveTen("10");
        const BigInt negativeOne("-1");
        const BigInt negativeTen("-10");

        expectTrue("zero == zero", zero == zero);
        expectTrue("zero != 1", zero != positiveOne);
        expectTrue("0 < 1", zero < positiveOne);
        expectTrue("1 > 0", positiveOne > zero);
        expectTrue("-1 < 0", negativeOne < zero);
        expectTrue("0 > -1", zero > negativeOne);
        expectTrue("-10 < -1", negativeTen < negativeOne);
        expectTrue("-1 > -10", negativeOne > negativeTen);
        expectTrue("10 > 1", positiveTen > positiveOne);
    }

    void test_equal_and_not_equal_values()
    {
        const BigInt a("123456789");
        const BigInt b("123456789");
        const BigInt c("123456780");
        const BigInt d("-123456789");
        const BigInt e("-123456789");

        expectTrue("equal positives compare equal", a == b);
        expectTrue("different positives compare not equal", a != c);
        expectTrue("equal negatives compare equal", d == e);
        expectTrue("positive != negative same magnitude", a != d);
        expectTrue("a <= b", a <= b);
        expectTrue("b >= a", b >= a);
        expectTrue("c < a", c < a);
        expectTrue("a > c", a > c);
    }

    void test_large_value_comparisons()
    {
        const BigInt small("999999999999999999");
        const BigInt large("1000000000000000000");
        const BigInt huge("123456789012345678901234567890");
        const BigInt larger("123456789012345678901234567891");
        const BigInt hugeNegative("-123456789012345678901234567890");

        expectTrue("small < large", small < large);
        expectTrue("large > small", large > small);
        expectTrue("huge < larger", huge < larger);
        expectTrue("larger > huge", larger > huge);
        expectTrue("negative large < positive large", hugeNegative < large);
        expectTrue("positive large > negative large", large > hugeNegative);
    }

    void test_zero_edge_cases_with_mixed_values()
    {
        const BigInt zero(0);
        const BigInt zeroString("0");
        const BigInt positiveZeroPad("000000");
        const BigInt negativeZero("-0");

        expectTrue("zero string equals zero literal", zero == zeroString);
        expectTrue("zero with leading zeros equals zero", zero == positiveZeroPad);
        expectTrue("-0 equals 0", negativeZero == zero);
        expectTrue("-0 <= 0", negativeZero <= zero);
        expectTrue("0 >= -0", zero >= negativeZero);
    }

    void test_negative_magnitude_ordering()
    {
        const BigInt negA("-123456");
        const BigInt negB("-123457");
        const BigInt negC("-100000");
        const BigInt negD("-200000");

        expectTrue("-123456 > -123457", negA > negB);
        expectTrue("-200000 < -100000", negD < negC);
        expectTrue("-123456 >= -123456", negA >= negA);
        expectTrue("-123457 <= -123457", negB <= negB);
    }

    void test_same_length_different_digit_order()
    {
        const BigInt left("987654321");
        const BigInt right("987654320");
        const BigInt leftTwin("987654321");

        expectTrue("same length higher digit wins", left > right);
        expectTrue("same length equal digits compare equal", left == leftTwin);
        expectTrue("left >= right", left >= right);
        expectTrue("right <= left", right <= left);
    }

    void test_sign_boundary_cases()
    {
        const BigInt maxPositive("999999999999999999999999999999");
        const BigInt minNegative("-999999999999999999999999999999");
        const BigInt zero(0);

        expectTrue("largest positive > zero", maxPositive > zero);
        expectTrue("zero > most negative", zero > minNegative);
        expectTrue("most negative < zero", minNegative < zero);
        expectTrue("most negative < largest positive", minNegative < maxPositive);
    }

} // namespace

void run_all_comparison_tests()
{
    test_zero_and_basic_sign_cases();
    test_equal_and_not_equal_values();
    test_large_value_comparisons();
    test_zero_edge_cases_with_mixed_values();
    test_negative_magnitude_ordering();
    test_same_length_different_digit_order();
    test_sign_boundary_cases();

    std::cout << "All comparison operator tests passed." << std::endl;
}
