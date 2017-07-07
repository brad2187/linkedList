// BRADLEY HALL
// 10/20/16
// ASSIGNMENT_5 IMPEMENTATION OF SEQUENCE


#include "sequence.h"
#include "node.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#define _SCL_SECURE_NO_WARNINGS

using namespace std;

namespace NSU_DATA_STRUCTURES
{

	// sequence constructor - set private members to null
	sequence::sequence()
	{
		head_ptr = NULL;
		tail_ptr = NULL;
		cursor = NULL;
		precursor = NULL;
		many_nodes = 0;
	}
	// sequence copy constructor - copys one sequence to another. 
	sequence::sequence(const sequence& source)
	{


		if (this == &source)
		{
			return;
		}
		else
		{
			list_copy(source.head_ptr, head_ptr, tail_ptr);
			if (source.precursor == NULL)
			{
				if (source.cursor == NULL)
				{
					cursor = NULL;
					precursor = NULL;
				}
				else
				{
					cursor = head_ptr;
					precursor = NULL;
				}
			}
			else
			{
				node *temp = head_ptr;
				node *sourcePtr = source.head_ptr;
				while (sourcePtr != source.precursor)
				{
					sourcePtr = sourcePtr->link();
					temp = temp->link();
				}
				cursor = temp->link();
				precursor = temp;
			}
		}
		many_nodes = source.many_nodes;

	}
	// sequence deconstructor
	sequence::~sequence()
	{
		list_clear(head_ptr);
		many_nodes = 0;
	}
	// start method - moves the cursor to the beginning of the list
	void sequence::start()
	{
		if (head_ptr == NULL && tail_ptr == NULL)
		{
			return;
		}

		cursor = head_ptr;
		precursor = NULL;
	}
	// advance method - moves cursor forward and precursor gets cursor
	void sequence::advance()
	{
		precursor = cursor;
		cursor = cursor->link();
	}
	// insert method - inserts a new link into list with the specified data.
	void sequence::insert(const value_type& entry)
	{

		if (precursor == NULL || !is_item()) 
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;

			if (many_nodes == 0) 
			{
				tail_ptr = head_ptr;
			}
		}

		else 
		{
			list_insert(precursor, entry);
			cursor = precursor->link();
		}

		many_nodes++;
	}
	// attach method - attaches a new link to list with the specified data
	void sequence::attach(const value_type& entry)
	{
		if (is_item()) 
		{
			if (cursor == tail_ptr) 
			{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
				tail_ptr = tail_ptr->link();
			}

			else 
			{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
			}
		}
		if (!is_item()) 
		{
			if ((head_ptr == NULL) && (tail_ptr == NULL)) {
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = head_ptr;
			}

			else 
			{
				precursor = list_locate(head_ptr, list_length(head_ptr));
				list_insert(precursor, entry);
				cursor = precursor->link();
				tail_ptr = tail_ptr->link();
			}
		}
		many_nodes++;
	}
	// remove_current method - removes the currrent item in the linked list
	void sequence::remove_current()
	{
		node *aNode;
		aNode = NULL;

		if (cursor == head_ptr) 
		{
			if (many_nodes > 1) 
			{
				list_head_remove(head_ptr);
				cursor = head_ptr;
				precursor = NULL;
			}
			else 
			{
				list_head_remove(head_ptr);
				cursor = precursor = head_ptr = tail_ptr = NULL;
			}
		}
		else 
		{
			cursor = cursor->link();
			list_remove(precursor);
		}
		many_nodes--;
	}
	// overloaded assignment operator 
	void sequence::operator=(const sequence& source)
	{
		if (this == &source)
		{
			return;
		}
		
		else
		{
			list_clear(head_ptr);
			precursor = cursor = head_ptr = tail_ptr = NULL;
			many_nodes = 0;
			list_copy(source.head_ptr, head_ptr, tail_ptr);
			if (source.precursor == NULL)
			{
				if (source.cursor == NULL)
				{
					cursor = NULL;
					precursor = NULL;
				}
				else
				{
					cursor = head_ptr;
					precursor = NULL;
				}
			}
			else
			{
				node *temp = head_ptr;
				node *sourcePtr = source.head_ptr;
				while (sourcePtr != source.precursor)
				{
					sourcePtr = sourcePtr->link();
					temp = temp->link();
				}
				cursor = temp->link();
				precursor = temp;
			}
		}
		many_nodes = source.many_nodes;
	}
	// current method - returns the data of the current item
	sequence::value_type sequence::current() const
	{
		return cursor->data();
	}


}
