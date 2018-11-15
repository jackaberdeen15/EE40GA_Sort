#ifndef __ARRAYITEM_H_
#define __ARRAYITEM_H_

#include <iostream>
using namespace std;

#include "stdlib.h" 
#include "time.h" 
#include <string>
#include <sstream>
#include <fstream>

////// this is needed to check compatibility between items (and to use a derived-class pointer that is passes as "base class")
template <class Base, class Derived> Derived* typecastItem(Base* basic_ptr, Derived* derivedItem_ptr)
{
	Derived* typecasted_ptr=dynamic_cast <Derived *>(basic_ptr);

	if(typecasted_ptr==NULL)				
		printf("\n Error typecasting item: type does not match the expected derived item\n");

	return typecasted_ptr;
}
//////

typedef enum {FIRSTNAME, SURNAME, BLOODTYPE, HEIGHT, WEIGHT} data_sort_type;


// this is the base version of an object that holds the information about sorting ctiteria.
// for simple array items: the options "ascending/descending" affred here suffice.
// For more complex/composite array items: an appropriate sort criteria should be deirved from 
// this base class and used in "IsLargerThan" 
class basic_sort_criteria{
protected:
	bool ascending;
	void basic_initialization(){setAscending(true);}
	//int field_type=0;
public:
	basic_sort_criteria(){basic_initialization();}
	basic_sort_criteria(bool value){setAscending(value);}
	void setAscending(bool value){ascending=value;}
	bool getAscending(){return ascending;}	
	//void set_field_sort_type(int type) { field_type = type; }
};
//parent item
class basic_item{
protected:
	bool empty;

public:
	basic_item(){empty=true;}
	~basic_item(){;}
	
	bool isEmpty(){return empty;}
	
	//The following must be implemented by any derived item:	


	virtual void printItemOnScreen()=0;
	virtual void enterItemFromKeyboard()=0;
	//virtual void loadItemFromFile(FILE* fin)=0;
	virtual void generateRandomItem()=0;
	
	// Needed for sorting; the second paratmer holds the information about soritng ctireria;
	// If you do not supply a second parameter, a default option (simple ascending sorting) is assumed 
	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)=0;

	virtual basic_item* allocateItem()=0;
	virtual void deallocateItem(basic_item* item_ptr)=0;
	//virtual basic_item* makeCopyofItem()=0;

};

// height item child
class height_item: public basic_item{
protected:
	int item_value;
	
public:
	// default constructor and destructor: do nothing
	height_item(){;}
	~height_item(){;}

	int getItemVal(){return item_value;}
	
	virtual void printItemOnScreen()
	{
		if(isEmpty())
			cout << "Item is empty." << endl;
		else
			cout << "Item value is " << getItemVal() << " . " << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert element then hit enter." << endl;
		cin >> item_value;
		cout << endl;
		
		// item filled
		empty=false;
	}

	virtual void generateRandomItem()
	{
		int item;
		int max_rand_val = 193;

		item=rand();
		item = item % (max_rand_val+1);

		item_value=item;
		// item filled
		empty=false;
		
	}
	
	//virtual void loadItemFromFile(FILE* fin);
	
	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
	{
		bool result=false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		height_item* typecasted_other_item = typecastItem(other_item, this);
		
		// check that it worked
		if(typecasted_other_item==NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if( getItemVal() > (typecasted_other_item->getItemVal()) )
			result=true;


		// chek if there are sorting options to apply 
		if(sort_criteria!=NULL)
		{
			// if sorting is in descending order the result is reversed 
			if( !( sort_criteria->getAscending() ) )
				result=!result;
		}

		return result;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		height_item* typecasted_item_ptr = typecastItem(item_ptr, this);
		
		// check that it worked
		if(typecasted_item_ptr==NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for integer_item): "<< endl << "Other item is not of type integer_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}
	virtual basic_item* allocateItem()
	{
		height_item* result = new height_item;
		if(result==NULL)
			cout << " Error in integer_item::allocateItem(): out of memory"<< endl;
		return result;
	}
};

//weight item child
class weight_item: public basic_item{
protected:
	int item_value;

public:
	// default constructor and destructor: do nothing
	weight_item() { ; }
	~weight_item() { ; }

	int getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty())
			cout << "Item is empty." << endl;
		else
			cout << "Item value is " << getItemVal() << " . " << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert element then hit enter." << endl;
		cin >> item_value;
		cout << endl;

		// item filled
		empty = false;
	}

	virtual void generateRandomItem()
	{
		int item;
		int max_rand_val = 120;

		item = rand();
		item = item % (max_rand_val + 1);

		item_value = item;
		// item filled
		empty = false;

	}

	//virtual void loadItemFromFile(FILE* fin);

	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		weight_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() > (typecasted_other_item->getItemVal()))
			result = true;


		// chek if there are sorting options to apply 
		if (sort_criteria != NULL)
		{
			// if sorting is in descending order the result is reversed 
			if (!(sort_criteria->getAscending()))
				result = !result;
		}

		return result;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		weight_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for integer_item): " << endl << "Other item is not of type integer_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}
	virtual basic_item* allocateItem()
	{
		weight_item* result = new weight_item;
		if (result == NULL)
			cout << " Error in integer_item::allocateItem(): out of memory" << endl;
		return result;
	}
};

//class to use firstnames child
class firstname_item : public basic_item {
protected:
	string item_value;
	string firstname[13] = { "Chad", "Kronisford", "Jack", "Will", "Tom", "Gerald", "Bertram", "Chowdrey", "Alistair", "Benisford", "Gideon", "Quarian", "Magnus" };
	//string surname[12] = { "Atherton", "Godfrey", "MacLean", "Fyfe", "Connington", "Reese-Mogg", "Jeoffrey-Brown", "Buckinham", "Pensombry", "Addington", "Chadlington", "Chad" };
	//string bloodtype[8] = { "O-", "O+", "A-", "A+", "B-","B+", "AB-","AB+" };
	//int type = 3; //3 by default

public:
	firstname_item() { ; }
	~firstname_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "String is Empty." << endl;
		}
		else
			cout << "String is " << getItemVal() << "." << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert element then hit enter." << endl;
		getline(cin, item_value);
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()//1 is firstname, 2 is surname, 3 is blood type
	{
		int i;
		i = rand() % 13;
		item_value = firstname[i];
		/*switch (type) {
			case 1: 
				i = rand() % 13;
				item_value = firstname[i];
				break;
			
			case 2: 
				i = rand() % 12;
				item_value = surname[i];
				break;
			
			case 3: 
				i = rand() % 8;
				item_value = bloodtype[i];
				break;
			
			default:
				break;
		}*/
		// item filled
		empty = false;
	}

	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		firstname_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type string_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal())>0))
			result = true;



		// chek if there are sorting options to apply 
		if (sort_criteria != NULL)
		{
			// if sorting is in descending order the result is reversed 
			if (!(sort_criteria->getAscending()))
				result = !result;
		}

		return result;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		firstname_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for string_item): " << endl << "Other item is not of type string_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		firstname_item* result = new firstname_item;
		if (result == NULL)
			cout << " Error in string_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for surnames child
class surname_item : public basic_item {
protected:
	string item_value;
	//string firstname[13] = { "Chad", "Kronisford", "Jack", "Will", "Tom", "Gerald", "Bertram", "Chowdrey", "Alistair", "Benisford", "Gideon", "Quarian", "Magnus" };
	string surname[12] = { "Atherton", "Godfrey", "MacLean", "Fyfe", "Connington", "Reese-Mogg", "Jeoffrey-Brown", "Buckinham", "Pensombry", "Addington", "Chadlington", "Chad" };
	//string bloodtype[8] = { "O-", "O+", "A-", "A+", "B-","B+", "AB-","AB+" };
	//int type = 3; //3 by default

public:
	surname_item() { ; }
	~surname_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "String is Empty." << endl;
		}
		else
			cout << "String is " << getItemVal() << "." << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert element then hit enter." << endl;
		getline(cin, item_value);
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()//1 is firstname, 2 is surname, 3 is blood type
	{
		int i;
		i = rand() % 12;
		item_value = surname[i];
		/*switch (type) {
			case 1:
				i = rand() % 13;
				item_value = firstname[i];
				break;

			case 2:
				i = rand() % 12;
				item_value = surname[i];
				break;

			case 3:
				i = rand() % 8;
				item_value = bloodtype[i];
				break;

			default:
				break;
		}*/
		// item filled
		empty = false;
	}

	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		surname_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type string_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) > 0))
			result = true;



		// chek if there are sorting options to apply 
		if (sort_criteria != NULL)
		{
			// if sorting is in descending order the result is reversed 
			if (!(sort_criteria->getAscending()))
				result = !result;
		}

		return result;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		surname_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for string_item): " << endl << "Other item is not of type string_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		surname_item* result = new surname_item;
		if (result == NULL)
			cout << " Error in string_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for bloodtypes child
class bloodtype_item : public basic_item {
protected:
	string item_value;
	//string firstname[13] = { "Chad", "Kronisford", "Jack", "Will", "Tom", "Gerald", "Bertram", "Chowdrey", "Alistair", "Benisford", "Gideon", "Quarian", "Magnus" };
	//string surname[12] = { "Atherton", "Godfrey", "MacLean", "Fyfe", "Connington", "Reese-Mogg", "Jeoffrey-Brown", "Buckinham", "Pensombry", "Addington", "Chadlington", "Chad" };
	string bloodtype[8] = { "O-", "O+", "A-", "A+", "B-","B+", "AB-","AB+" };
	//int type = 3; //3 by default

public:
	bloodtype_item() { ; }
	~bloodtype_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "String is Empty." << endl;
		}
		else
			cout << "String is " << getItemVal() << "." << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert element then hit enter." << endl;
		getline(cin, item_value);
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()//1 is firstname, 2 is surname, 3 is blood type
	{
		int i;
		i = rand() % 8;
		item_value = bloodtype[i];
		/*switch (type) {
			case 1:
				i = rand() % 13;
				item_value = firstname[i];
				break;

			case 2:
				i = rand() % 12;
				item_value = surname[i];
				break;

			case 3:
				i = rand() % 8;
				item_value = bloodtype[i];
				break;

			default:
				break;
		}*/
		// item filled
		empty = false;
	}

	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		bloodtype_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type string_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) > 0))
			result = true;



		// chek if there are sorting options to apply 
		if (sort_criteria != NULL)
		{
			// if sorting is in descending order the result is reversed 
			if (!(sort_criteria->getAscending()))
				result = !result;
		}

		return result;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		bloodtype_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for string_item): " << endl << "Other item is not of type string_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		bloodtype_item* result = new bloodtype_item;
		if (result == NULL)
			cout << " Error in string_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

class composite_item : public basic_item {
protected:
	height_item h_item;
	weight_item w_item;
	firstname_item fn_item;
	surname_item sn_item;
	bloodtype_item bt_item;
	data_sort_type data_sorting_type=FIRSTNAME;

public:
	composite_item() { ; }
	~composite_item() { ; }

	virtual void printItemOnScreen()
	{
		h_item.printItemOnScreen();
		w_item.printItemOnScreen();
		fn_item.printItemOnScreen();
		sn_item.printItemOnScreen();
		bt_item.printItemOnScreen();

	}

	virtual void enterItemFromKeyboard()
	{
		h_item.enterItemFromKeyboard();
		w_item.enterItemFromKeyboard();
		fn_item.enterItemFromKeyboard();
		sn_item.enterItemFromKeyboard();
		bt_item.enterItemFromKeyboard();
	}

	//function to get random string from the protected
	virtual void generateRandomItem()//1 is firstname, 2 is surname, 3 is blood type
	{
		h_item.generateRandomItem();
		w_item.generateRandomItem();
		fn_item.generateRandomItem();
		sn_item.generateRandomItem();
		bt_item.generateRandomItem();
	}

	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;

		switch (data_sorting_type)
		{
		case HEIGHT:
			cout << "Item is height" << endl;
			result = h_item.IsLargerThan(other_item, sort_criteria);
			break;
		case WEIGHT:
			cout << "Item is weight" << endl;
			result = w_item.IsLargerThan(other_item, sort_criteria);
			break;
		case FIRSTNAME:
			cout << "Item is firstname" << endl;
			result = fn_item.IsLargerThan(other_item, sort_criteria);
			break;
		case SURNAME:
			cout << "Item is surname" << endl;
			result = sn_item.IsLargerThan(other_item, sort_criteria);
			break;
		case BLOODTYPE:
			cout << "Item is bloodtype" << endl;
			result = h_item.IsLargerThan(other_item, sort_criteria);
			break;
		default:
			break;
		}
		
		return result;
	}

	virtual void setDataSortType(data_sort_type datatype)
	{
		data_sorting_type = datatype;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		h_item.deallocateItem(item_ptr);
		w_item.deallocateItem(item_ptr);
		fn_item.deallocateItem(item_ptr);
		sn_item.deallocateItem(item_ptr);
		bt_item.deallocateItem(item_ptr);
	}

	virtual basic_item* allocateItem()
	{
		h_item.allocateItem();
		w_item.allocateItem();
		fn_item.allocateItem();
		sn_item.allocateItem();
		bt_item.allocateItem();
	}

	//virtual void setstringtype(int i) { type = i; }

};

#endif