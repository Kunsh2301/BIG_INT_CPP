#include"BigInt.hpp"
bool BigInt::operator==(const BigInt& other) const{
    return isNegative==other.isNegative && digits==other.digits;
}
bool BigInt::operator!=(const BigInt& other) const{
    return !(*this==other);
}
bool BigInt::operator<(const BigInt& other) const{
    if(isNegative!=other.isNegative){
        return isNegative;
    }
    if(!isNegative){
        if(digits.size()!=other.digits.size()){
            return digits.size()<other.digits.size();
        }
        for(int i=digits.size()-1;i>=0;i--){
            if(digits[i]!=other.digits[i]){
                return digits[i]<other.digits[i];
            }
        }
        return false;
    }
    if(digits.size()!=other.digits.size()){
        return digits.size()>other.digits.size();
    }
    for(int i=digits.size()-1;i>=0;i--){
        if(digits[i]!=other.digits[i]){
            return digits[i]>other.digits[i];
        }
    }
    return false;
}
bool BigInt::operator>(const BigInt& other) const{
    return other<*this;
}
bool BigInt::operator<=(const BigInt& other) const{
    return (*this<other) || (*this==other);
}
bool BigInt::operator>=(const BigInt& other) const{
    return (*this>other) || (*this==other);
}