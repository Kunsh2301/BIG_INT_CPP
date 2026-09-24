#include"BigInt.hpp"
#include <stdexcept>
#include <algorithm>
BigInt BigInt::operator+(const BigInt& other) const{
    BigInt result;
    result.digits.clear();
    if(isNegative==other.isNegative){
        int carry=0,i=0,j=0;
        while(carry>0 || i<digits.size() || j<other.digits.size()){
            int sum=carry;
            if(i<digits.size()){
                sum+=digits[i];
                i++;
            }
            if(j<other.digits.size()){
                sum+=other.digits[j];
                j++;
            }
            result.digits.push_back(sum%10);
            carry=sum/10;
        }
        result.isNegative=isNegative;
        result.Normalize();
        return result;
    }
    bool thisislarge=false;
    if(digits.size()!=other.digits.size()){
        thisislarge=digits.size()>other.digits.size();
    }
    else{
        for(int i=digits.size()-1;i>=0;i--){
            if(digits[i]!=other.digits[i]){
                thisislarge=digits[i]>other.digits[i];
                break;
            }
        }
    }
    if(digits==other.digits){
        result.digits.push_back(0);
        result.isNegative=false;
        return result;
    }
    const BigInt& larger=thisislarge?*this:other;
    const BigInt& smaller=thisislarge?other:*this;
    int borrow=0;
    for(int i=0;i<larger.digits.size();i++){
        int diff=larger.digits[i]-borrow;
        if(i<smaller.digits.size()){
            diff-=smaller.digits[i];
        }
        if(diff<0){
            borrow=1;
            diff+=10;
        }
        else{
            borrow=0;
        }
        result.digits.push_back(diff);
    }
    result.isNegative=larger.isNegative;
    result.Normalize();
    return result;
}
BigInt BigInt::operator-(const BigInt& other) const{
    BigInt result;
    result.digits.clear();
    bool thisislarge=false;
    if(other.isNegative==isNegative){
        if(digits.size() != other.digits.size()){
            thisislarge=digits.size()>other.digits.size();
        }
        else{
            for(int i=digits.size()-1;i>=0;i--){
                if(digits[i]!=other.digits[i]){
                    thisislarge=digits[i]>other.digits[i];
                    break;
                }
            }
        }
        if(digits==other.digits){
            result.isNegative=false;
            result.digits.push_back(0);
            return result;
        }
        BigInt larger=thisislarge?*this:other;
        BigInt smaller=thisislarge?other:*this;
        int borrow=0;
        for(int i=0;i<larger.digits.size();i++){
            int diff=larger.digits[i]-borrow;
            if(i<smaller.digits.size()){
                diff-=smaller.digits[i];
            }
            if(diff<0){
                diff+=10;
                borrow=1;
            }
            else borrow=0;
            result.digits.push_back(diff);
        }
        if(thisislarge){
            result.isNegative=isNegative;
        }
        else{
            result.isNegative=!isNegative;
        }
        result.Normalize();
    }
    else{
        int carry=0,i=0,j=0;
        while(carry>0 || i<digits.size() || j<other.digits.size()){
            int sum=carry;
            if(i<digits.size()){
                sum+=digits[i];
                i++;
            }
            if(j<other.digits.size()){
                sum+=other.digits[j];
                j++;
            }
            result.digits.push_back(sum%10);
            carry=sum/10;
        }
        result.isNegative = isNegative;
        result.Normalize();
    }
    return result;
}
BigInt BigInt::operator*(const BigInt& other) const{
    BigInt result;
    result.digits.clear();
    result.isNegative=(isNegative!=other.isNegative);
    int n=digits.size(),m=other.digits.size();
    result.digits.resize(m+n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            result.digits[i+j]+=digits[i]*other.digits[j];
            result.digits[i+j+1]+=result.digits[i+j]/10;
            result.digits[i+j]%=10;
        }
    }
    int i=n+m-1;
    while(i>=0 && result.digits[i]==0) i--;
    if(i==-1){
        result.digits.clear();
        result.digits.push_back(0);
        result.isNegative = false;
        return result;
    }
    result.digits.resize(i+1);
    return result;
}
BigInt BigInt::operator/(const BigInt& other) const{
    if(other.digits.size()==1 && other.digits[0]==0){
        throw std::runtime_error("Division by zero");
    }
    BigInt dividend=*this;
    BigInt divisor=other;
    dividend.isNegative = false;
    divisor.isNegative = false;
    BigInt quotient;
    quotient.digits.clear();
    BigInt remainder;
    quotient.isNegative = false;
    for(int i=static_cast<int>(dividend.digits.size()-1);i>=0;i--){
        if(remainder.digits.size()==1 && remainder.digits[0]==0){
            remainder.digits[0]=dividend.digits[i];
        }
        else{
            remainder.digits.insert(remainder.digits.begin(),dividend.digits[i]);
        }
        remainder.Normalize();
        int quotient_digit=0;
        while(remainder>=divisor){
            remainder=remainder-divisor;
            quotient_digit++;
        }
        quotient.digits.push_back(quotient_digit);
    }
    reverse(quotient.digits.begin(),quotient.digits.end());
    quotient.Normalize();
    if(!(quotient.digits.size()==1 && quotient.digits[0]==0)){
        quotient.isNegative=(isNegative!=other.isNegative);
    }
    return quotient;
}