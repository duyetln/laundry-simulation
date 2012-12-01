#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>


template <typename Element> 
//Element type must implement <, >, ==, <=, >= and = operators and copy constructor
//If A < B, B is considered to have higher priority
class PriorityQueue
{
  public:
    //more fun with the Big 3 and doubly linked list
    PriorityQueue();
    PriorityQueue(const PriorityQueue<Element>& queue);
    ~PriorityQueue();
    
    PriorityQueue<Element>& operator=(const PriorityQueue<Element>& queue);
    
    void enqueue(const Element& element);
    const Element* getLowest() const;
    const Element* getHighest() const;
    void dequeueLowest();
    void dequeueHighest();
    void emptyQueue();
    
    unsigned int size() const;
    

  private:
    //doubly linked list
    struct Node
    {
      Node(const Element& value) : value(value) {}
      Element value;
      Node* previous;
      Node* next;
    };
    
    Node* highestElement; //highest element is at the front of the queue
    Node* lowestElement; //lowest element is at the end of the queue
    unsigned int count;
    
    void copyQueue(const Node* srcHead, Node*& destHead, Node*& destEnd); //
    void deleteQueue(Node*& head); //release memory and set "head" to NULL
};


template <typename Element>
void PriorityQueue<Element>::copyQueue(const Node* srcHead, Node*& destHead, Node*& destEnd)
{
  destHead = NULL;
  destEnd = NULL;
  
  if (srcHead != NULL)
  {
    const Node* src;
          Node* dest;
          Node* trail;
    
    src = srcHead;
    dest = new Node(src->value);
    dest->previous = NULL;
    dest->next = NULL;
    
    destHead = dest;
    destEnd = dest;
        
    while(src->next != NULL)
    {
      src = src->next;
      trail = dest;

      dest = new Node(src->value);
      dest->previous = NULL;
      dest->next = NULL;

      trail->next = dest;
      dest->previous = trail;
      destEnd = dest;
    }
  }
}


template <typename Element>
void PriorityQueue<Element>::deleteQueue(Node*& head)
{
  if (head != NULL)
  {
    Node* trail;
    do
    {
      trail = head;
      head = head->next;
      delete trail;      
    }while(head != NULL);
  }
  head = NULL;
}

template <typename Element>
PriorityQueue<Element>::PriorityQueue()
{
  highestElement = NULL;
  lowestElement = NULL;
  count = 0;
}

template <typename Element>
PriorityQueue<Element>::PriorityQueue(const PriorityQueue<Element>& queue)
{
  highestElement = NULL;
  lowestElement = NULL;
  copyQueue(queue.highestElement, highestElement, lowestElement);
  count = queue.count;
}

template <typename Element>
PriorityQueue<Element>::~PriorityQueue()
{
  deleteQueue(highestElement);
  highestElement = NULL;
  lowestElement = NULL;
  count = 0;
}
    
template <typename Element>
PriorityQueue<Element>& PriorityQueue<Element>::operator=(const PriorityQueue<Element>& queue)
{
  if (this != & queue)
  {
    deleteQueue(highestElement);
    highestElement = NULL;
    lowestElement = NULL;
    count = 0;
  
    copyQueue(queue.highestElement, highestElement, lowestElement);
    count = queue.count;
  }
  
  return *this;
}

template <typename Element>
void PriorityQueue<Element>::enqueue(const Element& element)
{
  Node* node = new Node(element);
  node->previous = NULL;
  node->next = NULL;
  
  count++;
  
  if (highestElement == NULL || lowestElement == NULL)
  {
    highestElement = node;
    lowestElement = node;
  }
  else
  {
    Node* current = highestElement;
    while(current != NULL && current->value >= node->value)
    {
      current = current->next; 
    }
    
        
    if (current == NULL)
    {
      lowestElement->next = node;
      node->previous = lowestElement;
      lowestElement = node;
    }
    else if (current == highestElement)
    {
      highestElement->previous = node;
      node->next = highestElement;
      highestElement = node;
    }
    else
    {
      node->previous = current->previous;
      node->next = current;
      current->previous->next = node;
      current->previous = node;
    }
  }
}

template <typename Element>
const Element* PriorityQueue<Element>::getLowest() const
{
  Element* value = NULL;
  if (lowestElement != NULL)
  {
    value = &(lowestElement->value);
  }
  return value;
}

template <typename Element>
const Element* PriorityQueue<Element>::getHighest() const
{
  Element* value = NULL;
  if (highestElement != NULL)
  {
    value = &(highestElement->value);
  }
  return value;
}

template <typename Element>
void PriorityQueue<Element>::dequeueLowest() //user of this function deallocates the memory returned
{  
  if (lowestElement != NULL)
  {
    Node* previous = lowestElement->previous;
    delete lowestElement;
    lowestElement = previous;
    
    if (lowestElement != NULL)
    {
      lowestElement->next = NULL;
    }
    else
    {
      highestElement = NULL;
    }
    count--;
  }
}
    
template <typename Element>
void PriorityQueue<Element>::dequeueHighest()
{  
  if (highestElement != NULL)
  {  
    Node* next = highestElement->next;
    delete highestElement;
    highestElement = next;
    
    if (highestElement != NULL)
    {
      highestElement->previous = NULL;
    }
    else
    {
      lowestElement = NULL;
    }

    count--;
  }
}

template <typename Element>
void PriorityQueue<Element>::emptyQueue()
{
  deleteQueue(highestElement);
  highestElement = NULL;
  lowestElement = NULL;
  count = 0;
}

template <typename Element>   
unsigned int PriorityQueue<Element>::size() const
{
  return count;
}




#endif //PRIORITY_QUEUE_H
