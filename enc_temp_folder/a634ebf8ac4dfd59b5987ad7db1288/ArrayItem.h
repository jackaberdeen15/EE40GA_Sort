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

typedef enum {FIRSTNAME, SURNAME, BLOODTYPE, HEIGHT, WEIGHT, NATIONALITY, STUDENTID, EMAIL, DEGREE, DOB, CURRENTCGS, PREVIOUSCGS, YEAR} data_sort_type;
//string path("/Users/willatherton/Desktop/output.csv");

// this is the base version of an object that holds the information about sorting ctiteria.
// for simple array items: the options "ascending/descending" affred here suffice.
// For more complex/composite array items: an appropriate sort criteria should be deirved from 
// this base class and used in "IsLargerThan" 
class basic_sort_criteria{
protected:
	bool ascending;
	void basic_initialization(){setAscending(true);}
	//int field_type=0;
    data_sort_type type =HEIGHT;
public:
	basic_sort_criteria(){basic_initialization();}
	basic_sort_criteria(bool value){setAscending(value);}
	void setAscending(bool value){ascending=value;}
	bool getAscending(){return ascending;}
    
    void set_data_sort_type(data_sort_type value){type=value;};
    data_sort_type get_data_sort_type(){return type;};
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
    //is smaller than
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)=0;

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL) = 0;

	virtual basic_item* allocateItem()=0;
	virtual void deallocateItem(basic_item* item_ptr)=0;
	//virtual basic_item* makeCopyofItem()=0;

};

// Example of derived class implementing an integer item
class integer_item : public basic_item {
protected:
	int item_value;

public:
	// default constructor and destructor: do nothing
	integer_item() { ; }
	~integer_item() { ; }

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
		int max_rand_val = 1000;

		item = rand();
		item = item % (max_rand_val + 1);

		// turn to negative 50% of the time
		if ((rand() % 10) >= 5)
			item = (-1)*item;

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
		integer_item* typecasted_other_item = typecastItem(other_item, this);

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

	virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		integer_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() < (typecasted_other_item->getItemVal()))
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		integer_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() == (typecasted_other_item->getItemVal()))
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
		integer_item* typecasted_item_ptr = typecastItem(item_ptr, this);

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
		integer_item* result = new integer_item;
		if (result == NULL)
			cout << " Error in integer_item::allocateItem(): out of memory" << endl;
		return result;
	}
};


// This object only accepts negative elements; it is readily derived from integer_item 
// by implementing only a few functions (all others are inhereited from the parent).
class neg_int_item : public integer_item {
public:
	// We must implement the following two functions to allocate/free neg_int_item differently from integer_item
	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		neg_int_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for neg_int_item): " << endl << "Other item is not of type integer_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}
	virtual basic_item* allocateItem()
	{
		neg_int_item* result = new neg_int_item;
		if (result == NULL)
			cout << " Error in neg_int_item::allocateItem(): out of memory" << endl;
		return result;
	}
	//---------------------------------------------------------------------------------------//
	// We implement the following two functions to fill neg_int_item differently from integer_item
	virtual void enterItemFromKeyboard()
	{
		//warn the user:
		cout << "Insertion of neg_int_item: element value must be negative." << endl;
		// loop till you get a negative input number
		while (empty)
		{
			//call the parent funciton to fill the object
			integer_item::enterItemFromKeyboard();
			if (getItemVal() >= 0)
				empty = true;
		}
	}
	virtual void generateRandomItem()
	{
		// loop till you get a negative random number
		while (empty)
		{
			//call the parent funciton to fill the object
			integer_item::generateRandomItem();
			if (getItemVal() >= 0)
				empty = true;
		}
	}

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
			cout << "\"height_item\" is empty." << endl;
		else
			cout << "Height(Cm): " << getItemVal() << endl;
        
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert height then hit enter." << endl;
		//getline(cin, item_value);
		cin >> item_value;
		cin.ignore();
		cout << endl;
		// item filled
		empty=false;
	}

	virtual void generateRandomItem()
	{
		int item;
		item = rand();
		item = (item % 50);
		item = item + 140;

		item_value = item;

		// item filled
		empty = false;
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
			cout << "Other item is not of type height_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
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
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		height_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() == (typecasted_other_item->getItemVal()))
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
		height_item* typecasted_item_ptr = typecastItem(item_ptr, this);
		
		// check that it worked
		if(typecasted_item_ptr==NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for height_item): "<< endl << "Other item is not of type height_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		height_item* result = new height_item;
		if(result==NULL)
			cout << " Error in height_item::allocateItem(): out of memory"<< endl;
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
			cout << "\"weight_item\" is empty." << endl;
		else
			cout << "Weight(Kg): " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert weight then hit enter." << endl;
		//getline(cin, item_value);
		cin >> item_value;
		cin.ignore();
		cout << endl;
		// item filled
		empty = false;
	}

	virtual void generateRandomItem()
	{
		int item;
		item = rand();
		item = (item % 91);
		item = item + 50;

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
			cout << "Other item is not of type weight_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        weight_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
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
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() == (typecasted_other_item->getItemVal()))
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
			cout << "Error in deallocateItem (for weight_item): " << endl << "Other item is not of type weight_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}
	virtual basic_item* allocateItem()
	{
		weight_item* result = new weight_item;
		if (result == NULL)
			cout << " Error in weight_item::allocateItem(): out of memory" << endl;
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
			cout << "\"firstname_item\" is Empty." << endl;
		}
		else
			cout << "Firstname: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert first name then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
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
			cout << "Other item is not of type firstname_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        firstname_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
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
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
			cout << "Error in deallocateItem (for firstname_item): " << endl << "Other item is not of type firstname_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		firstname_item* result = new firstname_item;
		if (result == NULL)
			cout << " Error in firstname_item::allocateItem(): out of memory" << endl;
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
			cout << "\"surname_item\" is Empty." << endl;
		}
		else
			cout << "Surname: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert surname then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
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
			cout << "Other item is not of type surname_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        surname_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
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
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
			cout << "Error in deallocateItem (for surname_item): " << endl << "Other item is not of type surname_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		surname_item* result = new surname_item;
		if (result == NULL)
			cout << " Error in surname_item::allocateItem(): out of memory" << endl;
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
			cout << "\"bloodtype_item\" is Empty." << endl;
		}
		else
			cout << "Bloodtype: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert bloodtype then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
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
			cout << "Other item is not of type bloodtype_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        bloodtype_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
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
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
			cout << "Error in deallocateItem (for bloodtype_item): " << endl << "Other item is not of type bloodtype_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		bloodtype_item* result = new bloodtype_item;
		if (result == NULL)
			cout << " Error in bloodtype_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for nationality child //i dont think we represent enough nationalities here
class nationality_item : public basic_item {
protected:
	string item_value;
	string nationality[111] = { "Afghan","Albanian","Algerian","Argentinian","Australian","Austrian","Bangladeshi","Belgian","Bolivian","Batswana","Brazilian","Bulgarian","Cambodian","Cameroonian","Canadian","Chilean","Chinese","Colombian","Costa Rican","Croatian","Cuban","Czech","Danish","Dominican","Ecuadorian","Egyptian","Salvadorian","English","Estonian","Ethiopian","Fijian","Finnish","French","German","Ghanaian","Greek","Guatemalan","Haitian","Honduran","Hungarian","Icelandic","Indian","Indonesian","Iranian","Iraqi","Irish","Israeli","Italian","Jamaican","Japanese","Jordanian","Kenyan","Kuwaiti","Lao","Latvian","Lebanese","Libyan","Lithuanian","Malaysian","Malian","Maltese","Mexican","Mongolian","Moroccan","Mozambican","Namibian","Nepalese","Dutch","New Zealand","Nicaraguan","Nigerian","Norwegian","Pakistani","Panamanian","Paraguayan","Peruvian","Philippine","Polish","Portuguese","Romanian","Russian","Saudi","Scottish","Senegalese","Serbian","Singaporean","Slovak","South African","Korean","Spanish","Sri Lankan","Sudanese","Swedish","Swiss","Syrian","Taiwanese","Tajikistani","Thai","Tongan","Tunisian","Turkish","Ukrainian","Emirati","British","American","Uruguayan","Venezuelan","Vietnamese","Welsh","Zambian","Zimbabwe" };

public:
	nationality_item() { ; }
	~nationality_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"nationality_item\" is Empty." << endl;
		}
		else
			cout << "Nationality: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert nationality then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		int i;
		i = rand() % 111;
		item_value = nationality[i];

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
		nationality_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type nationality_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        nationality_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		nationality_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
		nationality_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for nationality_item): " << endl << "Other item is not of type nationality_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		nationality_item* result = new nationality_item;
		if (result == NULL)
			cout << " Error in nationality_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for studentid child
class studentid_item : public basic_item {
protected:
	int item_value;

public:
	studentid_item() { ; }
	~studentid_item() { ; }

	int getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"studentid_item\" is Empty." << endl;
		}
		else
			cout << "Student ID: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert student ID then hit enter." << endl;
		//getline(cin, item_value);
		cin >> item_value;
		cin.ignore();
		cout << endl;
		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		int i;
		i = 51550000 + rand() % 9999;   //This is a trash way to generate a student ID, look into replacing with 8 randomly generated values chained into a string.
		item_value = i;

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
		studentid_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type studentid_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal()>typecasted_other_item->getItemVal())
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        studentid_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		studentid_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal()==typecasted_other_item->getItemVal())
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
		studentid_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for studentid_item): " << endl << "Other item is not of type studentid_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		studentid_item* result = new studentid_item;
		if (result == NULL)
			cout << " Error in studentid_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for e-mail address child
class email_item : public basic_item {
protected:
	string item_value;
	string emailpre[13] = { "Chad1997", "Kiehop", "PwNzEr", "Watty", "Custard90", "Fernando", "LotRFan83", "Winelover67", "Henry", "Swansong89", "Kush420", "IsThisLoss", "JollyRoger" };
	string emailsuf[9] = {"@hotmail.co.uk","@hotmail.com","@yahoo.co.uk","@yahoo.com","@abdn.ac.uk", "@aberdeen.ac.uk" ,"@gmail.co.uk","@gmail.com","@icloud.com"};
public:
	email_item() { ; }
	~email_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"email_item\" is Empty." << endl;
		}
		else
			cout << "E-mail Address: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert e-mail address then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		int i;
		int j;
		i = rand() % 13;
		j = rand() % 9;
		item_value = emailpre[i] + emailsuf[j]; // Does this actually work? I feel like it shouldn't...

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
		email_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type email_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        email_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		email_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
		email_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for email_item): " << endl << "Other item is not of type email_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		email_item* result = new email_item;
		if (result == NULL)
			cout << " Error in email_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for degree child
class degree_item : public basic_item {
protected:
	string item_value;
	string degreepre[2] = {"MEng","BEng" };
	string degreesuf[6] = {"Mechanical Engineering", "Chemical Engineering","Electrical & Electronic Engineering", "Petroleum Engineering","Electrical & Mechanical Engineering","Civil Engineering"};
public:
	degree_item() { ; }
	~degree_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"degree_item\" is Empty." << endl;
		}
		else
			cout << "Degree Programme: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert degree programme then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		int i;
		int j;
		i = rand() % 2;
		j = rand() % 6;
		item_value = degreepre[i] + " " + degreesuf[j]; // Does this actually work? I feel like it shouldn't...

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
		degree_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type degree_item." << endl;
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        degree_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type degree_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		degree_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type degree_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
		degree_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for degree_item): " << endl << "Other item is not of type degree_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		degree_item* result = new degree_item;
		if (result == NULL)
			cout << " Error in degree_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for date of birth child
class dateofbirth_item : public basic_item {
protected:
	string item_value;
public:
	dateofbirth_item() { ; }
	~dateofbirth_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"dateofbirth_item\" is Empty." << endl;
		}
		else
			cout << "Date of Birth: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert date of birth then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{

		int day = (rand() % 30);
		int month = rand() % 12;
		int year = 1950 + rand() % 68;
		item_value = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
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
		dateofbirth_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type dateofbirth_item." << endl;
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

	virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		dateofbirth_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type dateofbirth_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() < (typecasted_other_item->getItemVal()))
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		dateofbirth_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type dateofbirth_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
		dateofbirth_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for dateofbirth_item): " << endl << "Other item is not of type dateofbirth_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		degree_item* result = new degree_item;
		if (result == NULL)
			cout << " Error in degree_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

/*
//class for dateofbirth child
class dateofbirth_item : public basic_item {
protected:
	string item_value;
	
public:
	dateofbirth_item() { ; }
	~dateofbirth_item() { ; }

	string getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"dateofbirth_item\" is Empty." << endl;
		}
		else
			cout << "Date of Birth: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert date of birth then hit enter." << endl;
		getline(cin, item_value);
		//cin >> item_value;
		//cin.ignore();
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		int day = (rand() % 30);
		int month = rand() % 12;
		int year = 1950 + rand() % 68;
		item_value = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
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
		dateofbirth_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type dateofbirth_item." << endl;
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
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        dateofbirth_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type dateofbirth_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		dateofbirth_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type height_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if ((getItemVal().compare(typecasted_other_item->getItemVal()) == 0))
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
		dateofbirth_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for dateofbirth_item): " << endl << "Other item is not of type dateofbirth_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		dateofbirth_item* result = new dateofbirth_item;
		if (result == NULL)
			cout << " Error in dateofbirth_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};
*/



//class for current cgs child
class currentcgs_item : public basic_item {
protected:
	int item_value;

public:
	currentcgs_item() { ; }
	~currentcgs_item() { ; }

	int getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"currentcgs_item\" is Empty." << endl;
		}
		else
			cout << "Current CGS Grade: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert current CGS grade then hit enter." << endl;
		//getline(cin, item_value);
		cin >> item_value;
		cin.ignore();
		cout << endl;

		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		item_value = rand() % 22;
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
		currentcgs_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type currentcgs_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal()>typecasted_other_item->getItemVal())
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        currentcgs_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		currentcgs_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type currentcgs_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() == typecasted_other_item->getItemVal())
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
		currentcgs_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for currentcgs_item): " << endl << "Other item is not of type currentcgs_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		currentcgs_item* result = new currentcgs_item;
		if (result == NULL)
			cout << " Error in currentcgs_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

//class for past cgs child
class pastcgs_item : public basic_item {
protected:
	int item_value;

public:
	pastcgs_item() { ; }
	~pastcgs_item() { ; }

	int getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{
		if (isEmpty()) {
			cout << "\"pastcgs_item\" is Empty." << endl;
		}
		else
			cout << "Previous CGS Grade: " << getItemVal() << endl;
	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert previous CGS grade then hit enter." << endl;
		//getline(cin, item_value);
		cin >> item_value;
		cin.ignore();
		cout << endl;
		// item filled
		empty = false;
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		item_value = rand() % 22;
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
		pastcgs_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type pastcgs_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal()>typecasted_other_item->getItemVal())
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
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        pastcgs_item* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type height_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getItemVal() < (typecasted_other_item->getItemVal()) )
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

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		pastcgs_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type currentcgs_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() == typecasted_other_item->getItemVal())
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
		pastcgs_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for pastcgs_item): " << endl << "Other item is not of type pastcgs_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		pastcgs_item* result = new pastcgs_item;
		if (result == NULL)
			cout << " Error in pastcgs_item::allocateItem(): out of memory" << endl;
		return result;
	}

	//virtual void setstringtype(int i) { type = i; }

};

class year_item : public basic_item {
protected:
	int item_value;

public:
	// default constructor and destructor: do nothing
	year_item() { ; }
	~year_item() { ; }

	int getItemVal() { return item_value; }

	virtual void printItemOnScreen()
	{

		if (isEmpty())
			cout << "\"year_item\" is empty." << endl;
		else
			cout << "Year: " << getItemVal() << endl;

	}

	virtual void enterItemFromKeyboard()
	{
		cout << "Insert year then hit enter." << endl;
		//getline(cin, item_value);
		cin >> item_value;
		cin.ignore();
		cout << endl;
		// item filled
		empty = false;
	}

	virtual void generateRandomItem()
	{
		item_value = rand() % 5;
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
		year_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type year_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() > (typecasted_other_item->getItemVal()))
		{
			result = true;
		}
			


		// chek if there are sorting options to apply 
		if (sort_criteria != NULL)
		{
			// if sorting is in descending order the result is reversed 
			if (!(sort_criteria->getAscending()))
				result = !result;
		}

		return result;
	}

	virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		year_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type year_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is smaller than the curren
		if (getItemVal() < (typecasted_other_item->getItemVal())) {
			result = true;
		}
			


		// chek if there are sorting options to apply
		if (sort_criteria != NULL)
		{
			// if sorting is in descending order the result is reversed
			if (!(sort_criteria->getAscending()))
				result = !result;
		}

		return result;
	}

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if (other_item == NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		year_item* typecasted_other_item = typecastItem(other_item, this);

		// check that it worked
		if (typecasted_other_item == NULL)
		{
			cout << "Other item is not of type year_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if (getItemVal() == (typecasted_other_item->getItemVal()))
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
		year_item* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for year_item): " << endl << "Other item is not of type year_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		year_item* result = new year_item;
		if (result == NULL)
			cout << " Error in year_item::allocateItem(): out of memory" << endl;
		return result;
	}
};

class student_record : public basic_item {
protected:
	height_item h_item;
	weight_item w_item;
	firstname_item fn_item;
	surname_item sn_item;
	bloodtype_item bt_item;
	nationality_item n_item;
	studentid_item sid_item;
	email_item e_item;
	degree_item d_item;
	dateofbirth_item dob_item;
	currentcgs_item ccgs_item;
	pastcgs_item pcgs_item;
	year_item y_item;

private:
	virtual height_item* return_height_pointer() { return &h_item; }

	virtual weight_item* return_weight_pointer() { return &w_item; }

	virtual firstname_item* return_firstname_pointer() { return &fn_item; }

	virtual surname_item* return_surname_pointer() { return &sn_item; }

	virtual bloodtype_item* return_bloodtype_pointer() { return &bt_item; }

	virtual nationality_item* return_nationality_pointer() { return &n_item; }

	virtual studentid_item* return_studentid_pointer() { return &sid_item; }

	virtual email_item* return_email_pointer() { return &e_item; }

	virtual degree_item* return_degree_pointer() { return &d_item; }

	virtual dateofbirth_item* return_dob_pointer() { return &dob_item; }

	virtual currentcgs_item* return_currentcgs_pointer() { return &ccgs_item; }

	virtual pastcgs_item* return_previouscgs_pointer() { return &pcgs_item; }

	virtual year_item* return_year_pointer() { return &y_item; }

public:
	student_record() { ; }
	~student_record() { ; }
    
    virtual void writeItemToFile(){
        string path("/Users/tgb19/documents/output.csv");
        std::ofstream outfile;
        outfile.open(path, std::ios_base::app);
		outfile << fn_item.getItemVal() << "," << sn_item.getItemVal() << "," << bt_item.getItemVal() << "," << h_item.getItemVal() << "," << w_item.getItemVal() << "," << n_item.getItemVal() << "," << sid_item.getItemVal() << "," << e_item.getItemVal() << "," << d_item.getItemVal() << "," << dob_item.getItemVal() << "," << ccgs_item.getItemVal() << "," << pcgs_item.getItemVal() << "," << y_item.getItemVal() << "," << endl;
        //outfile << "test.txt";
    }

	virtual void printItemOnScreen()
	{
		//cout << "Print item on screen" << endl;
		h_item.printItemOnScreen();
		w_item.printItemOnScreen();
		fn_item.printItemOnScreen();
		sn_item.printItemOnScreen();
		bt_item.printItemOnScreen();
		n_item.printItemOnScreen();
		sid_item.printItemOnScreen();
		e_item.printItemOnScreen();
		d_item.printItemOnScreen();
		dob_item.printItemOnScreen();
		ccgs_item.printItemOnScreen();
		pcgs_item.printItemOnScreen();
		y_item.printItemOnScreen();
        writeItemToFile();
	}

	virtual void enterItemFromKeyboard()
	{
		//cout << "entering items from keyboard"<<endl;
		h_item.enterItemFromKeyboard();
		w_item.enterItemFromKeyboard();
		fn_item.enterItemFromKeyboard();
		sn_item.enterItemFromKeyboard();
		bt_item.enterItemFromKeyboard();
		n_item.enterItemFromKeyboard();
		sid_item.enterItemFromKeyboard();
		e_item.enterItemFromKeyboard();
		d_item.enterItemFromKeyboard();
		dob_item.enterItemFromKeyboard();
		ccgs_item.enterItemFromKeyboard();
		pcgs_item.enterItemFromKeyboard();
		y_item.enterItemFromKeyboard();
	}

	//function to get random string from the protected
	virtual void generateRandomItem()
	{
		//cout << "Generating Random Number" << endl;
		h_item.generateRandomItem();
		w_item.generateRandomItem();
		fn_item.generateRandomItem();
		sn_item.generateRandomItem();
		bt_item.generateRandomItem();
		n_item.generateRandomItem();
		sid_item.generateRandomItem();
		e_item.generateRandomItem();
		d_item.generateRandomItem();
		dob_item.generateRandomItem();
		ccgs_item.generateRandomItem();
		pcgs_item.generateRandomItem();
		y_item.generateRandomItem();
	}

	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;

		// first typecast the other item to confimr it is the same as this;
		student_record* typecasted_other_item = typecastItem(other_item, this);
		//data_sorting_type =

		switch (sort_criteria->get_data_sort_type())
		{
		case HEIGHT:
			//cout << "Item is height" << endl;
			result = h_item.IsLargerThan(typecasted_other_item->return_height_pointer(), sort_criteria);
			break;
		case WEIGHT:
			//cout << "Item is weight" << endl;
			result = w_item.IsLargerThan(typecasted_other_item->return_weight_pointer(), sort_criteria);
			break;
		case FIRSTNAME:
			//cout << "Item is firstname" << endl;
			result = fn_item.IsLargerThan(typecasted_other_item->return_firstname_pointer(), sort_criteria);
			break;
		case SURNAME:
			//cout << "Item is surname" << endl;
			result = sn_item.IsLargerThan(typecasted_other_item->return_surname_pointer(), sort_criteria);
			break;
		case BLOODTYPE:
			//cout << "Item is bloodtype" << endl;
			result = bt_item.IsLargerThan(typecasted_other_item->return_bloodtype_pointer(), sort_criteria);
			break;
		case NATIONALITY:
			//cout << "Item is nationality" << endl;
			result = n_item.IsLargerThan(typecasted_other_item->return_nationality_pointer(), sort_criteria);
			break;
		case STUDENTID:
			//cout << "Item is student id" << endl;
			result = sid_item.IsLargerThan(typecasted_other_item->return_studentid_pointer(), sort_criteria);
			break;
		case EMAIL:
			//cout << "Item is email address" << endl;
			result = e_item.IsLargerThan(typecasted_other_item->return_email_pointer(), sort_criteria);
			break;
		case DEGREE:
			//cout << "Item is degree programme" << endl;
			result = d_item.IsLargerThan(typecasted_other_item->return_degree_pointer(), sort_criteria);
			break;
		case DOB:
			//cout << "Item is date of birth" << endl;
			result = dob_item.IsLargerThan(typecasted_other_item->return_dob_pointer(), sort_criteria);
			break;
		case CURRENTCGS:
			//cout << "Item is current cgs grade" << endl;
			result = ccgs_item.IsLargerThan(typecasted_other_item->return_currentcgs_pointer(), sort_criteria);
			break;
		case PREVIOUSCGS:
			//cout << "Item is previous cgs grade" << endl;
			result = pcgs_item.IsLargerThan(typecasted_other_item->return_previouscgs_pointer(), sort_criteria);
			break;
		case YEAR:
			//cout << "Item is previous cgs grade" << endl;
			result = y_item.IsLargerThan(typecasted_other_item->return_year_pointer(), sort_criteria);
			break;
		default:
			break;
		}

		return result;
	}
    
    virtual bool IsSmallerThan(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
    {
        bool result = false;
        
        // first typecast the other item to confimr it is the same as this;
        student_record* typecasted_other_item = typecastItem(other_item, this);
        //data_sorting_type =
        
        switch (sort_criteria->get_data_sort_type())
        {
            case HEIGHT:
                //cout << "Item is height" << endl;
                result = h_item.IsSmallerThan(typecasted_other_item->return_height_pointer(), sort_criteria);
                break;
            case WEIGHT:
                //cout << "Item is weight" << endl;
                result = w_item.IsSmallerThan(typecasted_other_item->return_weight_pointer(), sort_criteria);
                break;
            case FIRSTNAME:
                //cout << "Item is firstname" << endl;
                result = fn_item.IsSmallerThan(typecasted_other_item->return_firstname_pointer(), sort_criteria);
                break;
            case SURNAME:
                //cout << "Item is surname" << endl;
                result = sn_item.IsSmallerThan(typecasted_other_item->return_surname_pointer(), sort_criteria);
                break;
            case BLOODTYPE:
                //cout << "Item is bloodtype" << endl;
                result = bt_item.IsSmallerThan(typecasted_other_item->return_bloodtype_pointer(), sort_criteria);
                break;
            case NATIONALITY:
                //cout << "Item is nationality" << endl;
                result = n_item.IsSmallerThan(typecasted_other_item->return_nationality_pointer(), sort_criteria);
                break;
            case STUDENTID:
                //cout << "Item is student id" << endl;
                result = sid_item.IsSmallerThan(typecasted_other_item->return_studentid_pointer(), sort_criteria);
                break;
            case EMAIL:
                //cout << "Item is email address" << endl;
                result = e_item.IsSmallerThan(typecasted_other_item->return_email_pointer(), sort_criteria);
                break;
            case DEGREE:
                //cout << "Item is degree programme" << endl;
                result = d_item.IsSmallerThan(typecasted_other_item->return_degree_pointer(), sort_criteria);
                break;
            case DOB:
                //cout << "Item is date of birth" << endl;
                result = dob_item.IsSmallerThan(typecasted_other_item->return_dob_pointer(), sort_criteria);
                break;
            case CURRENTCGS:
                //cout << "Item is current cgs grade" << endl;
                result = ccgs_item.IsSmallerThan(typecasted_other_item->return_currentcgs_pointer(), sort_criteria);
                break;
            case PREVIOUSCGS:
                //cout << "Item is previous cgs grade" << endl;
                result = pcgs_item.IsSmallerThan(typecasted_other_item->return_previouscgs_pointer(), sort_criteria);
                break;
			case YEAR:
				//cout << "Item is previous cgs grade" << endl;
				result = y_item.IsSmallerThan(typecasted_other_item->return_year_pointer(), sort_criteria);
				break;
            default:
                break;
        }
        
        return result;
    }

	virtual bool IsEqualTo(basic_item* other_item, basic_sort_criteria* sort_criteria = NULL)
	{
		bool result = false;

		// first typecast the other item to confimr it is the same as this;
		student_record* typecasted_other_item = typecastItem(other_item, this);
		//data_sorting_type =

		switch (sort_criteria->get_data_sort_type())
		{
		case HEIGHT:
			//cout << "Item is height" << endl;
			result = h_item.IsEqualTo(typecasted_other_item->return_height_pointer(), sort_criteria);
			break;
		case WEIGHT:
			//cout << "Item is weight" << endl;
			result = w_item.IsEqualTo(typecasted_other_item->return_weight_pointer(), sort_criteria);
			break;
		case FIRSTNAME:
			//cout << "Item is firstname" << endl;
			result = fn_item.IsEqualTo(typecasted_other_item->return_firstname_pointer(), sort_criteria);
			break;
		case SURNAME:
			//cout << "Item is surname" << endl;
			result = sn_item.IsEqualTo(typecasted_other_item->return_surname_pointer(), sort_criteria);
			break;
		case BLOODTYPE:
			//cout << "Item is bloodtype" << endl;
			result = bt_item.IsEqualTo(typecasted_other_item->return_bloodtype_pointer(), sort_criteria);
			break;
		case NATIONALITY:
			//cout << "Item is nationality" << endl;
			result = n_item.IsEqualTo(typecasted_other_item->return_nationality_pointer(), sort_criteria);
			break;
		case STUDENTID:
			//cout << "Item is student id" << endl;
			result = sid_item.IsEqualTo(typecasted_other_item->return_studentid_pointer(), sort_criteria);
			break;
		case EMAIL:
			//cout << "Item is email address" << endl;
			result = e_item.IsEqualTo(typecasted_other_item->return_email_pointer(), sort_criteria);
			break;
		case DEGREE:
			//cout << "Item is degree programme" << endl;
			result = d_item.IsEqualTo(typecasted_other_item->return_degree_pointer(), sort_criteria);
			break;
		case DOB:
			//cout << "Item is date of birth" << endl;
			result = dob_item.IsEqualTo(typecasted_other_item->return_dob_pointer(), sort_criteria);
			break;
		case CURRENTCGS:
			//cout << "Item is current cgs grade" << endl;
			result = ccgs_item.IsEqualTo(typecasted_other_item->return_currentcgs_pointer(), sort_criteria);
			break;
		case PREVIOUSCGS:
			//cout << "Item is previous cgs grade" << endl;
			result = pcgs_item.IsEqualTo(typecasted_other_item->return_previouscgs_pointer(), sort_criteria);
			break;
		case YEAR:
			//cout << "Item is previous cgs grade" << endl;
			result = y_item.IsEqualTo(typecasted_other_item->return_year_pointer(), sort_criteria);
			break;
		default:
			break;
		}

		return result;
	}

	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		student_record* typecasted_item_ptr = typecastItem(item_ptr, this);

		// check that it worked
		if (typecasted_item_ptr == NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for student_record_item): " << endl << "Other item is not of type student_record_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}

	virtual basic_item* allocateItem()
	{
		student_record* result = new student_record;
		if (result == NULL)
			cout << " Error in string_item::allocateItem(): out of memory" << endl;

		return result;
	}

	virtual void AssignSpeificItem(basic_sort_criteria* sort_criteria = NULL)
	{
		switch (sort_criteria->get_data_sort_type())
		{
		case HEIGHT:
			//cout << "Item is height" << endl;
			h_item.enterItemFromKeyboard();
			break;
		case WEIGHT:
			//cout << "Item is weight" << endl;
			w_item.enterItemFromKeyboard();
			break;
		case FIRSTNAME:
			//cout << "Item is firstname" << endl;
			fn_item.enterItemFromKeyboard();
			break;
		case SURNAME:
			//cout << "Item is surname" << endl;
			sn_item.enterItemFromKeyboard();
			break;
		case BLOODTYPE:
			//cout << "Item is bloodtype" << endl;
			bt_item.enterItemFromKeyboard();
			break;
		case NATIONALITY:
			//cout << "Item is nationality" << endl;
			n_item.enterItemFromKeyboard();
			break;
		case STUDENTID:
			//cout << "Item is student id" << endl;
			sid_item.enterItemFromKeyboard();
			break;
		case EMAIL:
			//cout << "Item is email address" << endl;
			e_item.enterItemFromKeyboard();
			break;
		case DEGREE:
			//cout << "Item is degree programme" << endl;
			d_item.enterItemFromKeyboard();
			break;
		case DOB:
			//cout << "Item is date of birth" << endl;
			dob_item.enterItemFromKeyboard();
			break;
		case CURRENTCGS:
			//cout << "Item is current cgs grade" << endl;
			ccgs_item.enterItemFromKeyboard();
			break;
		case PREVIOUSCGS:
			//cout << "Item is previous cgs grade" << endl;
			pcgs_item.enterItemFromKeyboard();
			break;
		case YEAR:
			//cout << "Item is previous cgs grade" << endl;
			y_item.enterItemFromKeyboard(); 
			break;
		default:
			break;
		}

	}

};
#endif