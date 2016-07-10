/*
 * Sophie Landver
 * CIS 314 Fall 2015 Lab 1
 * Assigned project
 * 
 * This program converts a x base to y base converter [less than 16]. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NUM 16
#define MAX_DECIMAL 2147483647 //for int

// Implement the rest of the program

char list[] = "0123456789ABCDEF";


int ToDecimal(char * in_number, int in_base) 
{
	/* This function converts a number in any base from binary to hexadecimal 
	to a decimal number. 
	Inputs: char * in_number: the number to be converted
			int in_base: the base of which in_number is to be converted to
	Returns: the integer decimal number if no overflow occured. -1 if overflow occured. 
	*/

	int decimal = 0;
	int j = 0;
	for (int i=(strlen(in_number)-1); i>=0; i--)
	{
		if (decimal < 0 || decimal > MAX_DECIMAL) //checking for overflow
		{return -1;}
		char *pointer = strchr(list, in_number[j]);
		int index = pointer - list; // index at which the cofficient is in list
		int newpart =  index * (pow(in_base, i));
		decimal = decimal + newpart;
		j++;
	}

	return decimal;
}


int DecimalToDesiredBase(int decimal, int out_base, char * out_number, char * original_out_number)
{
	/* This function converts a decimal number to any user-defined base (base can be any
	base from binary t hexadecimal). 
	Inputs: int decimal: the decimal number to be converted
			int out_base: the base of which decimal is to be converted to
			char * out_number: representation of the decimal number in base out_base
			char * original_out_number: the address of the first element in out_number 
	Returns: 0 if no over flow occured. 1 if over flow occured. 
	*/

	if (decimal == 0) 
	{ return 0; } //base case

	//OVERFLOW CASE
	if (decimal!=0 && out_number < original_out_number) 
	{ return 1; }

	int quotient = decimal/out_base;
	int rem = decimal % out_base;
	char fixed_rem = list[rem];
	*out_number = fixed_rem; 
	return DecimalToDesiredBase(quotient, out_base, out_number-1, original_out_number);
}

void FillOutNumber(char * out_number, int size)
{
	/* This function fills the last element in out_number with a null character and fills
	the rest of the elements in out_number with zeros. 
	Inputs: char * out_number: the number to be filled 
			int size: the size of out_number
	Returns: nothing. 
	*/

	for (int i=0; i<(size); i++)
	{
		if (i == (size) -1)
		{
			out_number[i] = '\0';
		}
		else
		{
			out_number[i] = '0';
		}
	}
}

bool FractionalInNumber (char * in_number)
{
	/* This function checks if in_number is a fractional number. 
	Inputs: char * in_number: the number to be checked
	Returns: true if in_number is a fractional number and false otherwise. 
	*/
	
	char * found = strstr(in_number, ".");
	return (found != NULL);
}

bool InValidNumberInBaseX(char * in_number, int in_base)
{
	/* This function checks if in_number is a valid number in base in_base.
	Inputs: char * in_number: the number to be checked
			int in_base: the base of in_number
	Returns: true if in_number is an invalid number in base in_base and false otherwise. 
	*/

	//creating sublist of allowable digits for in_number
	char sublist[(in_base+1)];
	for (int j=0; j<=in_base; j++)
	{
		if(j==in_base)
		{
			sublist[j] = '\0';
		}
		else
		{
			char newelement = list[j];
			sublist[j] = newelement;
		}

	}

	//checking that every digit in in_number is contained in sublist
	int size = strlen(in_number);
	char * contained;
	char element_array[2];
	element_array[1] = '\0';
	for (int r=0; r<size; r++)
	{
		element_array[0] = in_number[r];
		contained = strstr(sublist, element_array);
		if (contained == NULL)
		{
			return true;
		}

	}
	return false;
}


int main(){

	/* This function converts an input number from any user-defined base to another 
	(base to hexadecimal).
	*/

	char in_number[MAX_NUM+1];
	int in_base = 0;
	int out_base = 0;
	char out_number[MAX_NUM+1];

	FillOutNumber(out_number, (MAX_NUM+1));

	printf("Enter an Input Number: ");
	scanf("%s", in_number);
	//FRACTIONAL INPUT CASE
	if(FractionalInNumber(in_number))
	{
		printf("Error: This converter does not allow fractional input numbers.\n");
		exit(1);
	}

 
	printf("Enter the Input Base: ");
	scanf("%d", &in_base);
	//IN BASE OUT OF RANGE CASE
	if (in_base<2 || in_base>16)
	{
		printf("Error: Input base is out of range; base should be in range [2,16]\n");
		exit(1);
	}

	//INVALID NUMBER IN BASE X CASE
	if(InValidNumberInBaseX(in_number, in_base))
	{
		printf("Error: You have entered an invalid input number in the input base. \n");
		exit(1);
	}


	printf("Enter an Output Base: ");
	scanf("%d", &out_base);

	//OUT BASE OUT OF RANGE CASE
	if (out_base<2 || out_base>16)
	{
		printf("Error: Output base is out of range; base should be in range [2,16]\n");
		exit(1);
	}


	int decimal;
	decimal = ToDecimal(in_number, in_base); 
	if (decimal == -1)
	{ 
		printf("Overflow Error, could not convert input number to decimal. \n"); 
		exit(1);
	}
	else
	{ printf("The input number in decimal is: %d\n", decimal); }


	int exit_value;
	exit_value = DecimalToDesiredBase(decimal, out_base, (out_number + (MAX_NUM-1)), out_number);
	if (exit_value == 0)
	{ printf("The input number in the output base is: %s\n",out_number); }
	else
	{ printf("Overflow Error, could not convert input number to the desired output base.\n"); }
	

	return 0;
}





