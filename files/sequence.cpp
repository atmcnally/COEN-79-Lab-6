//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
	/*1. If the source sequence has no current item, then simply copy the source’s
	linked list with list_copy.Then set both precursor and cursor to the
	null pointer.

	2. If the current item of the source sequence is its first item, then copy the
	source’s linked list with list_copy.Then set precursor to null, and set
	cursor to point to the head node of the newly created linked list.
		
	3. If the current item of the source sequence is after its first item, then copy
	the source’s linked list in two pieces using list_piece from Self - Test
	Exercise 24 on page 258. The first piece that you copy goes from the head
	pointer to the precursor; the second piece goes from the cursor to the tail
	pointer.Put these two pieces together by making the link field of the precursor
	node point to the cursor node.The reason for copying in two separate
	pieces is to easily set the precursor and cursor. */


	sequence::~sequence() {
		//delete something
		list_clear(head_ptr);
	}

	void sequence::start() {
		if (many_nodes > 0) {
			cursor = head_ptr;
			precursor = NULL;
		}
	}
	//Postcondition: The precursor and cursor are adjusted such that the first item in the sequence becomes the current item
	//(but if the sequence is empty, then there is no current item).

	void sequence::end() {
		cursor = list_locate(head_ptr, many_nodes);
		precursor = list_locate(head_ptr, many_nodes - 1);
	}
	//Postcondition: The precursor and cursor are adjusted such that the last item in the sequence becomes the current item 
	//(but if the sequence is empty, then there is no current item).

	void sequence::advance() {
		assert(is_item());
		cursor = cursor->link();
		precursor = precursor->link();
	}
	//Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. 
	//Otherwise, the new current item is the item immediately after the original current item.

	void sequence::insert(const value_type& entry) {

	}
	//Postcondition: A new copy of entry has been inserted in the sequence before the current item. 
	//If there was no current item, then the new entry has been inserted at the front of the sequence. 
	//In either case, the newly inserted item is now the current item of the sequence.


	void sequence::attach(const value_type& entry) {

	}
//Postcondition: A new copy of entry has been inserted in the sequence after the current item. If there was no current item, then the new entry has
//been attached to the end of the sequence. In either case, the newly inserted item is now the current item of the sequence.

	void sequence::remove_current() {
		assert(is_item());
	}
	//Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.

	void sequence::operator =(const sequence& source) {

	}

	sequence::size_type sequence::() const {
		return many_nodes;
	}
//Postcondition: The return value is the number of items in the sequence.

	bool sequence::is_item() const {

	}
//     Postcondition: A true return value indicates that there is a valid "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that there is no valid current item.

	sequence::value_type sequence::current() const {
		assert(is_item());
		return *cursor;
	}

	//     Postcondition: The item returned is the current item in the sequence.


}
