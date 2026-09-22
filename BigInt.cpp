#include"BigInt.hpp"
#include<iostream>
BigInt::BigInt(){
    digits.push_back(0);
    isNegative=false;
}
BigInt::BigInt(long long value){
    if(value<0){
        isNegative=true;
        value=-value;
    }
    else{
        isNegative=false;
    }
    if(value==0){
        digits.push_back(0);
        return ;
    }
    while(value>0){
        digits.push_back(value%10);
        value/=10;
    }
}
BigInt::BigInt(const std::string& value){
    isNegative=false;
    int start=0;
    if(value[0]=='-'){
        isNegative=true;
        start=1;
    }
    for(int i=value.size()-1;i>=start;i--){
        digits.push_back(value[i]-'0');
    }
    Normalize();
}
void BigInt::Normalize(){
    while(digits.size()>1 && digits.back()==0){
        digits.pop_back();
    }
    if(digits.size()==1 && digits[0]==0){
        isNegative=false;
    }
}
void BigInt::print() const{
    if(isNegative){
        std::cout<<'-';
    }
    for(int i=digits.size()-1;i>=0;i--){
        std::cout<<digits[i];
    }
    std::cout<<"\n";
}
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
