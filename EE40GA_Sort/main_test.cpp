
#include "arrayItem.h"
#include "generalArray.h"
//#include "SomeStringTests.cpp"






void test_array(int array_size, basic_item* ref_item)
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


void main()
{
	int array_size = 10;
	int temp;	
	// used as "example item" by the general_array to populate the entire array with integer_item 
	integer_item ref_int_item;
	// used as "example item" by the general_array to populate the entire array with neg_int_item 
	neg_int_item ref_nint_item;
	// used as "example item" by the general_array to populate the entire array with firstname_item
	firstname_item ref_fname_item;
	// used as "example item" by the general_array to populate the entire array with surname_item
	surname_item ref_sname_item;
	// used as "example item" by the general_array to populate the entire array with bloodtype_item
	bloodtype_item ref_btype_item;

	// first test with the inger item
	cout << " testing array with integer (positve and negative) items: " << endl << endl;
	test_array(array_size, &ref_int_item);
	cout << " done. enter any nymber to progress to the next test." << endl;
	cin>>temp;
	// next test with the negative ingteger item
	cout << " testing array with negative only integer items: " << endl << endl;
	test_array(array_size, &ref_nint_item);
	cout << " done. enter any nymber to progress to the next test." << endl;
	cin>>temp;
	//finally test with string
	cout << " testing array with firstname items: " << endl << endl;
	test_array(array_size, &ref_fname_item);
	cout << " done. enter any nymber to finish." << endl;
	cin >> temp;
	//
	cout << " testing array with surname items: " << endl << endl;
	test_array(array_size, &ref_sname_item);
	cout << " done. enter any nymber to finish." << endl;
	cin >> temp;
	//
	cout << " testing array with bloodtype items: " << endl << endl;
	test_array(array_size, &ref_btype_item);
	cout << " done. enter any nymber to finish." << endl;
	cin >> temp;

}
