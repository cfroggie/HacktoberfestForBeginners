// Carly Fohn
// TemplateDoublyLinkedList.h

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T> class DoublyLinkedList; // class declaration

// list node
template <class T> struct DListNode {
  T obj;
  DListNode<T> *prev, *next;
  DListNode(T e=T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
template<class T> class DoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T{}), trailer(T{}) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  
  DoublyLinkedList(const DoublyLinkedList<T>& dll) // copy constructor
  {
	  // Initialize the list
	  header.next = &trailer; trailer.prev = &header;
	  
	  DListNode<T>* head = dll.getFirst();
	  const DListNode<T>* tail = dll.getAfterLast();
	  DListNode<T>* node = head;
	  
	  while(node != tail){
		insertLast(node->obj);
		node = node->next;
	  }
  }
  
  ~DoublyLinkedList() // destructor
  {
	  DListNode<T> *prev_node, *node = header.next;
	  while (node != &trailer) {
		prev_node = node;
		node = node->next;
		delete prev_node;
	  }
	  header.next = &trailer;
	  trailer.prev = &header;
  }
  
  DoublyLinkedList& operator=(const DoublyLinkedList<T>& dll) // assignment operator
  {
	  // Delete the whole list
	  DListNode<T>* head = dll.getFirst();
	  const DListNode<T>* tail = dll.getAfterLast();
	  DListNode<T>* node = head;
	  
	  while(node != tail){
		insertLast(node->obj);
		node = node->next;
	  }
	  return *this;
  }
  
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  
  T first() const // return the first object
  {
	  if (isEmpty()){
		  throw EmptyDLinkedListException("Empty Doubly Linked List");
	  }
	  
	  return header.next->obj;
  }
  
  T last() const // return the last object
  {
	  if (isEmpty()){
		  throw EmptyDLinkedListException("Empty Doubly Linked List");
	  }
	  
	  return trailer.prev->obj;
  }
  
  void insertFirst(T newobj) // insert to the first of the list
  {
	  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
	  header.next->prev = newNode;
	  header.next = newNode;
  }
  
  T removeFirst() // remove the first node
  {
	  if (isEmpty()){
		  throw EmptyDLinkedListException("Empty Doubly Linked List");
	  }
	  
	  DListNode<T> *node = header.next;
	  node->next->prev = &header;
	  header.next = node->next;
	  T obj = node->obj;
	  
	  delete node;
	  return obj;
  }
  
  void insertLast(T newobj) // insert to the last of the list
  {
	  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer);
	  trailer.prev->next = newNode;
	  trailer.prev = newNode; 
  }
  
  T removeLast() // remove the last node
  {
	  if (isEmpty()){
		  throw EmptyDLinkedListException("Empty Doubly Linked List");
	  }
	  
	  DListNode<T> *node = trailer.prev;
	  node->prev->next = &trailer;
	  trailer.prev = node->prev;
	  T obj = node->obj;
	  
	  delete node;
	  return obj;
  }
  
  void insertAfter(DListNode<T> &p, T newobj)
  {
	if(p.next == &trailer){
        insertLast(newobj);
        return;
    }
    if(&p == &trailer){
        throw EmptyDLinkedListException("Error: cannot insert past tail");
    }

    DListNode<T> *newNode = new DListNode<T>(newobj, &p, p.next);
    p.next->prev = newNode;
    p.next = newNode;
  }
  
  void insertBefore(DListNode<T> &p, T newobj)
  {
    if(p.prev == &header){
		insertFirst(newobj);
        return;
    }
    if(&p == &header){
        throw EmptyDLinkedListException("Error: cannot insert before head");
    }

    DListNode<T> *newNode = new DListNode<T>(newobj, p.prev, &p);
    p.prev->next = newNode;
    p.prev = newNode;
  }
  
  void removeAfter(DListNode<T> &p)
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

    DListNode<T> *curr = new DListNode<T>();//get rid of stuff after ?
    curr = &p;
    curr = curr->next;
    p.next = curr->next;
    curr->next->prev = &p;
    
	delete curr;
    curr = NULL;
  }
  
  void removeBefore(DListNode<T> &p)
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

    DListNode<T> *curr = new DListNode<T>();//get rid of stuff after ?
    curr = &p;
    curr = curr->prev;
    p.prev = curr->prev;
    curr->prev->next = &p;
    
	delete curr;
    curr = NULL;
  }
  
  // extend range_error from <stdexcept>
  struct EmptyDLinkedListException : std::range_error {
	explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
  };
  
};

// output operator
template <class T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
    DListNode<T> *current = dll.getFirst();
    while(current->next != NULL){
        out << current->obj << " ";
        current = current->next;
    }
	return out;
}

// return the list length
template <class T> int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
    int count = 0;
    DListNode<T> *curr = dll.getFirst();
    while(curr != dll.getAfterLast()){
        count++;
        curr = curr->next;
    }
    return count;
}