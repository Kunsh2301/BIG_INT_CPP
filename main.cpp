#include "BigInt.hpp"
#include <iostream>
int main() {
    BigInt a("12345678901234567890");
    BigInt b("987654321");
    BigInt c("-500");
    BigInt d("-1000");
    BigInt e("12345678901234567890");
    std::cout << (a == e) << '\n';
    std::cout << (a != b) << '\n';
    std::cout << (a > b) << '\n';
    std::cout << (b < a) << '\n';
    std::cout << (c < b) << '\n';
    std::cout << (d < c) << '\n';
    std::cout << (c <= c) << '\n';
    std::cout << (a >= e) << '\n';
    return 0;
}