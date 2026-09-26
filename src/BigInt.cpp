#include "BigInt.hpp"
#include <iostream>
BigInt::BigInt()
{
    digits.push_back(0);
    isNegative = false;
}
BigInt::BigInt(long long value)
{
    if (value < 0)
    {
        isNegative = true;
        value = -value;
    }
    else
    {
        isNegative = false;
    }
    if (value == 0)
    {
        digits.push_back(0);
        return;
    }
    while (value > 0)
    {
        digits.push_back(value % 10);
        value /= 10;
    }
}
BigInt::BigInt(const std::string &value)
{
    isNegative = false;
    int start = 0;
    if (value[0] == '-')
    {
        isNegative = true;
        start = 1;
    }
    for (int i = static_cast<int>(value.size()) - 1; i >= start; i--)
    {
        digits.push_back(value[i] - '0');
    }
    Normalize();
}
void BigInt::Normalize()
{
    while (static_cast<int>(digits.size()) > 1 && digits.back() == 0)
    {
        digits.pop_back();
    }
    if (static_cast<int>(digits.size()) == 1 && digits[0] == 0)
    {
        isNegative = false;
    }
}
