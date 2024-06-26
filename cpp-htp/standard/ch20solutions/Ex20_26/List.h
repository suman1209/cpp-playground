// Exercise 20.26 Solution: List.h
// Template List class definition.
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Listnode.h" // ListNode class definition
using namespace std;

template< typename NODETYPE >
class List 
{
public:
   List(); // constructor
   ~List(); // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool insertByLocation( const NODETYPE &, int );
   bool deleteNodeByValue( const NODETYPE &, NODETYPE & );
   bool deleteNodeByLocation( NODETYPE &, int );
   bool isEmpty() const;
   void print() const;
private:
   ListNode< NODETYPE > *firstPtr; // pointer to first node
   ListNode< NODETYPE > *lastPtr; // pointer to last node

   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );
}; // end class List

// default constructor
template< typename NODETYPE >
List< NODETYPE >::List() 
   : firstPtr( 0 ), lastPtr( 0 ) 
{ 
   // empty body
} // end List constructor

// destructor
template< typename NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) // List is not empty
   {    
      cout << "Destroying nodes ...\n";

      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 ) // delete remaining nodes
      {  
         tempPtr = currentPtr;
         cout << tempPtr->data << '\n';
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      } // end while
   } // end if

   cout << "All nodes destroyed\n\n";
} // end List destructor

// insert node at front of list
template< typename NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value ); // new node

   if ( isEmpty() ) // List is empty
      firstPtr = lastPtr = newPtr; // new list has only one node
   else // List is not empty
   {
      newPtr->nextPtr = firstPtr; // point new node to previous 1st node
      firstPtr = newPtr; // aim firstPtr at new node
   } // end else
} // end function insertAtFront

// insert node at back of list
template< typename NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value ); // new node

   if ( isEmpty() ) // List is empty
      firstPtr = lastPtr = newPtr; // new list has only one node
   else // List is not empty
   {
      lastPtr->nextPtr = newPtr; // update previous last node
      lastPtr = newPtr; // new last node
   } // end else
} // end function insertAtBack

// delete node from front of list
template< typename NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() ) // List is empty
      return false; // delete unsuccessful
   else 
   {
      ListNode< NODETYPE > *tempPtr = firstPtr; // hold tempPtr to delete

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0; // no nodes remain after removal
      else
         firstPtr = firstPtr->nextPtr; // point to previous 2nd node

      value = tempPtr->data; // return data being removed
      delete tempPtr; // reclaim previous front node
      return true; // delete successful
   } // end else
} // end function removeFromFront

// delete node from back of list
template< typename NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() ) // List is empty
      return false; // delete unsuccessful
   else 
   {
      ListNode< NODETYPE > *tempPtr = lastPtr; // hold tempPtr to delete

      if ( firstPtr == lastPtr ) // List has one element
         firstPtr = lastPtr = 0; // no nodes remain after removal
      else 
      {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         // locate second-to-last element            
         while ( currentPtr->nextPtr != lastPtr )    
            currentPtr = currentPtr->nextPtr; // move to next node

         lastPtr = currentPtr; // remove last node
         currentPtr->nextPtr = 0; // this is now the last node
      } // end else

      value = tempPtr->data; // return value from old last node
      delete tempPtr; // reclaim former last node
      return true; // delete successful
   } // end else
} // end function removeFromBack

// is List empty?
template< typename NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
} // end function isEmpty

// return pointer to newly allocated node
template< typename NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
   const NODETYPE &value )
{
   return new ListNode< NODETYPE >( value );
} // end function getNewNode

// display contents of List
template< typename NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) // List is empty
   {
      cout << "The list is empty\n\n";
      return;
   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) // get element data
   {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;
   } // end while

   cout << "\n\n";
} // end function print

// insert node anywhere in list
template< typename NODETYPE >
bool List< NODETYPE >::insertByLocation(
   const NODETYPE &value, int location )
{
   int count = 1;

   // if list is empty and index is not 0, then index is not valid
   if ( isEmpty() && ( location != 0 ) )
      return false;

   if ( location < 0 ) // negative indices are invalid
      return false;
   else if ( location == 0 ) // if index 0, simply insert at front
   {
      insertAtFront( value );
      return true; // successful insertion
   } // end else

   // pointers_and_references used to keep track of current node,
   // previous node and new node
   ListNode< NODETYPE > *currentPtr = firstPtr->nextPtr,
      *previousPtr = firstPtr, *newPtr = getNewNode( value );

   // loop until we reach proper location
   while ( count < location )
   {
      if ( currentPtr == lastPtr ) // if end of list found first
      {
         if ( location == count + 1 )
         {
            // if user specified index one after end of list,
            // add node at back of list
            insertAtBack( value );
            return true; // successful insertion
         } // end inner if

         return false; // index too large, invalid input
      } // end outer if
      else
      {
         // continue to next position in list
         previousPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         count++;
      } // end else
   } // end while

   // we have reached specified location, insert new node
   previousPtr->nextPtr = newPtr;
   newPtr->nextPtr = currentPtr;
   return true; // successful insertion
} // end function insertByLocation

// delete specified value
template< typename NODETYPE >
bool List< NODETYPE >::deleteNodeByValue(
   const NODETYPE &val, NODETYPE &deletedVal )
{
   if ( isEmpty() )
      return false; // delete unsuccessful
   if ( firstPtr->getData() == val ) // value at beginning of list
      return removeFromFront( deletedVal ); // remove from the front
   else // search through list for value specified
   {
      // pointers_and_references used to keep track of current and previous nodes
      ListNode< NODETYPE > *currentPtr = firstPtr, *previousPtr;

      // loop until end of list reached
      do
      {
         // move to next node
         previousPtr = currentPtr;
         currentPtr = currentPtr->getNextPtr();

         // if value found
         if ( currentPtr->getData() == val )
         {
            // store data of node to be deleted
            ListNode< NODETYPE > *tempPtr = currentPtr;
            deletedVal = currentPtr->getData();

            // have previous node point to next node
            previousPtr->setNextPtr( currentPtr->getNextPtr() );

            delete tempPtr; // delete node
            return true; // delete successful
         } // end if
      } while ( currentPtr != lastPtr ); // end do...while loop

      // if we are here, reached end of list and did not find value
      return false; // delete unsuccessful
   } // end else
} // end function deleteNodeByValue

template< typename NODETYPE >
bool List< NODETYPE >::deleteNodeByLocation(
   NODETYPE &deletedValue, int location )
{
   int count = 1; // counter used to move through list

   if ( isEmpty() )
      return false; // no nodes to delete

   if ( location < 0 ) // invalid index
      return false;
   else if ( location == 0 ) // index 0, remove from front of list
      return removeFromFront( deletedValue );

   // keep track of current and previous pointers_and_references
   ListNode< NODETYPE > *currentPtr = firstPtr->nextPtr,
      *previousPtr = firstPtr;

   // move through list until proper location reached
   while ( count < location )
   {
      if ( ( currentPtr == lastPtr ) ) // if end of list reached first
         return false; // invalid index entered
      else
      {
         // move to next node in list
         previousPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         count++;
      } // end else
   } // end while

   // we have reached specified location, remove node
   ListNode< NODETYPE > *tempPtr = currentPtr;
   deletedValue = currentPtr->getData();

   // have previous node point to next node
   previousPtr->setNextPtr( currentPtr->getNextPtr() );

   delete tempPtr; // delete node
   return true; // delete successful
} // end function deleteNodeByLocation

#endif

/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
