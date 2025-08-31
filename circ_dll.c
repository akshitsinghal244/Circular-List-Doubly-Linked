#include "circ_dll.h"


static NODE *head = NULL;
static NODE *tail = NULL;

int ListSize ()
{
	int count = 0;
	NODE *p_node = head;

	if (p_node != NULL)
	{
		do
		{
			count ++;
			p_node = p_node -> next;
		} while (p_node != head);
	}

	return count;
}

// Creates a node; allocates memory, gets the data value, etc
NODE *CreateNode ()
{
 	NODE *p_node;
	if ((p_node = (NODE *) malloc (sizeof (NODE))) == NULL)
	{
		printf ("Unable to create node: memory not available\n");
		exit (0);
	}
	p_node -> next = NULL;
	p_node -> prev = NULL;
	printf ("Key in the value:");
	scanf ("%d", &p_node->data);
	return p_node;
}

void ModifyList ()
{
	int pos, val;
	NODE *p_temp = head, *p_prev;

	printf ("Number of the node you want to modify:");
	scanf ("%d", &pos);
	printf ("The new value:");
	scanf ("%d", &val);

	for (int i = 0; i < (pos - 1); i ++)
		p_temp = p_temp -> next;
	p_temp->data = val;
}


void CreateList ()
{
	int num, val;
	NODE *p_node, *p_temp;

	printf ("How many nodes do you want to create?:");
	scanf ("%d", &num);

	for (int i = 0; i < num; i ++)
	{
		p_node = CreateNode ();

		if (head == NULL)
			head = tail = p_node;
		else
		{
			tail -> next = p_node;
			p_node -> prev = tail;
			tail = p_node;
		}

	}
	tail -> next = head;
	head -> prev = tail;
}


void PrintList ()
{
	NODE *p_node = head;

	if (p_node != NULL)
	{
		do
		{
			printf ("Val is %d\n", p_node->data);
			p_node = p_node -> next;
		} while (p_node != head);
	}
}

void ReversePrint ()
{
	NODE *p_node = tail;

	// Check whether tail is NULL
	if (tail != NULL)
	{
		do
		{
			printf ("Val is %d\n", p_node->data);
			p_node = p_node -> prev;
		} while (p_node != tail);
	}

}


void InsertAtBeginning ()
{
	NODE *p_node;

	p_node = CreateNode ();
	if (head == NULL)	// An empty list
	{
		head = tail = p_node;
		head -> next = tail;
		head -> prev = tail;
		tail -> next = head;
		tail -> prev = head;
	}
	else
	{
		p_node -> next = head;
		head -> prev = p_node;
		head = p_node;
		head -> prev = tail;
		tail -> next = head;
	}

}

void InsertAtEnd ()
{
	NODE *p_node, *p_temp;

	p_node = CreateNode ();

	tail -> next = p_node;
	p_node -> prev = tail;
	tail = p_node;
	tail -> next = head;
	head -> prev = tail;
}

void InsertAnywhere ()
{
	int pos;
	int listLen;
	NODE *p_temp = head, *p_prev, *p_node;

	listLen = ListSize ();
	printf ("Position at which to insert:");
	scanf ("%d", &pos);
	if (pos < 1 || pos > listLen)
	{
		printf ("Invalid position\n");
		exit (0);
	}
	if (pos == 1)
		InsertAtBeginning ();
	else if (pos == listLen)
		InsertAtEnd ();
	else
	{
		for (int i = 0; p_temp != NULL; p_prev = p_temp,
						p_temp = p_temp->next, i++)
		{
			if (i == (pos - 1))
			{
				p_node = CreateNode ();
				p_prev -> next = p_node;
				p_node -> prev = p_prev;
				p_node -> next = p_temp;
				p_temp -> prev = p_node;
				break;
			}
		}
	}
}


bool SearchList ()
{
	NODE *p_temp = head;
	int value;
	bool found = false;

	printf ("What are you looking for?:");
	scanf ("%d", &value);

	if (p_temp != NULL)
	{
		do
		{
			if (p_temp->data == value)
			{
				found = true;
				break;
			}
			p_temp = p_temp -> next;
		} while (p_temp != head);
	}

	return found;
}

void DeleteFirstNode ()
{
	NODE *p_temp;

	if (head != NULL)
	{
		if (head -> next == head)
		{
			free (head);
			head = tail = NULL;
		}
		else
		{
			p_temp = head;
			head = head -> next;
			head -> prev = tail;
			tail -> next = head;
			free (p_temp);
		}
	}
	else
		printf ("There is nothing to delete\n");
}

void DeleteLastNode()
{
	NODE *p_temp, *p_prev;
	if (head != NULL)
	{
		if (head -> next == head)	// only one node in the list
		{
			free (head);
			head = tail = NULL;
		}
		else
		{
			p_temp = tail;
			p_prev = tail -> prev;
			p_prev -> next = head;
			head -> prev = p_prev;
			tail = p_prev;
			free (p_temp);
		}
	}
	else
		printf ("There is nothing to delete\n");
}

void DeleteAnyNode ()
{
	int nodeNum, i;
	int lsize = ListSize ();
	NODE *p_cur, *p_prev, *p_next;

	printf ("Enter the number of the node you want to delete:");
	scanf ("%d", &nodeNum);

	if (nodeNum < 0 || nodeNum > lsize)
	{
		printf ("Invalid node number\n");
		exit (0);
	}

	if (nodeNum == 1)	// Delete first node
	{
		DeleteFirstNode ();
		return;
	}

	if (nodeNum == lsize)	// Last node to be deleted
	{
		DeleteLastNode ();
		return;
	}

	p_cur = head;
	for (i = 0; i < (nodeNum - 1); i ++, p_cur = p_cur -> next)
		;

	p_prev = p_cur -> prev;
	p_next = p_cur -> next;
	p_prev -> next = p_next;
	p_next -> prev = p_prev;
	free (p_cur);
}

bool IsListEmpty ()
{
	bool ret_val = false;
	if (head == NULL)
		ret_val = true;
	return ret_val;
}

void NavigateList ()
{
	char sub_opt;
	NODE *p_node = head;
	bool go_on = true;

	while (1)
	{
		printf ("Select: P - Previous N - Next F - First L - Last: R - Return:");
		scanf (" %c", &sub_opt);
		sub_opt = toupper (sub_opt);
		switch (sub_opt)
		{
			case 'F':
				p_node = head;
			break;

			case 'L':
				p_node = tail;
			break;

			case 'P':
				p_node = p_node -> prev;
			break;

			case 'N':
				p_node = p_node -> next;
			break;

			case 'R':
				go_on = false;
			break;

			default:
				printf ("Invalid option\n");
		}
		if (go_on == false)
			break;
		DisplayNode (p_node);
	}
}

void DisplayNode (NODE *p_node)
{
	if (p_node != NULL)
		printf ("Data is %d\n", p_node->data);
}

// Free memory alloted to all the nodes in the list
void FreeList()
{
    	NODE *current = head;
    	NODE *nextNode;
	if (head != NULL)
	{
    		while (current -> next != head)
    		{
			nextNode = current->next;
        		free(current);
        		current = nextNode;
		}
		free (current);
    	}

    	head = tail = NULL;
}