#include "BigInt.hpp"
#include <iostream>
#include <stdexcept>
std::ostream& operator<<(std::ostream& os,const BigInt& value){
    if(value.isNegative){
        os<<'-';
    }
    for(int i=static_cast<int>(value.digits.size())-1;i>=0;i--){
        os<<value.digits[i];
    }
    return os;
}
std::istream& operator>>(std::istream& is,BigInt& value){
    std::string input;
    if (!(is >> input))
    {
        return is;
    }
    try
    {
        BigInt parsed(input);
        value = parsed;
    }
    catch (const std::invalid_argument &)
    {
        is.setstate(std::ios::failbit);
    }
    return is;
}