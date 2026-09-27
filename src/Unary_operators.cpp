#include "BigInt.hpp"
BigInt BigInt::operator-() const
{
    BigInt result = *this;
    if (result.digits.size() == 1 && result.digits[0] == 0)
    {
        result.isNegative = false;
    }
    else
    {
        result.isNegative = !result.isNegative;
    }
    return result;
}
BigInt BigInt::operator+() const
{
    return *this;
}
BigInt &BigInt::operator++()
{
    *this = *this + 1;
    return *this;
}
BigInt &BigInt::operator--()
{
    *this = *this - 1;
    return *this;
}
BigInt BigInt::operator++(int)
{
    BigInt old = *this;
    *this = *this + 1;
    return old;
}
BigInt BigInt::operator--(int)
{
    BigInt old = *this;
    *this = *this - 1;
    return old;
}
