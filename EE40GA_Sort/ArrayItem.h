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


// this is the base version of an object that holds the information about sorting ctiteria.
// for simple array items: the options "ascending/descending" affred here suffice.
// For more complex/composite array items: an appropriate sort criteria should be deirved from 
// this base class and used in "IsLargerThan" 
class basic_sort_criteria{
protected:
	bool ascending;
	void basic_initialization(){setAscending(true);}
public:
	basic_sort_criteria(){basic_initialization();}
	basic_sort_criteria(bool value){setAscending(value);}
	void setAscending(bool value){ascending=value;}
	bool getAscending(){return ascending;}	
};



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

// Example of derived class implementing an integer item
class integer_item: public basic_item{
protected:
	int item_value;
	
public:
	// default constructor and destructor: do nothing
	integer_item(){;}
	~integer_item(){;}

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
		int max_rand_val = 1000;

		item=rand();
		item = item % (max_rand_val+1);

		// turn to negative 50% of the time
		if( (rand()%10) >=5 )
			item=(-1)*item;

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
		integer_item* typecasted_other_item = typecastItem(other_item, this);
		
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
		integer_item* typecasted_item_ptr = typecastItem(item_ptr, this);
		
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
		integer_item* result = new integer_item;
		if(result==NULL)
			cout << " Error in integer_item::allocateItem(): out of memory"<< endl;
		return result;
	}
};


// This object only accepts negative elements; it is readily derived from integer_item 
// by implementing only a few functions (all others are inhereited from the parent).
class neg_int_item: public integer_item{
public:
	// We must implement the following two functions to allocate/free neg_int_item differently from integer_item
	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		neg_int_item* typecasted_item_ptr = typecastItem(item_ptr, this);
		
		// check that it worked
		if(typecasted_item_ptr==NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for neg_int_item): "<< endl << "Other item is not of type integer_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}
	virtual basic_item* allocateItem()
	{
		neg_int_item* result = new neg_int_item;
		if(result==NULL)
			cout << " Error in neg_int_item::allocateItem(): out of memory"<< endl;
		return result;
	}
	//---------------------------------------------------------------------------------------//
	// We implement the following two functions to fill neg_int_item differently from integer_item
	virtual void enterItemFromKeyboard()
	{
		//warn the user:
		cout << "Insertion of neg_int_item: element value must be negative." << endl;
		// loop till you get a negative input number
		while(empty)
		{
			//call the parent funciton to fill the object
			integer_item::enterItemFromKeyboard();
			if(getItemVal()>=0)
				empty=true;
		}
	}
	virtual void generateRandomItem()
	{
		// loop till you get a negative random number
		while(empty)
		{
			//call the parent funciton to fill the object
			integer_item::generateRandomItem();
			if(getItemVal()>=0)
				empty=true;
		}
	}

};

//class to use string items
class string_item : public basic_item {
protected:
	string item_value;
	string firstname[13] = { "Chad", "Kronisford", "Jack", "Will", "Tom", "Gerald", "Bertram", "Chowdrey", "Alistair", "Benisford", "Gideon", "Quarian", "Magnus" };
	string surname[12] = { "Atherton", "Godfrey", "MacLean", "Fyfe", "Connington", "Reese-Mogg", "Jeoffrey-Brown", "Buckinham", "Pensombry", "Addington", "Chadlington", "Chad" };
	string bloodtype[8] = { "O-", "O+", "A-", "A+", "B-","B+", "AB-","AB+" };
	int type = 3; //3 by default

public:
	string_item() { ; }
	~string_item() { ; }

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
		switch (type) {
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
		}
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
		string_item* typecasted_other_item = typecastItem(other_item, this);

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
		string_item* typecasted_item_ptr = typecastItem(item_ptr, this);

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
		string_item* result = new string_item;
		if (result == NULL)
			cout << " Error in string_item::allocateItem(): out of memory" << endl;
		return result;
	}

	virtual void setstringtype(int i) { type = i; }

};



#endif