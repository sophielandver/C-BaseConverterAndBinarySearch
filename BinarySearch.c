/*
 * Sophie Landver
 * CIS 314 Fall 2015 Lab 1
 *
 * This program reads a sorted array from a file and finds a requested number
 *    using recursive or iterative binary search. The array is read from a file
 *    defined by FILE_NAME, which should be written as the number of elements
 *    followed by the elements themselses. each number can be deliniated with
 *    any whitepace character. Also, the maximum size of the array is defined 
 *    as MAX_SIZE.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 150
#define FILE_NAME "array.dat" //must include quotes




 int IterativeBinarySearch(int * array, int size, int x)
{
   /* This function performs iterative binary search on array. 
   Inputs: int * array: the array to search through
           int size : the size of the array
           int x: the integer to search for
   Returns: -1 if x is not in array and the index of x in array otherwise. 
   */
   
	int low = 0;
	int high = size - 1;
	int mid;
	while (low <= high)
	{
		mid = (low + high)/2;
		if(x > array[mid])
		{
			low = mid + 1;
		}
		else if (x < array[mid])
		{
			high = mid - 1;
		}
		else 
		{
			return mid;
		}
	}

	return -1; //x not in array

}

int RecursiveBinarySearch(int * array, int low, int high, int x)
{
   /* This function performs recursive binary search on array. 
   Inputs: int * array: the array to search through
           int low : the index of the array at which to start looking
           int high: the index at which to stop looking
           int x: the integer to search for
   Returns: -1 if x is not in array and the index of x in array otherwise.
   */

	if (low > high) //base case
	{
		return -1;
	}

	int mid = (low + high)/2;

	if (x > array[mid])
	{
		return RecursiveBinarySearch(array, (mid + 1), high, x);
	}
	else if (x < array[mid])
	{
		return RecursiveBinarySearch(array, low, (mid - 1), x);
	}
	else
	{
		return mid;
	}

}

void PrintArray(int * array, int arraySize)
{
   /* This function prints an array of integers.  
   Inputs: int * array: the array to be printed
           int arraySize : the size of the array
   Returns: nothing.
   */

	printf("Array = ");
	for (int i = 0; i<arraySize; i++)
   {
   		if (i == 0)
   		{
   			printf("[%d, ", array[i]);
   		}
   		else if (i == (arraySize -1))
   		{
   			printf("%d]\n", array[i]);
   		}
   		else
   		{
   			printf("%d, ", array[i]);
   		}
   }
}

void ReadFileIntoArray(int * array, int * size, char * in_file_name, FILE * in_file)
{
   /* This function reads integers from a file and stores them in an array.
   Inputs: int * array: the array in which the integers from the file will be stored in
           int * size : the address at which the size of the array will be stored 
           char * in_file_name: the string name of the file to read from
           FILE * in_file: a FILE pointer 
   Returns: nothing.
   */

   in_file = fopen(in_file_name, "r"); //open it
   fscanf(in_file, "%d", size);  //get first line which is size

   for (int i=0; i<(*size); i++)   //now scan rest of numbers starting on second line
   {
      fscanf(in_file, "%d", &array[i]);
   }

   fclose(in_file);
}



int main(void) {

   /* This function reads an array of integers from a file, performs iterative and 
   recursive binary search on the array, and prints the array, results of the two types of
   binary searches, and the execution times of each type of binary search. 
   */

   FILE *in_file; 
   int array[MAX_SIZE];
   int size;
   char in_file_name[] = FILE_NAME; //infilenmae[0] = a //string 

   ReadFileIntoArray(array, &size, in_file_name, in_file);

   printf("\n\n=== CIS314 Fall 2014 - Lab 1: Part 2: Program 2 ===\n\n");

   int x; 
   printf("Enter an integer to search array for: ");
   scanf("%d", &x);

   int IterativeResult;
   int IterativeDelta;
   clock_t t1, t2;
   t1 = clock();
   IterativeResult = IterativeBinarySearch(array, size, x);
   t2 = clock();
   IterativeDelta = t2 - t1;


   int RecursiveResult;
   int RecursiveDelta;
   clock_t t3, t4;
   t3 = clock();
   RecursiveResult = RecursiveBinarySearch(array, 0, (size -1), x);
   t4 = clock();
   RecursiveDelta = t4 - t3;

   PrintArray(array, size);

   printf("Iterative Binary Search Result: %d\n", IterativeResult);

   printf("Recursive Binary Search Result: %d\n", RecursiveResult);

   printf("Execution Time of Iterative Binary Search: %d\n", IterativeDelta);

   printf("Execution Time of Recursive Binary Search: %d\n", RecursiveDelta);

   return 0;

}





