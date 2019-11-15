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
#include "node.cpp"

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
		if(is_item()) {
			precursor = cursor;

			if (cursor == tail_ptr) {
				cursor = NULL;
			} else {
				cursor = cursor->link();
			}
		}
		

	}
	//Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. 
	//Otherwise, the new current item is the item immediately after the original current item.

	void sequence::insert(const value_type& entry) {
		
		if (cursor == NULL || precursor == NULL) {
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			//not sure if below is needed but leaving it is safe
			precursor = NULL;
			tail_ptr = head_ptr;
		} else {
			list_insert(precursor, entry);
			cursor = precursor->link();
			tail_ptr = list_locate(head_ptr, many_nodes);
		}

		many_nodes++;

	}
	//Postcondition: A new copy of entry has been inserted in the sequence before the current item. 
	//If there was no current item, then the new entry has been inserted at the front of the sequence. 
	//In either case, the newly inserted item is now the current item of the sequence.


	void sequence::attach(const value_type& entry) {
		if (cursor == NULL || precursor == NULL) {
			list_head_insert(head_ptr, entry);
			tail_ptr = head_ptr;
			cursor = head_ptr;
			//not sure if below is needed but leaving it is safe
			precursor = NULL;
			return;
		} else {
			list_insert(cursor, entry);
			precursor = cursor;
			cursor = cursor->link();
			tail_ptr = list_locate(head_ptr, many_nodes);
		}

		many_nodes++;
	}
//Postcondition: A new copy of entry has been inserted in the sequence after the current item. If there was no current item, then the new entry has
//been attached to the end of the sequence. In either case, the newly inserted item is now the current item of the sequence.

	void sequence::remove_current() {
		assert(is_item());
		if (cursor == head_ptr) {
			list_head_remove(head_ptr);
			cursor = NULL;
		} else {
			list_remove(precursor);
			precursor = cursor;
			cursor = cursor->link();
		}

		many_nodes--;
		tail_ptr = list_locate(head_ptr, many_nodes);
	}
	//Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.

	void sequence::operator =(const sequence& source) {
		if (this == &source) {
			return;
		}

		list_clear(head_ptr);
		init();
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		//set cursors
		cursor = list_search(head_ptr, source.cursor->data());
		precursor = list_search(head_ptr, source.precursor->data());
		//Initializiing many_nodes (or our counter) to 0
		many_nodes = source.many_nodes;
	}

	sequence::size_type sequence::size() const {
		return many_nodes;
	}
	//Postcondition: The return value is the number of items in the sequence.

	bool sequence::is_item() const {
		if (cursor != NULL) {
			return true;
		}

		return false;
	}
	//Postcondition: A true return value indicates that there is a valid "current" item that may be retrieved by activating the current member function. 
	//A false return value indicates that there is no valid current item.

	sequence::value_type sequence::current() const {
		assert(is_item());
		return cursor->data();
	}
	//Postcondition: The item returned is the current item in the sequence.

}
