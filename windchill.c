#include <stdio.h>	// Include directs the compiler to also load the specified files. We are adding the code from
			// the .h files ("header" files, or libraries) so that we can use the values and functions 
			// inside these files. stdio.h is the standard input/output functions (printf, scanf, etc.) for the
			// specific architecture.
#include <stdlib.h>	// stdlib.h contains memory allocation and release functions for the specific architecture.
			// It may also include definitions for some variable types and conversion functions (from string
			// to double, for example).
#include <float.h>	// float.h contains definitions of float variable types (float, double). These may vary by
			// architecture (32 bit float vs 64 bit float).
#include <math.h>	// The math.h library contains some extended arithmetic functions ("pow" for exponentiation, "sqrt"
			// for square roots, etc.).
#include <stdbool.h>	// The stdbool.h file defines the boolean values for the machine architecture ("true" or "false').
			// These are almost universally the integer constants 1 for true and 0 for false.
#include <string.h>	// string.h contains functions and methods for handling characters as strings; C treats strings
			// as arrays of chars, and the string library provides more convenient ways of dealing with
			// these arrays as complete units (a string) instead of an array.


/* 
  This line defines a function that will be implemented later in the code. This is done so that the compiler
  is aware of the function (and how it is called) as it proceeds through the code. Remember that the compiler
  "reads" the code file top to bottom. Without this declaration the compiler will warn that function "chillTemp"
  doesn't exist or that it has been declared implicitly (without definition).
*/
double chillTemp(double curTemp, double curWindVel, char *unitRef);

/*
  "main" is a special keyword that defines the primary method (function) of the program. The compiler will set
  the entry point of the program to the main function. It is possible to have arguments for the main function
  that will be passed from the command line when the program is executed ex: "int main(int argCount, char *argVals[])"
  The number of arguments will be stored in argCount, and each argument (string) will be stored as an array element
  in argVals.
*/
int main(void) {
/*
  Here we define the variables we will be using in our program. The char types with a * before the name indicate
  that this is a pointer to where the variable data is stored. This is done because by default "strings" in C are
  treated as a sequence of bytes (chars). The pointer is to the start of the memory location where the string is
  located. If the value stored was "string," the variable is essentially saying 'start at "s"' Strings in C are
  null-terminated, meaning that a null character (\0) is at the end of the array of characters. This is how the
  compiler/system knows where the string ends, so the value above would be stored in memory as "string\0". The
  string.h library contains some useful functions and definitions for handling strings, but may not be necessary
  if string use is kept simple.
*/
    char *entVal = NULL;
    char tempUnit[2];
    char windUnit[4];
    double cnvWindVel = 0.0;
    double cnvTemp = 0.0;
    double tFact = -1.0;
    int readRes;
    long unsigned int inpLen;
/*
  We can use the "false" value for this boolean because we included the stdbool.h library, otherwise we would
  use an int and assign value 0.
*/
    bool exitCond = false;

/* 
  Here we start the program loop. In the condition for the while loop, the "!" inverts the value of the variable
  being evaluated, basically saying "while NOT exitCond." 
*/
    while(!exitCond){
		/*
		  && is a logical operator for AND; both conditions must be true to satisfy the condition. This loop
		  will repeat until the exit condition is set or the user enters a valid temperature.
		*/
		while (!exitCond && cnvTemp > tFact) {
				printf("Enter the measured temperature followed by C or F (press enter to quit): ");
			/* 
			  The getline function will read a line of input from the specified input device (in this case
			  stdin, the keyboard). The read line will be stored in entVal, the length (in bytes) of the input is
			  stotred in inpLen, and the function will return a value indicating the number of characters read (excluding
			  terminating nulls).
			*/
			readRes = getline(&entVal, &inpLen, stdin);
			// Check if we have any input (almost redundant since getline call above 
			// will not return until the user presses enter).
			if (readRes > 0) {
				if (inpLen > 0) {
					// If the only returned character is newline (press enter), then set the exit condition to true.
					if (entVal[0] == '\n') {
						exitCond = true;
					} else {
						/*
							The strtod function attemps to convert a string into a double decimal value. Valid
							(numeric) characters are loaded into the double cnvTemp, and any other characters are
							placed in the entVal string. Note that the original value of entVal is used as the input
							as the first parameter for strtod *AND* the output second parameter. This means that the
							original value will be lost, but we're not interested in preserving that anyways. This is
							introducing a problem, however, detailed further down.
						*/
						cnvTemp = strtod(entVal, &entVal);
						/*
							Here we check what temperature scale the user indicated. This evaluation is flawed, however, as I
							am assuming the user enters something like "8.3C" as input. Note that only the first character in
							entVal (with index 0) is being evaluated. If the user were to type "8.3 C" then this check would
							return false, as character 0 would be a space. Ideally we'd write a function to process the input
							and check only for vaalid characters, and return a true/false for the specified character.
						*/
						if ((entVal[0] == 'C') || (entVal[0] == 'c')) {
							/*
							  The user specified centigrade. Set the units and maximum temperature factor accordingly.
							  The strncpy function fills the target character arrays with each character from the provided
							  string literals, and then pads the remaining with nulls. In this case we have made sure that
							  our char arrays are large enough to contain the data ("C") and the null terminator (\0).
							*/
							strncpy(tempUnit, "C", 2);
							strncpy(windUnit, "kph", 4);
							tFact = 10.0;
						} else {
							strncpy(tempUnit, "F", 2);
							strncpy(windUnit, "mph", 4);
							tFact = 50.0;
						}
						
						/*
							We've now collected our input and done some evaluation. Below we set the input pointer entVal
							back to null so that getline can store data there again when the loop repeats. We also do
							one final check to see if the entered value will produce a valid result, else we will ask
							for input again. We're also setting entVal back to null so getline can load the input
							to memory again.
							
							But there's something wrong here. C requires the programmer to carefully account for all
							memory, especially for pointers or other things with otherwise unknown or unbounded values
							(types like int or long int are different, since they have pre-defined sizes, as we saw in
							the limits exercise). When we used getline above, it allocated the memory for entVal for
							us (that's handy!). However, when we then used strtod and passed entVal as the ouput, the strtod
							function changed the address of entVal to be a position inside the original string (the location
							of the non-numeric part of the input). So if the original input was "32.5F" then entVal would
							originally point to the "3". After running strtod, entVal now points to the "F". So what happened
							to the old location? Well, we lost track of it, but *it's still there,* holding the previous
							value of entVal. Each time this loop executes, a new memory location is allocated and the new
							value for entVal is stored there and the old one is lost. This will continue to use memory until
							all of the memory is used up, and is a condition known as a "memory leak."
							
							The solution in this case could be one of two things:
							- Don't re-use the pointer entVal, and instead use a new separate pointer. This way the memory
							  allocated for entVal can be properly released with the free() command.
							- Before using strtod, make a copy of the entVal pointer. The copy will reference the original
							  address location and can be used to release the allocated memory with the free() command.
						*/
						
						entVal = NULL;
						if (cnvTemp > tFact) {
								/*
									Here we check that the entered temperature is valid per the limits on the formula
									from https://en.wikipedia.org/wiki/Wind_chill
									Technically we should also be checking the wind speed, but that has been skipped.
								*/
								printf("Temperature must be less than %0.2lf degrees.\n\n", tFact);
						}
					}
				}
			}
		}

		// If we haven't set the exit condition, finish the input and calculate the wind chill value.
		if (!exitCond) {
			printf("Enter the measured wind velocity in %s: ", windUnit);
			/*
				Re-using entVal again without a call to free(), making the memory problem described above even worse.
				Note that if we were using a separate pointer for the output of strtod, we would *not* need to worry about
				using free() on *that* pointer before using it again. As stated above, this is because it is a pointer that 
				references a subsection of an already allocated block of memory (no memory was actually allocated to create it).
			*/
			readRes = getline(&entVal, &inpLen, stdin);
			cnvWindVel = strtod(entVal, &entVal);
			entVal = NULL;
				// Here we print our results, using the output of the function we defined above and have implemented below.
				printf("\nTemperature after windchill is %0.2lf %s\n", chillTemp(cnvTemp, cnvWindVel, tempUnit), tempUnit);

			// "Reset" variables in anticipation of the next iteration.
			cnvTemp = 0.0;
			cnvWindVel = 0.0;
			tFact = -1.0;
		}
    }

	// If exitCond becomes true, we end up here. Return 0 to the operating system and exit the program.
    return 0;
}

/*
	This is the implementation of the function we declared above. It returns a double and takes three doubles as input.
	We could have put the definition / implementation in the same place we did the declaration. In a single-file program
	like this it does not matter. Being able to have separate declarations and definitions becomes important when
	creating libraries, where the header files contain the function declarations and the library files the definitions.
*/
double chillTemp(double curTemp, double curWindVel, char *unitRef) {
	// Declaring a local variable to store our calculation results. Since we didn't use the static keyword,
	// this variable will be lost when this function finishes executing.
    double calcTemp = 0.0;

	// Here we check which units are being used and calculate the appropriate wind chill value. The pow function
	// is provided in math.h and allows us to raise a value to an arbitrary power.
    if (unitRef[0] == 'C') {
		calcTemp = 13.12 + (0.6125 * curTemp) - (11.37  * pow(curWindVel, 0.16)) + (0.3965 * curTemp * pow(curWindVel, 0.16));
    } else {
    	calcTemp = 35.74 + (0.6125 * curTemp) - (35.75  * pow(curWindVel, 0.16)) + (0.4275 * curTemp * pow(curWindVel, 0.16));
    }

	// Return the calculated value to the main program loop where the function was called.
    return calcTemp;
}
