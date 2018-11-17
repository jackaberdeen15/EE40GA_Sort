
#include "ArrayItem.h"
#include "generalArray.h"

void test_array(int array_size, basic_item* ref_item, char data_entry_method)
{
	basic_sort_criteria srt_crt(true);
	general_array test_array;	
	
	// attach the "integer item" as referecen item
	cout << "Attaching reference..." << endl;
	test_array.attachRefrenceItem(ref_item);
	
	// now allocate the array	
	cout << "Allocating the array memory..." << endl;
	test_array.allocateArray(array_size);

	// print content to screen (empty)

	cout << "The array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();

	// fill with random items
	if (data_entry_method == 'r' || data_entry_method == 'R') {
		cout << endl << "Filling Array..." << endl << endl;
		test_array.fillRandomValueArray();
	}
	else if (data_entry_method == 'm' || data_entry_method == 'M') {
		//cout << "Populating database manually" << endl;
		test_array.enterArrayFromKeyboard();
	}
	// print content to screen
	test_array.printArrayOnScreen();
	// sort the array 
	cout << endl << "Sorting Array..." << endl << endl;
	test_array.bubblesort(&srt_crt);
	test_array.printArrayOnScreen();
	cout << endl;
	}

int main()
{
	int array_size;
	int temp;
	char mode;
	composite_item ref_comp_item; 	//composite item reference for general array
	cout << "How many records would you like to create?" << endl;
	cin >> array_size;
	cout << endl;
	cout << "How would you like to generate your database:" << endl << "R = Randomly Generated" << endl << "M = Manual Input" << endl << endl;
	cin >> mode;
	cout << endl;
    if(mode=='r' || mode == 'R')
	{
		cout << "Populating Database: Random" << endl;            
	}
	else if(mode=='m' || mode == 'M')
	{
        cout << "Populating Database: Manual" << endl;
    }
	else
	{
        cout << "Error: Please enter a valid choice." << endl;
		return 0;
    }
	cout << "Testing array with composite items: " << endl << endl;
	test_array(array_size, &ref_comp_item, mode);
	cout << "Test Complete." << endl << "Enter any number to end the test." << endl;
	cin >> temp;
    
    return 0;
}
