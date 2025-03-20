#include <algorithm>
#include <iostream>
#include <string>

std::string schoolMethodAddition(const std::string &firstNum, const std::string &secondNum, int base) {
  // Variables to store the total sum and the carry
  std::string sum;
  int carry = 0;

  // Obtaining the lengths of each number and determining the longer number
  int len1 = firstNum.length();
  int len2 = secondNum.length();
  int maxLen = std::max(len1, len2);

  for (int i = 0; i < maxLen || carry > 0; i++) {
    int digit1 = 0;
    int digit2 = 0;

    // Extract digits from each number (starting from the rightmost digit)
    // Convert that digit from char to int
    if (i < len1) {
      digit1 = firstNum[len1 - 1 - i] - '0';
    } 

    if (i < len2) {
      digit2 = secondNum[len2 - 1 - i] - '0';
    }
     
    // Calculate the current result
    // Calculate the carry and since it is integer division, the decimals will
    // be discarded To get our digit for the final sum, we can determine the
    // remainder between the current sum and the base by using the modulo
    // operator
    int curr = digit1 + digit2 + carry;
    carry = curr / base;
    sum.insert(0, 1, (curr % base) + '0');
  }
  
  return sum;
}

int main() {
  // Variables in which we will store the input
  int base;
  std::string num1, num2;

  // We then take all the input in one line
  std::cin >> num1 >> num2 >> base;

  // We can then output the results
  std::cout << schoolMethodAddition(num1, num2, base) << " " << "0" << " 0 ";
  return 0;
}