#include "BigInt.hpp"
#include <iostream>
#include <stdexcept>
BigInt::BigInt()
{
    digits.push_back(0);
    isNegative = false;
}
BigInt::BigInt(long long value)
{
    unsigned long long magnitude;
    if (value < 0)
    {
        isNegative = true;
        magnitude = static_cast<unsigned long long>(-(value + 1)) + 1;
    }
    else
    {
        isNegative = false;
        magnitude = static_cast<unsigned long long>(value);
    }
    if (magnitude == 0)
    {
        digits.push_back(0);
        return;
    }
    while (magnitude > 0)
    {
        digits.push_back(static_cast<int>(magnitude % 10));
        magnitude /= 10;
    }
}
BigInt::BigInt(const std::string &value)
{
    isNegative = false;
    std::string::size_type start = 0;
    if (!value.empty() && value[0] == '-')
    {
        isNegative = true;
        start = 1;
    }
    if (start == value.size())
    {
        throw std::invalid_argument("BigInt string must contain decimal digits");
    }
    for (std::string::size_type i = start; i < value.size(); ++i)
    {
        if (value[i] < '0' || value[i] > '9')
        {
            throw std::invalid_argument("BigInt string must contain only decimal digits");
        }
    }
    for (std::string::size_type i = value.size(); i > start; --i)
    {
        digits.push_back(value[i - 1] - '0');
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
