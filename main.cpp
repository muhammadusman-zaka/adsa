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
    // be discarded. To get our digit for the final sum, we can determine the
    // remainder between the current sum and the base by using the modulo
    // operator
    int curr = digit1 + digit2 + carry;
    carry = curr / base;
    sum.insert(0, 1, (curr % base) + '0');
  }
  
  return sum;
}

std::string singleDigitMultiplication(std::string &firstNum, std::string &secondNum, int base){
  int result = (firstNum[0]-'0') * (secondNum[0]-'0');
  std::string product = "";

  // Convert the result to correct base
  while (result > 0)
  {
    product.insert(0, 1, (result % base) + '0');
    result /= base;
  }

  return product;
  
}

std::string subtraction(std::string &num1, std::string &num2, int base) {
  std::string difference;
  int borrow = 0;
  int len1 = num1.length();
  int len2 = num2.length();

  for (int i = 0; i < len1; i++) {
      int digit1 = num1[len1 - 1 - i] - '0';
      int digit2 = (i < len2) ? num2[len2 - 1 - i] - '0' : 0;

      int curr = digit1 - digit2 - borrow;
      if (curr < 0) {
          curr += base;
          borrow = 1;
      } 
      
      else {
          borrow = 0;
      }
      
      difference.push_back(curr + '0');
  }
  
  while (difference.size() > 1 && difference.back() == '0') {
      difference.pop_back();
  }
  
  std::reverse(difference.begin(), difference.end());
  return difference;
}

std::string karatsubaMultiplication(std::string &firstNum, std::string &secondNum, int base){
  int len1 = firstNum.length();
  int len2 = secondNum.length();

  // Bases cases are if multiplication is with 0 or 1 digit multiplication
  if (len1 == 0 || len2 == 0)
  {
    return "0";
  }

  if (len1 == 1 && len2 == 1)
  {
    return singleDigitMultiplication(firstNum, secondNum, base);
  }
  

  int maxLength = std::max(len1,len2);
  int k = (maxLength + 1) / 2;

  // Make both numbers the same length by adding 0s as padding
  std::string num1 = std::string(maxLength - len1, '0') + firstNum;
  std::string num2 = std::string(maxLength - len2, '0') + secondNum;

  // Split the numbers
  std::string a1 = num1.substr(0, maxLength-k);
  std::string a0 = num1.substr(maxLength-k);
  std::string b1 = num2.substr(0, maxLength-k);
  std::string b0 = num2.substr(maxLength-k);
  
  // Get the three products, p2,p1,p0 according to the lectures
  std::string p0 = karatsubaMultiplication(a0, b0, base);
  
  std::string p1sum1 = schoolMethodAddition(a1, a0, base);
  std::string p1sum2 = schoolMethodAddition(b1, b0, base);

  std::string p1 = karatsubaMultiplication(p1sum1, p1sum2, base);

  std::string p2 = karatsubaMultiplication(a1, b1, base);

  // Using the 3 products, getting the 3 terms of the final equation
  std::string middleTermSum = schoolMethodAddition(p2, p0, base);
  std::string middleTerm = subtraction(p1, middleTermSum, base);

  std::string firstTerm = p2 + std::string(2 * k, '0');
  middleTerm = middleTerm + std::string(k, '0');

  // Adding everything together
  std::string firstSum = schoolMethodAddition(firstTerm, middleTerm, base);
  std::string product = schoolMethodAddition(firstSum, p0, base);
  
  product.erase(0, product.find_first_not_of('0'));

  return product;
}

int main() {
  // Variables in which we will store the input
  int base;
  std::string num1, num2;

  // We then take all the input in one line
  std::cin >> num1 >> num2 >> base;

  // We can then output the results
  std::cout << schoolMethodAddition(num1, num2, base) << " " << karatsubaMultiplication(num1, num2, base) << " 0 ";
  return 0;
}