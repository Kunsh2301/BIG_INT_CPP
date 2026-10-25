#include "BigInt.hpp"
#include <iostream>

int main()
{
    std::cout << "Welcome to the BigInt demo!\n"
              << "This program lets you try the BigInt operators with your own numbers.\n"
              << "Enter whole numbers with an optional leading minus sign.\n\n";

    BigInt first;
    BigInt second;

    std::cout << "Enter the first large integer: ";
    if (!(std::cin >> first))
    {
        std::cerr << "Input ended before the first integer could be read.\n";
        return 1;
    }

    std::cout << "Enter the second large integer: ";
    if (!(std::cin >> second))
    {
        std::cerr << "Input ended before the second integer could be read.\n";
        return 1;
    }

    std::cout << "\nYou entered:\n"
              << "  First:  " << first << '\n'
              << "  Second: " << second << "\n\n";

    std::cout << "Arithmetic operators\n"
              << "  +  " << first << " + " << second << " = " << first + second << '\n'
              << "  -  " << first << " - " << second << " = " << first - second << '\n'
              << "  *  " << first << " * " << second << " = " << first * second << '\n';

    if (second != BigInt(0))
    {
        std::cout << "  /  " << first << " / " << second << " = " << first / second << '\n'
                  << "  %  " << first << " % " << second << " = " << first % second << '\n';
    }
    else
    {
        std::cout << "  / and % skipped because division by zero is not allowed.\n";
    }

    std::cout << "\nComparison operators\n"
              << std::boolalpha
              << "  " << first << " == " << second << ": " << (first == second) << '\n'
              << "  " << first << " != " << second << ": " << (first != second) << '\n'
              << "  " << first << " <  " << second << ": " << (first < second) << '\n'
              << "  " << first << " >  " << second << ": " << (first > second) << '\n'
              << "  " << first << " <= " << second << ": " << (first <= second) << '\n'
              << "  " << first << " >= " << second << ": " << (first >= second) << '\n';

    BigInt assigned = first;
    std::cout << "\nArithmetic assignment operators (starting with " << assigned << ")\n";
    assigned += second;
    std::cout << "  After += second: " << assigned << '\n';
    assigned = first;
    assigned -= second;
    std::cout << "  After -= second: " << assigned << '\n';
    assigned = first;
    assigned *= second;
    std::cout << "  After *= second: " << assigned << '\n';
    if (second != BigInt(0))
    {
        assigned = first;
        assigned /= second;
        std::cout << "  After /= second: " << assigned << '\n';
        assigned = first;
        assigned %= second;
        std::cout << "  After %= second: " << assigned << '\n';
    }
    else
    {
        std::cout << "  /= and %= skipped because division by zero is not allowed.\n";
    }

    std::cout << "\nUnary and increment/decrement operators (starting with " << first << ")\n"
              << "  Unary +: " << +first << '\n'
              << "  Unary -: " << -first << '\n';

    BigInt changed = first;
    std::cout << "  Prefix ++ returns " << ++changed << " (value is now " << changed << ")\n";
    changed = first;
    std::cout << "  Postfix ++ returns " << changed++ << " (value is now " << changed << ")\n";
    changed = first;
    std::cout << "  Prefix -- returns " << --changed << " (value is now " << changed << ")\n";
    changed = first;
    std::cout << "  Postfix -- returns " << changed-- << " (value is now " << changed << ")\n";

    std::cout << "\nThanks for trying the BigInt demo! Run the test suite for broader checks.\n";
    return 0;
}