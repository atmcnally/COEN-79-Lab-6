// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {

		if (start_ptr == NULL) {
			head_ptr = NULL;
			tail_ptr = NULL;
			return;
		} else {
			list_head_insert(head_ptr, start_ptr->data());
			tail_ptr = head_ptr;

			if(start_ptr == end_ptr) {
				return;
			}

			// Copy the rest of the nodes one at a time, adding at the tail of new list.
			start_ptr = start_ptr->link();
			while (start_ptr != end_ptr && start_ptr != NULL) {
				list_insert(tail_ptr, start_ptr->data());
				tail_ptr = tail_ptr->link();
				start_ptr = start_ptr->link();
			}
		}

	}
	//Precondition: start_ptr and end_ptr are pointers to nodes on the same linked list, with the start_ptr node at or before the end_ptr node
	//Postcondition: head_ptr and tail_ptr are the head and tail pointers for a new list that contains the items from start_ptr up to but not including end_ptr.
	//The end_ptr may also be NULL, in which case the new list contains elements from start_ptr to the end of the list.

	size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		int count = 0;
		node* tmp_ptr = head_ptr;

		while (tmp_ptr != NULL) {
			if (tmp_ptr->data() == target) {
				count++;
			}
			tmp_ptr = tmp_ptr->link();
		}

		return count;
	}
	//Precondition: head_ptr is the head pointer of a linked list.
	//Postcondition: The return value is the count of the number of times target appears as the data portion of a node on the linked list.
	//The linked list itself is unchanged.

	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		assert(position > 0 && position <= list_length(head_ptr) + 1);
		if(position == 1) {
			list_head_insert(head_ptr, entry);
		} else {
			list_insert(list_locate(head_ptr, position - 1), entry);
		}
		
	}

	//Postcondition: A new node has been added to the linked list with entry as the data. The new node occurs at the specified position in the list.
	//(The head node is position 1, the next node is position 2, and so on.)
	//Any nodes that used to be after this specified position have been shifted to make room for the one new node.

	node::value_type list_remove_at(node*& head_ptr, size_t position) {
		assert(position > 0 && position <= list_length(head_ptr));
		node::value_type val = list_locate(head_ptr, position)->data();

		if(position == 1) {
			list_head_remove(head_ptr);
		} else {
			list_remove(list_locate(head_ptr, position - 1));
		}

		return val;
	}
	//Postcondition: The node at the specified position has been removed from the linked list
	//and the function has returned a copy of the data from the removed node.
	//(The head node is position 1, the next node is position 2, and so on.)

	node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		//use piece in this
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
		node *start_ptr;
		node *end_ptr;
		list_piece(list_locate(head_ptr, start), list_locate(head_ptr, finish)->link(), start_ptr, end_ptr);

		return start_ptr;
	}
	//Postcondition: The value returned is the head pointer for a new list that contains copies of the items from
	//the start position to the finish position in the list that head_ptr points to.
	//(The head node is position 1, the next node is position 2, and so on.)
	//The list pointed to by head_ptr is unchanged.

	void list_print(const node* head_ptr) {
		//use <<
		while(head_ptr->link() != NULL) {
			cout << head_ptr->data() << ", ";
			head_ptr = head_ptr->link();
		}

		cout << head_ptr->data() << endl;
	}
	//Postcondition: The value_type of all the nodes in the linked list are printed

	void list_remove_dups(node* head_ptr) {

		node* ptr;
		node* del;

		while (head_ptr != NULL && head_ptr->link() != NULL) {
			ptr = head_ptr;

				while (ptr->link() != NULL)
				{
					if (head_ptr->data() == ptr->link()->data()) {
						del = ptr->link();
						ptr->set_link(ptr->link()->link());
						delete(del);
					} else {
						ptr = ptr->link();
					}
				}
				head_ptr = head_ptr->link();
		}

	}
	//Postcondition: All the duplicates are removed from the linked list
	//Example: If the list contains 1,1,1,2, after running this function the list contains 1,2

	node* list_detect_loop(node* head_ptr) {

		node *slow_p = head_ptr;
		node *fast_p = head_ptr;

		while (slow_p && fast_p && fast_p->link()) {
			slow_p = slow_p->link();
			fast_p = fast_p->link()->link();
			if (slow_p == fast_p) {
				return slow_p;
			}
		}
		
		return NULL;
	}
	//Postcondition: If there is a loop in the linked list, the returned value is a pointer to the start of the loop.
	//The returned value is NULL if there is no loop in the list

}
