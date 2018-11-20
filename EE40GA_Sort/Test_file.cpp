#include "ArrayItem.h"
#include "generalArray.h"


void test_array(int array_size, basic_item* ref_item, bool order)
{
	basic_sort_criteria srt_crt(order);
	general_array test_array;
	char data_entry_method='r';
	// attach the "integer item" as referecen item
	test_array.attachRefrenceItem(ref_item);
	// now allocate the array	
	test_array.allocateArray(array_size);
	// print content to screen (empty)
	cout << " Array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();

	cout << "How would you like to generate your database:" << endl << "R = Randomly Generated" << endl << "M = Manual Input" << endl << endl;
	cin >> data_entry_method;

	if (data_entry_method == 'r' || data_entry_method == 'R') {
		cout << endl << "Filling Array..." << endl << endl;
		test_array.fillRandomValueArray();
	}
	else if (data_entry_method == 'm' || data_entry_method == 'M') {
		//cout << "Populating database manually" << endl;
		test_array.enterArrayFromKeyboard();
	}
	else
	{
		cout << "Invalid Entry. Ending Program." << endl;
		return;
	}
	// print content to screen
	test_array.printArrayOnScreen();
	// sort the array 
	cout << endl << " Sorting Array." << endl;
	test_array.bubblesort(&srt_crt);
	test_array.printArrayOnScreen();
	cout << endl;
}

int main2()
{
	int order;
	bool ascending=true;
	int array_size = 10;
	int temp;
	// Used as "example item" by the general_array to populate the entire array with integer_item 
	integer_item ref_int_item;
	// Used as "example item" by the general_array to populate the entire array with neg_int_item 
	neg_int_item ref_nint_item;
	// First test with the inger item
	cout << " Testing array with integer (positve and negative) items: " << endl << endl;
	cout << "How do you want to sort the Array? 1:Ascending or 2:Descending?\nAscending is default." << endl;
	cin >> order;
	if (order == 2) { ascending = false; }
	test_array(array_size, &ref_int_item, ascending);
	cout << " Done. Enter any nymber to progress to the next test." << endl;
	cin >> temp;
	ascending = true;
	// Next test with the negative ingteger item
	cout << " Testing array with NEGATIVE ONLY integer items: " << endl << endl;
	cout << "How do you want to sort the Array? 1:Ascending or 2:Descending?\nAscending is default." << endl;
	cin >> order;
	if (order == 2) { ascending = false; }
	test_array(array_size, &ref_nint_item,ascending);
	cout << " Done. Enter any nymber to finish." << endl;
	cin >> temp;
	return 0;
}