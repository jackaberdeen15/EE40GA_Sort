
#include "ArrayItem.h"
#include "generalArray.h"
//#include "SomeStringTests.cpp"






void test_array(int array_size, basic_item* ref_item, char data_entry_method)
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
	// used as "example item" by the general_array to populate the entire array with integer_item 
	height_item ref_height_item;
	// used as "example item" by the general_array to populate the entire array with neg_int_item 
	weight_item ref_weight_item;
	// used as "example item" by the general_array to populate the entire array with firstname_item
	firstname_item ref_fname_item;
	// used as "example item" by the general_array to populate the entire array with surname_item
	surname_item ref_sname_item;
	// used as "example item" by the general_array to populate the entire array with bloodtype_item
	bloodtype_item ref_btype_item;

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
		cout << " testing array with composite items: " << endl << endl;
		test_array(array_size, &ref_comp_item, mode);
		cout << " done. enter any number to end test." << endl;
		cin >> temp;
    }
    
    return 0;
}
