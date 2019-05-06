// number_to_text.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


std::string excuse = "I don't know how to print that yet";

std::string units_to_string(int unit_in) {
	std::string units[10] = { "zero", "one","two","three","four", "five","six","seven","eight","nine" };
	return units[unit_in];
}

std::string two_digit_to_string(int digits_in) {

	std::string teens[10] = { "ten", "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen" };
	std::string tens[10] = { "","ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety" };

	// first, deal with case where number is single-digit
	if (digits_in < 10) {
		return units_to_string(digits_in);
	}
	// next, deal with case where number is in the teens
	if (digits_in < 20) {
		return teens[digits_in - 10];
	}

	// if neither of above, then deal with "normal" two-digit numbers. The below two are generating single digits\
	for the units and tens columns of the number

	int units_digit = digits_in % 10; 
	int tens_digit = digits_in / 10;

	std::string tens_string = tens[tens_digit];
	std::string units_string = "";
	if (units_digit != 0) {
		units_string = units_to_string(units_digit);
	} 

	std::string two_digit_string = (tens_string + " " +units_string);
	return two_digit_string;
	
}

std::string three_digit_to_string(int digits_in) {
	int two_digits = digits_in % 100;
	std::string two_digit_string = two_digit_to_string(two_digits);
	if (digits_in < 100) {
		return two_digit_string;
	}

	int hundreds_digit = digits_in / 100;
	std::string hundreds_string = units_to_string(hundreds_digit) + " hundred";
	if (two_digits != 0) {
		return hundreds_string + " and " + two_digit_string;
	}
	else {
		return hundreds_string;
	}
}

int main()
{
    std::cout << "Type your number\n"; 
	int digits;
	std::cin >> digits;
	if (digits < 1000){
		std::cout << three_digit_to_string(digits);
	} else {
		std::cout << excuse;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
