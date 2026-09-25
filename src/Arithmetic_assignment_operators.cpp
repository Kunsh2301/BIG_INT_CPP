#include "BigInt.hpp"
BigInt& BigInt::operator+=(const BigInt& other){
    *this=*this+other;
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& other){
    *this=*this-other;
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& other){
    *this=(*this)*other;
    return *this;
}
BigInt& BigInt::operator/=(const BigInt& other){
    *this=(*this)/other;
    return *this;
}
BigInt& BigInt::operator%=(const BigInt& other){
    *this=(*this)%other;
    return *this;
}