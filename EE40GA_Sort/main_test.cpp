
#include "ArrayItem.h"
#include "generalArray.h"
//#include "SomeStringTests.cpp"






void test_array(int array_size, basic_item* ref_item, char data_entry_method)
{
	basic_sort_criteria srt_crt(true);
	general_array test_array;	
	
	// attach the "integer item" as referecen item
	cout << "Attachting reference..." << endl;
	test_array.attachRefrenceItem(ref_item);
	
	// now allocate the array	
	cout << "Allocating the array memory..." << endl;
	test_array.allocateArray(array_size);

	// print content to screen (empty)

	cout << " Array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();

	// fill with random items
	if (data_entry_method == 'r' || data_entry_method == 'R') {
		cout << endl << " Filling Array with random values." << endl;
		test_array.fillRandomValueArray();
	}
	else if (data_entry_method == 'm' || data_entry_method == 'M') {
		cout << "Populating database manually" << endl;
		test_array.enterArrayFromKeyboard();
	}
	// print content to screen
	test_array.printArrayOnScreen();
	// sort the array 
	cout << endl << " Sorting Array." << endl;
	test_array.bubblesort(&srt_crt);
	test_array.printArrayOnScreen();
	cout << endl;
}


int main()
{
	int array_size = 10;
	int temp;

	//composite item reference for general array
	composite_item ref_comp_item;
    

    cout << "Type R to populate database Randomly and M to populate Manually" << endl;

    char mode;
    while (cin.get(mode)) {
        if(mode=='r' || mode == 'R'){
                cout << "Populating database randomly" << endl;            
                break;
        }else if(mode=='m' || mode == 'M'){
                cout << "Populating database manually" << endl;
                break;
        }else{
                cout << "Error: please enter a valid choice" << endl;
                return 0;
        }
    }
	cout << " testing array with composite items: " << endl << endl;
	test_array(array_size, &ref_comp_item, mode);
	cout << " done. enter any number to end test." << endl;
	cin >> temp;
    
    return 0;
}
