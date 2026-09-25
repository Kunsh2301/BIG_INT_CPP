#ifndef BIGINT_HPP
#define BIGINT_HPP
#include<vector>
#include<string>
class BigInt {
    private:
        std::vector<int> digits;
        bool isNegative;
        void Normalize();
    public:
        BigInt();
        BigInt(long long value);
        BigInt(const std::string& value);

        // Comparison operators
        
        bool operator==(const BigInt& other) const;
        bool operator!=(const BigInt& other) const;
        bool operator<(const BigInt& other) const;
        bool operator>(const BigInt& other) const;
        bool operator<=(const BigInt& other) const;
        bool operator>=(const BigInt& other) const;

        // Arithmetic operators

        BigInt operator+(const BigInt& other) const;
        BigInt operator-(const BigInt& other) const;
        BigInt operator*(const BigInt& other) const;
        BigInt operator/(const BigInt& other) const;
        BigInt operator%(const BigInt& other) const;

        // Arithmetic assignment operators

        BigInt& operator+=(const BigInt& other); 
        BigInt& operator-=(const BigInt& other); 
        BigInt& operator*=(const BigInt& other); 
        BigInt& operator/=(const BigInt& other); 
        BigInt& operator%=(const BigInt& other); 

        void print() const;
};
#endif