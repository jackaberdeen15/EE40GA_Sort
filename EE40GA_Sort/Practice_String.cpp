//Fabios Headers
#include "arrayItem.h"
#include "generalArray.h"

//General Headers
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void string_array(int array_size, basic_item* ref_item)
{
	basic_sort_criteria srt_crt(true);
	general_array test_array;
	// attach the "integer item" as referecen item
	test_array.attachRefrenceItem(ref_item);
	// now allocate the array	
	test_array.allocateArray(array_size);
	// print content to screen (empty)
	cout << " Array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();
	// fill with random items
	cout << endl << " Filling Array with random values." << endl;
	test_array.fillRandomValueArray();
	// print content to screen
	test_array.printArrayOnScreen();
	// sort the array 
	cout << endl << " Sorting Array." << endl;
	test_array.bubblesort(&srt_crt);
	test_array.printArrayOnScreen();
	cout << endl;
}