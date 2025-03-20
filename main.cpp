#include <iostream>
#include <string>

int main(){
    // Variables in which we will store the input
    int base;
    std::string num1, num2;

    // We then take all the input in one line
    std::cin >> num1 >> num2 >> base;

    // We can then output the results
    std::cout << schoolMethodAddition(num1, num2, base) << " " << karatsubaMultiplication(num1, num2, base) << " 0";
    return 0;
}