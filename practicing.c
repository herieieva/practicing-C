#include "practicing.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SingleListNode* CreateSingleList()
{
    SingleListNode* descriptor = (SingleListNode*) malloc( sizeof( SingleListNode ) );
    if ( !descriptor )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }
    descriptor->next = NULL;
    return descriptor;
}

void AddBackNode( int data, SingleListNode* descriptor )
{
    SingleListNode* back = (SingleListNode*) malloc( sizeof( SingleListNode ) );
    if ( !back )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    back->data = data;
    back->next = NULL;

    if ( descriptor->next == NULL )
    {
        descriptor->next = back;
        return;
    }

    SingleListNode* ptr = descriptor->next;
    while ( ptr->next != NULL )
    {
        ptr = ptr->next;
    }

    ptr->next = back;
}

bool AddBefore( int position, int data, SingleListNode* descriptor )
{
    SingleListNode* ptr = descriptor;
    int counter;
    for ( counter = 0; ptr->next != NULL && counter != position - 1; ++counter )
    {
        ptr = ptr->next;
    }

    if ( ptr->next == NULL && counter != position - 1 )
    {
        return false;
    }

    SingleListNode* new_node = (SingleListNode*) malloc( sizeof( SingleListNode ) );
    if ( !new_node )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    new_node->data = data;
    new_node->next = ptr->next;

    ptr->next = new_node;
    return true;
}

bool AddAfter( int position, int data, SingleListNode* descriptor )
{
    if ( descriptor->next == NULL )
    {
        return false;
    }

    SingleListNode* current = descriptor->next;

    int counter = 0;

    while ( current->next != NULL && counter != position )
    {
        current = current->next;
        ++counter;
    }

    if ( current->next == NULL && counter != position )
    {
        return false;
    }

    SingleListNode* new_node = (SingleListNode*) malloc( sizeof( SingleListNode ) );
    if ( !new_node )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    new_node->data = data;
    new_node->next = current->next;

    current->next = new_node;

    return true;
}

bool FindShow( int data, SingleListNode* descriptor )
{
    SingleListNode* ptr = descriptor;
    while ( ptr )
    {
        if ( ptr->data == data )
        {
            printf( "Found it: %d\n", ptr->data );
            return true;
        }
        ptr = ptr->next;
    }
    return false; // no such element in list
}

bool ShowFirst( SingleListNode* descriptor )
{
    if ( descriptor->next == NULL )
    {
        return false;
    }

    printf( "First element of the list: %d", descriptor->next->data );
    return true;
}

void ShowLast( SingleListNode* descriptor )
{
    SingleListNode* ptr = descriptor;

    while ( ptr->next != NULL )
    {
        ptr = ptr->next;
    }

    printf( "The last element: %d\n", ptr->data );
}

void ShowList( SingleListNode* descriptor )
{
    SingleListNode* ptr = descriptor->next;
    printf( "Single linked list: \n" );
    while ( ptr )
    {
        printf( "%d ", ptr->data );
        ptr = ptr->next;
    }
    printf( "\n" );
}

bool IsListEmpty( SingleListNode* descriptor )
{
    if ( descriptor->next == NULL )
    {
        return true;
    }
    return false;
}

SingleListNode* ModifyListAt( SingleListNode* descriptor, int position )
{
    if ( position > HowMuchNodes( descriptor ) )
    {
        return NULL;
    }

    SingleListNode* ptr = descriptor->next;

    for ( int counter = 0; counter < position; ++counter )
    {
        ptr = ptr->next;
    }

    return ptr;
}

DoubleListNode* ModifyDoubleList( DoubleListNode* descriptor, int position )
{
    if ( position > DoubleListSize( descriptor ) )
    {
        return NULL;
    }

    DoubleListNode* ptr = descriptor->next;

    for ( int counter = 0; counter < position; ++counter )
    {
        ptr = ptr->next;
    }

    return ptr;
}

void RewriteFromList( SingleListNode* from, int to[], int start, int end )
{
    SingleListNode* ptr = from->next;

    ++start;
    ++end;

    int size = end - start + 1;
    int counter;

    for ( counter = 1; counter < start; ++counter )
    {
        ptr = ptr->next;
    }

    for ( int index = 0; index < size; ++index )
    {
        to[ index ] = ptr->data;
        ptr         = ptr->next;
    }
}

void RewriteDoubleList( DoubleListNode* from, int to[], int start, int end )
{
    DoubleListNode* ptr = from->next;

    ++start;
    ++end;

    int size = end - start + 1;
    int counter;

    for ( counter = 1; counter < start; ++counter )
    {
        ptr = ptr->next;
    }

    for ( int index = 0; index < size; ++index )
    {
        to[ index ] = ptr->data;
        ptr         = ptr->next;
    }
}

void IterativeMerge( int start_left, int left_end, int right_end, SingleListNode* descriptor )
{
    int left_size  = left_end - start_left + 1;
    int right_size = right_end - left_end;

    int left_sub[ left_size ];
    int right_sub[ right_size ];

    RewriteFromList( descriptor, left_sub, start_left, left_end );
    RewriteFromList( descriptor, right_sub, left_end + 1, right_end );

    int left = 0, right = 0, orig = start_left;
    while ( left < left_size && right < right_size )
    {
        if ( left_sub[ left ] <= right_sub[ right ] )
        {
            SingleListNode* ptr = ModifyListAt( descriptor, orig );
            ptr->data           = left_sub[ left ];

            ++left;
        }
        else
        {
            SingleListNode* ptr = ModifyListAt( descriptor, orig );
            ptr->data           = right_sub[ right ];

            ++right;
        }
        ++orig;
    }

    while ( left < left_size )
    {
        SingleListNode* ptr = ModifyListAt( descriptor, orig );
        ptr->data           = left_sub[ left ];

        ++left;
        ++orig;
    }

    while ( right < right_size )
    {
        SingleListNode* ptr = ModifyListAt( descriptor, orig );
        ptr->data           = right_sub[ right ];

        ++right;
        ++orig;
    }
}

void IterativeMergeSort( SingleListNode* descriptor )
{
    int orig_size = HowMuchNodes( descriptor );

    for ( int subs_size = 1; subs_size < orig_size - 1; subs_size = subs_size * 2 )
    {
        for ( int start_left = 0; start_left < orig_size - 1; start_left += subs_size * 2 )
        {
            int left_end  = ( start_left + subs_size - 1 ) < orig_size - 1
                 ? start_left + subs_size - 1
                 : orig_size - 1;
            int right_end = ( start_left + ( 2 * subs_size ) - 1 ) < orig_size - 1
                ? start_left + ( 2 * subs_size ) - 1
                : orig_size - 1;

            IterativeMerge( start_left, left_end, right_end, descriptor );
        }
    }
}

bool DeleteAt( int position, SingleListNode* descriptor )
{
    SingleListNode* current = descriptor;
    if ( current->next == NULL )
    {
        return false;
    }
    SingleListNode* next_el = current->next;

    int counter;
    for ( counter = 1; next_el->next != NULL && counter != position; ++counter )
    {
        current = next_el;
        next_el = next_el->next;
    }

    if ( next_el->next == NULL && counter != position )
    {
        return false;
    }

    current->next = next_el->next;
    free( next_el );
    return true;
}

int HowMuchNodes( SingleListNode* descriptor )
{
    SingleListNode* ptr = descriptor->next;

    int counter = 0;

    for ( ; ptr; ++counter )
    {
        ptr = ptr->next;
    }

    return counter;
}

void DeleteList( SingleListNode* descriptor )
{
    if ( !descriptor )
    {
        return;
    }

    SingleListNode* curr_node = descriptor->next;
    SingleListNode* next_node;

    while ( curr_node != NULL )
    {
        next_node = curr_node->next;
        free( curr_node );
        curr_node = next_node;
    }

    free( descriptor );
}

int* GenerateRandom( int min, int max, int destination[], int size )
{
    int array_size = size;

    unsigned int seed = time( 0 );

    int rand_int;
    for ( int counter = 0; counter < array_size; ++counter )
    {
        rand_int               = rand_r( &seed ) % ( max - min + 1 + min );
        destination[ counter ] = rand_int;
    }

    return destination;
}

// Double linked list

DoubleListNode* CreateDoubleList()
{
    DoubleListNode* descriptor = (DoubleListNode*) malloc( sizeof( DoubleListNode ) );
    if ( !descriptor )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    printf( "A list with descriptor created\n" );

    descriptor->next = NULL;
    descriptor->prev = NULL;

    return descriptor;
}

bool AddAt( DoubleListNode* descriptor, int number, int data )
{
    if ( descriptor->next == NULL && number != 0 )
    {
        return false;
    }

    DoubleListNode* previous = descriptor;

    int counter = 0;

    while ( counter != number )
    {
        previous = previous->next;
        ++counter;
    }

    if ( !previous && counter != number )
    {
        return false;
    }

    DoubleListNode* new_node = (DoubleListNode*) malloc( sizeof( DoubleListNode ) );
    if ( !new_node )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = previous;

    previous->next = new_node;

    descriptor->prev = new_node;

    return true;
}

void ShowDoubleList( DoubleListNode* descriptor )
{
    DoubleListNode* ptr = descriptor->next;

    printf( "Single linked list: \n" );
    while ( ptr )
    {
        printf( "%d ", ptr->data );
        ptr = ptr->next;
    }
    printf( "\n" );
}

int DoubleListSize( DoubleListNode* descriptor )
{
    DoubleListNode* ptr = descriptor->next;

    int counter;
    for ( counter = 0; ptr; ++counter )
    {
        ptr = ptr->next;
    }

    return counter;
}

bool IsDoubleListEmpty( DoubleListNode* descriptor )
{
    if ( descriptor->next && descriptor->prev == NULL )
    {
        return true;
    }

    return false;
}

bool DoubleDeleteAt( DoubleListNode* descriptor, int position )
{
    DoubleListNode* ptr = descriptor;
    DoubleListNode* temp;

    // if size of list is equal to position, we delete the last element (previous to descriptor)
    if ( DoubleListSize( descriptor ) - 1 == position )
    {
        temp = descriptor->prev;

        ptr       = temp->prev;
        ptr->next = NULL;

        descriptor->prev = ptr;

        free( temp );
        return true;
    }

    temp = descriptor;
    ptr  = ptr->next;

    int counter;
    for ( counter = 0; counter < position && ptr; ++counter )
    {
        ptr  = ptr->next;
        temp = temp->next;
    }

    if ( !ptr && counter != position )
    {
        return false;
    }

    if ( !ptr )
    {
        temp->next = NULL;
        free( ptr );
        descriptor->prev = temp;
        return true;
    }

  //a node before the node we want to delete has to know what it's "new next node" is
    temp->next      = ptr->next;
    ptr->next->prev = temp; //the "new next node" has to know it's "new previous"
    free( ptr );
    return true;
}

void MergeDoubleList( int start_left, int left_end, int right_end, DoubleListNode* descriptor )
{
    int left_size  = left_end - start_left + 1;
    int right_size = right_end - left_end;

    int left_sub[ left_size ];
    int right_sub[ right_size ];

    RewriteDoubleList( descriptor, left_sub, start_left, left_end );
    RewriteDoubleList( descriptor, right_sub, left_end + 1, right_end );

    int left = 0, right = 0, orig = start_left;
    while ( left < left_size && right < right_size )
    {
        if ( left_sub[ left ] <= right_sub[ right ] )
        {
            DoubleListNode* ptr = ModifyDoubleList( descriptor, orig );
            ptr->data           = left_sub[ left ];

            ++left;
        }
        else
        {
            DoubleListNode* ptr = ModifyDoubleList( descriptor, orig );
            ptr->data           = right_sub[ right ];

            ++right;
        }
        ++orig;
    }
    while ( left < left_size )
    {
        DoubleListNode* ptr = ModifyDoubleList( descriptor, orig );
        ptr->data           = left_sub[ left ];

        ++left;
        ++orig;
    }

    while ( right < right_size )
    {
        DoubleListNode* ptr = ModifyDoubleList( descriptor, orig );
        ptr->data           = right_sub[ right ];

        ++right;
        ++orig;
    }
}

void SortDoubleList( DoubleListNode* descriptor )
{
    int orig_size = DoubleListSize( ( descriptor ) );

    for ( int subs_size = 1; subs_size < orig_size - 1; subs_size = subs_size * 2 )
    {
        for ( int left_start = 0; left_start < orig_size - 1; left_start += subs_size * 2 )
        {
            int left_end = ( left_start + subs_size - 1 ) < orig_size - 1
                ? left_start + subs_size - 1
                : orig_size - 1;

            int right_end = ( left_start + ( 2 * subs_size ) - 1 ) < orig_size - 1
                ? left_start + ( 2 * subs_size ) - 1
                : orig_size - 1;

            MergeDoubleList( left_start, left_end, right_end, descriptor );
        }
    }
}

void DeleteDoubleList( DoubleListNode* descriptor )
{
    if ( descriptor->next == NULL )
    {
        free( descriptor );
        printf( "The list with descriptor deleted!\n" );
        return;
    }

    DoubleListNode* slow = descriptor->next;
    DoubleListNode* fast;

    while ( slow )
    {
        fast = slow->next;
        free( slow );
        slow = fast;
    }

    free( descriptor );

    printf( "The list with descriptor deleted!\n" );
}
