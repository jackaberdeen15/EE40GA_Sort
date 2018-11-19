
#include "ArrayItem.h"
#include "generalArray.h"
//this is release 3
void test_array(int array_size, basic_item* ref_item, char data_entry_method, int field, bool direction)
{
	basic_sort_criteria srt_crt(true);
	general_array test_array;
    
    
    switch (field){
        case HEIGHT:
            srt_crt.set_data_sort_type(HEIGHT);
			srt_crt.setAscending(direction);
            break;
        case WEIGHT:
            srt_crt.set_data_sort_type(WEIGHT);
			srt_crt.setAscending(direction);
            break;
        case BLOODTYPE:
            srt_crt.set_data_sort_type(BLOODTYPE);
			srt_crt.setAscending(direction);
            break;
        case SURNAME:
            srt_crt.set_data_sort_type(SURNAME);
			srt_crt.setAscending(direction);
            break;
        case FIRSTNAME:
            srt_crt.set_data_sort_type(FIRSTNAME);
			srt_crt.setAscending(direction);
            break;
		case NATIONALITY:
			srt_crt.set_data_sort_type(NATIONALITY);
			srt_crt.setAscending(direction);
			break;
		case STUDENTID:
			srt_crt.set_data_sort_type(STUDENTID);
			srt_crt.setAscending(direction);
			break;
		case EMAIL:
			srt_crt.set_data_sort_type(EMAIL);
			srt_crt.setAscending(direction);
			break;
		case DEGREE:
			srt_crt.set_data_sort_type(DEGREE);
			srt_crt.setAscending(direction);
			break;
		case DOB:
			srt_crt.set_data_sort_type(DOB);
			srt_crt.setAscending(direction);
			break;
		case CURRENTCGS:
			srt_crt.set_data_sort_type(CURRENTCGS);
			srt_crt.setAscending(direction);
			break;
		case PREVIOUSCGS:
			srt_crt.set_data_sort_type(PREVIOUSCGS);
			srt_crt.setAscending(direction);
			break;
		case YEAR:
			srt_crt.set_data_sort_type(YEAR);
			srt_crt.setAscending(direction);
			break;
        default:
            break;
            
    }
	
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
    cout << "search array by min and max ?" <<endl;
    
    //typedef enum {FIRSTNAME, SURNAME, BLOODTYPE, HEIGHT, WEIGHT, NATIONALITY, STUDENTID, EMAIL, DEGREE, DOB, CURRENTCGS, PREVIOUSCGS} data_sort_type;

    switch (field){

        case HEIGHT:
        {
            student_record min;
            student_record max;
            
            cout << "min_HEIGHT=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_HEIGHT=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case WEIGHT:
        {
            student_record min;
            student_record max;
            
            cout << "min_WEIGHT=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_WEIGHT=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case BLOODTYPE:
        {
            student_record min;
            student_record max;
            
            cout << "min_BLOODTYPE=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_BLOODTYPE=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case SURNAME:
        {
            student_record min;
            student_record max;
            
            cout << "min_SURNAME=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_SURNAME=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case FIRSTNAME:
        {
            student_record min;
            student_record max;
            
            cout << "min_FIRSTNAME=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_FIRSTNAME=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case NATIONALITY:
        {
            student_record min;
            student_record max;
            
            cout << "min_NATIONALITY=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_NATIONALITY=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case STUDENTID:
        {
            student_record min;
            student_record max;
            
            cout << "min_STUDENTID=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_STUDENTID=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case EMAIL:
        {
            student_record min;
            student_record max;
            
            cout << "email_STUDENTID=";
            min.AssignSpeificItem(&srt_crt);
            cout << "email_STUDENTID=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case DEGREE:
        {
            student_record min;
            student_record max;
            
            cout << "min_DEGREE=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_DEGREE=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case DOB:
        {
            student_record min;
            student_record max;
            
            cout << "min_DOB=";
            min.AssignSpeificItem();
            cout << "max_DOB=";
            max.AssignSpeificItem();
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case CURRENTCGS:
        {
            student_record min;
            student_record max;
            
            cout << "min_CURRENTCGS=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_CURRENTCGS=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
        case PREVIOUSCGS:
        {
            student_record min;
            student_record max;
            
            cout << "min_PREVIOUSCGS=";
            min.AssignSpeificItem(&srt_crt);
            cout << "max_PREVIOUSCGS=";
            max.AssignSpeificItem(&srt_crt);
            test_array.findItemsWithinRange(&min,&max,&srt_crt);
            test_array.printArrayOnScreen();
        }
            break;
		case YEAR:
		{
			student_record min;
			student_record max;

			cout << "min_YEAR=";
			min.AssignSpeificItem(&srt_crt);
			cout << "max_YEAR=";
			max.AssignSpeificItem(&srt_crt);
			test_array.findItemsWithinRange(&min, &max, &srt_crt);
			test_array.printArrayOnScreen();
		}
		break;
        default:
            break;
            
    }
	}

int main()
{
	int array_size;
	int temp;
	char mode;
    int field;
	int direction;
	bool directionbool;
    //char order;
    
	student_record ref_item; 	//composite item reference for general array
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
    cout << "Enter field to search by: {0:FIRSTNAME, 1:SURNAME, 2:BLOODTYPE, 3:HEIGHT, 4:WEIGHT, 5:NATIONALITY, 6:STUDENT ID, 7:EMAIL, 8:DEGREE, 9:DOB, 10:CURRENT CGS, 11:PREVIOUS CGS, 12:YEAR}" << endl << endl;
    cin >> field;
	cout << endl;
	if(field==0 || field == 1 || field == 2 ||field==5 || field==7 || field==8 ){
			cout << "How would you like to sort" << endl << "1 = Ascending = A ---> Z" << endl << "2 = Descending = Z ---> A" << endl << endl;
			cin >> direction;
	}
	else if (field == 3 || field == 4 || field == 10 || field == 6 || field == 10 || field == 11 || field == 12) {
		cout << "How would you like to sort" << endl << "1 = Ascending = Lowest ---> Highest" << endl << "2 = Descending = Highest ---> Lowest" << endl << endl;
		cin >> direction;
	}
	else if (field == 9) {
		cout << "How would you like to sort" << endl << "1 = Ascending = Youngest ---> Oldest" << endl << "2 = Descending = Oldest ---> Youngest" << endl << endl;
		cin >> direction;
	}
	if (direction == 1 || direction == 2) {
		if (direction == 1) {
			directionbool = true;
		}
		if (direction == 2) {
			directionbool = false;
		}
	}
	else {
		cout << "Error: Please enter a valid choice." << endl << endl;
		return 0;
	}
	cout << endl;
	cout << "Testing array with composite items: " << endl << endl;
	test_array(array_size, &ref_item, mode, field, directionbool);
	cout << "Test Complete." << endl << "Enter any number to end the test." << endl;
	cin >> temp;
    
    return 0;
}
