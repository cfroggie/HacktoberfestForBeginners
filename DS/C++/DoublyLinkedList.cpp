// Carly Fohn
// DoublyLinkedList.cpp

#include "DoublyLinkedList.h"
#include <stdexcept>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
  header.next = &trailer; trailer.prev = &header;
  
  DListNode* head = dll.getFirst();
  const DListNode* tail = dll.getAfterLast();
  DListNode* node = head;
  
  while(node != tail){
	insertLast(node->obj);
	node = node->next;
  }
}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  // Delete the whole list
  DListNode* head = dll.getFirst();
  const DListNode* tail = dll.getAfterLast();
  DListNode* node = head;
  
  while(node != tail){
	insertLast(node->obj);
	node = node->next;
  }
  return *this;
}

// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj)
{ 
  DListNode *newNode = new DListNode(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
  DListNode *newNode = new DListNode(newobj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
  if (isEmpty()){
	  throw EmptyDLinkedListException("Empty Doubly Linked List");
  }
  
  DListNode *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  int obj = node->obj;
  
  delete node;
  return obj;
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
  if (isEmpty()){
	  throw EmptyDLinkedListException("Empty Doubly Linked List");
  }
  
  DListNode *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  int obj = node->obj;
  
  delete node;
  return obj;
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
  DListNode *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// return the first object
int DoublyLinkedList::first() const
{ 
  if (isEmpty()){
	  throw EmptyDLinkedListException("Empty Doubly Linked List");
  }
  
  return header.next->obj;
}

// return the last object
int DoublyLinkedList::last() const
{
  if (isEmpty()){
	  throw EmptyDLinkedListException("Empty Doubly Linked List");
  }
  
  return trailer.prev->obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
	if(p.next == &trailer){
        insertLast(newobj);
        return;
    }
    if(&p == &trailer){
        throw EmptyDLinkedListException("Error: cannot insert past tail");
    }

    DListNode *newNode = new DListNode(newobj, &p, p.next);
    p.next->prev = newNode;
    p.next = newNode;
}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
    if(p.prev == &header){
		insertFirst(newobj);
        return;
    }
    if(&p == &header){
        throw EmptyDLinkedListException("Error: cannot insert before head");
    }

    DListNode *newNode = new DListNode(newobj, p.prev, &p);
    p.prev->next = newNode;
    p.prev = newNode;
}

// remove the node after the node p
void DoublyLinkedList::removeAfter(DListNode &p)
{
    if(isEmpty()){
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    }
    if(&p == &trailer){
        throw EmptyDLinkedListException("Error: cannot remove past tail");
    }
    if(p.next == &trailer){
        throw EmptyDLinkedListException("Error: cannot remove tail");
    }

    DListNode *curr = new DListNode();
    curr = &p;
    curr = curr->next;
    p.next = curr->next;
    curr->next->prev = &p;
    
	delete curr;
    curr = NULL;
}

// remove the node before the node p
void DoublyLinkedList::removeBefore(DListNode &p)
{
    if(isEmpty()){
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    }
    if(&p == &header){
        throw EmptyDLinkedListException("Error: cannot remove before head");
    }
    if(p.prev == &header){
        throw EmptyDLinkedListException("Error: cannot remove head");
    }

    DListNode *curr = new DListNode();
    curr = &p;
    curr = curr->prev;
    p.prev = curr->prev;
    curr->prev->next = &p;
    
	delete curr;
    curr = NULL;
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
    int count = 0;
    DListNode *curr = dll.getFirst();
    while(curr != dll.getAfterLast()){
        count++;
        curr = curr->next;
    }
    return count;
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
    DListNode *current = dll.getFirst();
    while(current->next != NULL){
        out << current->obj << " ";
        current = current->next;
    }
	return out;
}
