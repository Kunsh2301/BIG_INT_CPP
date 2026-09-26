#include "BigInt.hpp"
bool BigInt::operator==(const BigInt &other) const
{
    return isNegative == other.isNegative && digits == other.digits;
}
bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}
bool BigInt::operator<(const BigInt &other) const
{
    if (isNegative != other.isNegative)
    {
        return isNegative;
    }
    if (!isNegative)
    {
        if (static_cast<int>(digits.size()) != static_cast<int>(other.digits.size()))
        {
            return static_cast<int>(digits.size()) < static_cast<int>(other.digits.size());
        }
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--)
        {
            if (digits[i] != other.digits[i])
            {
                return digits[i] < other.digits[i];
            }
        }
        return false;
    }
    if (static_cast<int>(digits.size()) != static_cast<int>(other.digits.size()))
    {
        return static_cast<int>(digits.size()) > static_cast<int>(other.digits.size());
    }
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--)
    {
        if (digits[i] != other.digits[i])
        {
            return digits[i] > other.digits[i];
        }
    }
    return false;
}
bool BigInt::operator>(const BigInt &other) const
{
    return other < *this;
}
bool BigInt::operator<=(const BigInt &other) const
{
    return (*this < other) || (*this == other);
}
bool BigInt::operator>=(const BigInt &other) const
{
    return (*this > other) || (*this == other);
}