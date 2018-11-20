
#include "ArrayItem.h"
#include "generalArray.h"
//this is release 3
void test_array(int array_size, basic_item* ref_item, char data_entry_method, int field, bool direction)
{
	basic_sort_criteria srt_crt(true);
	general_array test_array;
	int search, searchtype;
    
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
		case LEVEL:
			srt_crt.set_data_sort_type(LEVEL);
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
    
	cout << "Would you like to search these records:" << endl << "1 = Yes" << endl << "2 = No" << endl << endl;
	cin >> search;
	cout << endl;
	if (search == 1) {
		switch(field){
		case HEIGHT:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << "3 - Item is between these values" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				cout << endl;
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << "Printing records which contain value:\n";
				test_array.findItemsThatInclude(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 3) {
				student_record min;
				student_record max;
				cin.ignore();
				cout << "Minimum Height:";
				min.AssignSpeificItem(&srt_crt);
				cout << "Maximum Height=";
				max.AssignSpeificItem(&srt_crt);
				cout << "Printing records within range:\n";
				test_array.findItemsWithinRange(&min, &max, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case WEIGHT:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << "3 - Item is between these values" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				cout << endl;
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else if (searchtype == 3) {
				student_record min;
				student_record max;
				cin.ignore();
				cout << "Minimum Weight:=";
				min.AssignSpeificItem(&srt_crt);
				cout << "Maximum Weight:=";
				max.AssignSpeificItem(&srt_crt);
				cout << "Printing records within range:\n";
				test_array.findItemsWithinRange(&min, &max, &srt_crt);
				//test_array.printArrayOnScreen();
				cout << "\n";
			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case BLOODTYPE:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case SURNAME:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case FIRSTNAME:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case NATIONALITY:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case STUDENTID:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << "3 - Item is between these values" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				cout << endl;
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else if (searchtype == 3) {
				student_record min;
				student_record max;
				cin.ignore();
				cout << "Minimum Student ID:=";
				min.AssignSpeificItem(&srt_crt);
				cout << "Maximum Student ID=";
				max.AssignSpeificItem(&srt_crt);
				cout << "Printing records within range:\n";
				test_array.findItemsWithinRange(&min, &max, &srt_crt);
				//test_array.printArrayOnScreen();
				cout << "\n";
			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case EMAIL:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case DEGREE:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case DOB:
		{

		}
		break;
		case CURRENTCGS:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << "3 - Item is between these values" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				cout << endl;
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else if (searchtype == 3) {
				student_record min;
				student_record max;
				cin.ignore();
				cout << "Minimum Current CGS:=";
				min.AssignSpeificItem(&srt_crt);
				cout << "Maximum Current CGS:=";
				max.AssignSpeificItem(&srt_crt);
				cout << "Printing records within range:\n";
				test_array.findItemsWithinRange(&min, &max, &srt_crt);
				//test_array.printArrayOnScreen();
				cout << "\n";
			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case PREVIOUSCGS:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << "3 - Item is between these values" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				cout << endl;
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else if (searchtype == 3) {
				student_record min;
				student_record max;
				cin.ignore();
				cout << "Minimum Previous CGS:=";
				min.AssignSpeificItem(&srt_crt);
				cout << "Maximum Previous CGS:=";
				max.AssignSpeificItem(&srt_crt);
				cout << "Printing records within range:\n";
				test_array.findItemsWithinRange(&min, &max, &srt_crt);
				//test_array.printArrayOnScreen();
				cout << "\n";
			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		case LEVEL:
		{
			cout << "Which type of search would you like to carry out:" << endl << "1 - Item is exactly value" << endl << "2 - Value appears anywhere in item" << endl << "3 - Item is between these values" << endl << endl;
			cin >> searchtype;
			cout << endl;
			if (searchtype == 1) {
				student_record exact;
				cin.ignore();
				cout << "What are you searching for? (not case sensitive):";
				exact.AssignSpeificItem(&srt_crt);
				cout << endl;
				cout << "Printing records which match:\n";
				test_array.findItemsThatMatch(&exact, &srt_crt);
				cout << endl;
				//test_array.printArrayOnScreen();
			}
			else if (searchtype == 2) {

			}
			else if (searchtype == 3) {
				student_record min;
				student_record max;
				cin.ignore();
				cout << "Minimum Level:=";
				min.AssignSpeificItem(&srt_crt);
				cout << "Maximum Level:=";
				max.AssignSpeificItem(&srt_crt);
				cout << "Printing records within range:\n";
				test_array.findItemsWithinRange(&min, &max, &srt_crt);
				//test_array.printArrayOnScreen();
				cout << "\n";
			}
			else {
				cout << "Please enter a valid input." << endl;
			}
		}
		break;
		default:
		break;
		}
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
	ref_item.setupPrint();
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
    cout << "Enter field to sort by: {0:FIRSTNAME, 1:SURNAME, 2:BLOODTYPE, 3:HEIGHT, 4:WEIGHT, 5:NATIONALITY, 6:STUDENT ID, 7:EMAIL, 8:DEGREE, 9:DOB, 10:CURRENT CGS, 11:PREVIOUS CGS, 12:LEVEL}" << endl;
    cout << "Please note - if you wish to search through records you must sort by that type at this point." << endl;
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
