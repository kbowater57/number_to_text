// number_to_text.cpp : This function asks the user for an input, and generates the number as a string for 
// up to nine digits. The implementation means that it would be trivial to expand this function to arbitrarily
// large numbers.

#include <iostream>


std::string units_to_string(int unit_in) {
	//Function to output single digit number as string, given a single digit number as int
	std::string units[10] = { "zero", "one","two","three","four", "five","six","seven","eight","nine" };
	return units[unit_in];
}

std::string two_digit_to_string(int digits_in) {
	// Function to output two digit number as string, given two digit number as int. Single digit numbers and teens are corner cases
	// treated separately from the majority of numbers

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

	// if neither of above, then deal with "normal" two-digit numbers. The below two are generating the digits in the units
	// and tens columns of the number

	int units_digit = digits_in % 10; 
	int tens_digit = digits_in / 10;

	// access appropriate entry in the tens array created earlier
	std::string tens_string = tens[tens_digit];
	std::string units_string = "";

	// if the units column has a zero in it, we don't want anything to be printed for the units column (e.g. not "twenty zero" or similar)
	if (units_digit != 0) {
		// If not zero, find correct entry using previously defined function
		units_string = units_to_string(units_digit);
	} 

	// concatenate tens and units strings before returning
	std::string two_digit_string = (tens_string + " " +units_string);
	return two_digit_string;
	
}

std::string three_digit_to_string(int digits_in) {
	// Returns 3 digit number as string, given it as an int

	// Remove hundreds column, to pass this to two digit function
	int two_digits = digits_in % 100;

	// Use previously defined function to find tens and units string
	std::string two_digit_string = two_digit_to_string(two_digits);

	// If the input is less than 100 then we are done - return string
	if (digits_in < 100) {
		return two_digit_string;
	}

	// If greater than 100, find digit in hundreds column
	int hundreds_digit = digits_in / 100;

	// Generate hundreds part of string, reusing units function earlier
	std::string hundreds_string = units_to_string(hundreds_digit) + " hundred";

	// Only add tens and units columns if they aren't zero (Avoiding "One hundred zero" or similar)
	if (two_digits != 0) {
		return hundreds_string + " and " + two_digit_string;
	}
	else {
		return hundreds_string;
	}
}

std::string nine_digit_to_string(int digits_in) {
	// Returns nine digit number as string, given an int. This breaks the number down into three-digit numbers for millions, 
	// thousands, and units, and reuses three-digit function above for each step, appending suffixes to each part in turn.

	// Deal with corner case of zero
	if (digits_in == 0) {
		return "Zero";
	}
	
	// Initialise output
	std::string output_string = "";

	// Use arrays to store orders of magnitude. If larger numbers were needed, would only have to add extra
	// elements here, and change initialisation of for loop
	std::string suffix[3] = { ""," thousand"," million" };
	int powers[3] = { 1,1000,1000000 };

	for (int x = 2; x != -1; --x) {
		// Generate number from left to right: starting with millions column and working down
		if (digits_in > powers[x]-1) {

			// Find the next three digit number
			int three_digits = digits_in / powers[x];

			// Generate string for that three digit number
			std::string three_digit_string = three_digit_to_string(three_digits); 
			
			// Only add this string and appropriate suffix to output if it isn't zero. Note, we dealed with input 
			// zero earlier.
			if (three_digits != 0) {
				output_string = output_string + three_digit_string + suffix[x] ;
			}

			// Remove the part of the number we've now added to the output string
			digits_in %= powers[x];

			// Add a comma if it's appropriate (e.g. we still have more numbers to add to the output)
			if (digits_in > 0) {
				output_string = output_string + ", ";
			}
		}
	}
	// Capitalise first letter and add full stop at end
	output_string[0] = toupper(output_string[0]);
	output_string = output_string + ".";
	return output_string;
}

int main()
{
    std::cout << "Type your number, up to nine digits long:\n"; 
	int digits;
	std::cin >> digits;
	if (digits < 1000000000){
		std::cout << nine_digit_to_string(digits);
	} else {
		// Catch invalid inputs
		std::cout << "I don't know how to print that";
	}
}
