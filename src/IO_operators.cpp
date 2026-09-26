#include "BigInt.hpp"
#include <iostream>
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
    is>>input;
    value=BigInt(input);
    return is; 
}