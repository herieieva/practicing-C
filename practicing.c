#include "practicing.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

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

    // a node before the node we want to delete has to know what it's "new next node" is
    temp->next      = ptr->next;
    ptr->next->prev = temp; // the "new next node" has to know it's "new previous"
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

// Stack

StackNode* CreateStack()
{
    StackNode* descriptor = (StackNode*) malloc( sizeof( StackNode ) );
    if ( !descriptor )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    descriptor->next = NULL;

    return descriptor;
}

void StackPush( StackNode* descriptor, int data )
{
    StackNode* new_node = (StackNode*) malloc( sizeof( StackNode ) );
    if ( !new_node )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    new_node->data = data;
    new_node->next = descriptor->next;

    descriptor->next = new_node;
}

void ShowStack( StackNode* descriptor )
{
    StackNode* ptr = descriptor->next;

    while ( ptr )
    {
        printf( "%d ", ptr->data );
        ptr = ptr->next;
    }
    printf( "\n" );
}

int ReadAndDeleteTop( StackNode* descriptor )
{
    if ( descriptor->next == NULL )
    {
        printf( "Error! The stack is empty. Nothing to delete (apart from descriptor)\n" );
    }

    StackNode* ptr = descriptor->next;

    descriptor->next = ptr->next;

    int data = ptr->data;

    free( ptr );

    return data;
}

void DeleteStack( StackNode* descriptor )
{
    StackNode* ptr = descriptor;

    while ( ptr != NULL )
    {
        StackNode* temp = ptr;
        ptr             = ptr->next;
        free( temp );
    }
}

// Queue

QueueDesc* CreateQueue()
{
    QueueDesc* descriptor = (QueueDesc*) malloc( sizeof( QueueDesc ) );
    if ( !descriptor )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough dynamic memory.\n" );
        exit( EXIT_FAILURE );
    }

    descriptor->size  = 0;
    descriptor->first = NULL;
    descriptor->last  = NULL;

    return descriptor;
}

void PriorityAdd( QueueDesc* descriptor, int data, int priority )
{
    QueueNode* new = (QueueNode*) malloc( sizeof( QueueNode ) );
    if ( !new )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough dynamic memory.\n" );
        exit( EXIT_FAILURE );
    }

    new->data     = data;
    new->next     = NULL;
    new->priority = priority;

    if ( descriptor->first == NULL )
    {
        descriptor->first = new;
        descriptor->last  = new;
        ++descriptor->size;
        return;
    }

    QueueNode* pre_ptr = descriptor->first;
    QueueNode* ptr     = descriptor->first;
    for ( ; ptr && ptr->priority <= priority; ptr = ptr->next )
    {
        pre_ptr = ptr;
    }

    if ( !ptr )
    {
        descriptor->last->next = new;
        descriptor->last       = new;
    }
    else if ( ptr == descriptor->first )
    {
        new->next         = descriptor->first;
        descriptor->first = new;
    }
    else
    {
        pre_ptr->next = new;
        new->next     = ptr;
    }

    descriptor->size++;
}

int PopFirst( QueueDesc* descriptor )
{
    QueueNode* ptr  = descriptor->first;
    QueueNode* next = ptr->next; // second node

    descriptor->first = next;

    next->next = ptr->next->next; // assign third element`s address to the second "next" field

    int result = ptr->data;
    free( ptr );
    return result;
}

void ShowQueue( QueueDesc* descriptor )
{
    QueueNode* ptr = descriptor->first;

    while ( ptr )
    {
        printf( "%d ", ptr->data );
        ptr = ptr->next;
    }

    printf( "\n" );
}

void DeleteQueue( QueueDesc* descriptor )
{
    if ( !descriptor )
    {
        return;
    }

    QueueNode* ptr = descriptor->first;
    QueueNode* next;

    while ( ptr )
    {
        next = ptr->next;
        free( ptr );
        ptr = next;
    }

    free( descriptor );
}

// Deque

DequeNode* CreateDeque( int size )
{
    DequeNode* descriptor = (DequeNode*) malloc( sizeof( DequeNode ) );

    descriptor->data      = (int*) malloc( sizeof( int ) * size );
    descriptor->data[ 0 ] = size;

    descriptor->next = NULL;
    descriptor->prev = NULL;

    return descriptor;
}

DequeNode* NewDequeNode( DequeNode* descriptor )
{
    DequeNode* new_node = (DequeNode*) malloc( sizeof( DequeNode ) );
    if ( !new_node )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough dynamic memory.\n" );
        exit( EXIT_FAILURE );
    }

    new_node->data = (int*) malloc( sizeof( int ) * descriptor->data[ 0 ] );
    new_node->next = NULL;

    if ( descriptor->next == NULL )
    {
        new_node->prev = descriptor;

        descriptor->next = new_node;

        return new_node;
    }

    DequeNode* ptr = descriptor->next;
    while ( ptr->next != NULL )
    {
        ptr = ptr->next;
    }

    new_node->prev = ptr;

    ptr->next = new_node;

    return new_node;
}

int DequeSize( DequeNode* descriptor )
{
    DequeNode* ptr = descriptor->next;

    int counter = 0;
    for ( ; ptr; ++counter )
    {
        ptr = ptr->next;
    }

    return counter * descriptor->data[ 0 ];
}

void InitializeDeque( DequeNode* descriptor, const int array[], int size )
{
    while ( DequeSize( descriptor ) < size )
    {
        NewDequeNode( descriptor );
    }

    DequeNode* ptr = descriptor->next;
    for ( int array_ind = 0; array_ind < size; ptr = ptr->next )
    {
        for ( int counter = 0; counter < descriptor->data[ 0 ] && array_ind < size;
              ++counter, ++array_ind )
        {
            ptr->data[ counter ] = array[ array_ind ];
            printf("%d ",  ptr->data[ counter ]);
        }
    }
}

void DeleteDeque( DequeNode* descriptor )
{
    DequeNode* ptr = descriptor->next;

    for ( DequeNode* prev = descriptor; ptr; ptr = prev->next )
    {
        free( prev->data );
        free( prev );
        prev = ptr;
    }
}*/

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
    if ( !descriptor->next )
    {
        printf( "This list is empty. \n" );
        return;
    }

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

/*DoubleListNode* ModifyDoubleList( DoubleListNode* descriptor, int position )
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
}*/

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

TreeDS* CreateTree()
{
    TreeDS* descriptor = (TreeDS*) malloc( sizeof( TreeDS ) );
    if ( !descriptor )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    descriptor->root = NULL;
    descriptor->size = 0;

    return descriptor;
}

void PreOrderDisplay( TreeNode* node )
{
    if ( node )
    {
        printf( "%c", node->data );
        PreOrderDisplay( node->left );
        PreOrderDisplay( node->right );
    }
}

void InOrderDisplay( TreeNode* node )
{
    if ( node )
    {
        InOrderDisplay( node->left );
        printf( "%c", node->data );
        InOrderDisplay( node->right );
    }
}

void PostOrderDisplay( TreeNode* node )
{
    if ( node )
    {
        PostOrderDisplay( node->left );
        PostOrderDisplay( node->right );
        printf( "%c", node->data );
    }
}

bool FWriteTree( TreeNode* node, FILE* file )
{
    if ( node )
    {
        FWriteTree( node->left, file );
        fwrite( &node->data, sizeof( node->data ), 1, file );
        FWriteTree( node->right, file );
    }

    return true;
}

bool FReadTree( TreeDS* descriptor, FILE* file )
{
    if ( !descriptor )
    {
        return false;
    }

    char temp[ 1 ];
    while ( fread( temp, sizeof( char ), 1, file ) == 1 )
    {
        TreeInsert( temp, descriptor->root, descriptor );
    }
    return true;
}

void TreeInsert( const char* data, TreeNode* root_ptr, TreeDS* descriptor )
{
    // Handle the case when the tree is empty (root_ptr is NULL)
    if ( root_ptr == NULL )
    {
        TreeNode* new_node = (TreeNode*) malloc( sizeof( TreeNode ) );
        if ( !new_node )
        {
            perror( "Memory allocation failed" );
            fprintf( stderr, "Error: Probably not enough space!\n" );
            exit( EXIT_FAILURE );
        }

        new_node->data = *data;
        new_node->left = new_node->right = NULL;

        descriptor->root = new_node;
        descriptor->size++;
        return;
    }

    TreeNode *parent = NULL, *current = root_ptr;

    // Traverse the tree to find the insertion point
    while ( current != NULL )
    {
        parent = current;
        if ( *data < current->data )
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    TreeNode* new_node = (TreeNode*) malloc( sizeof( TreeNode ) );
    if ( !new_node )
    {
        perror( "Memory allocation failed" );
        fprintf( stderr, "Error: Probably not enough space!\n" );
        exit( EXIT_FAILURE );
    }

    new_node->data = *data;
    new_node->left = new_node->right = NULL;

    // Insert the new node as the child of the parent
    if ( *data < parent->data )
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }

    descriptor->size++;
}

bool DeleteNode( const char* key, TreeNode* root_ptr )
{
    if ( !root_ptr ) // empty tree
    {
        return false;
    }

    TreeNode *current = root_ptr, *parent = NULL;

    while ( current && *key != current->data ) // looking for the node to delete (current)
    {
        parent  = current;
        current = ( *key < current->data ) ? current->left : current->right;
    }
    if ( !current ) // no such node in the tree
    {
        return false;
    }

    if ( current->right
         && current->left ) // if the node meant to be deleted (current) has two children
    {
        TreeNode *child, *child_parent;

        child = current->right;

        while ( child->left )
        {
            child_parent = child;
            child        = child->left;
        }

        current->data = child->data;

        current = child;
        parent  = child_parent;
    }

    // when the current node has only 1 child
    TreeNode* last_child = ( current->left )
        ? current->left
        : current->right; // we initialize new variable with the node that exists

    if ( !parent ) // current node is the root node
    {
        root_ptr = last_child; // exclude the current node, but remember the nodes that go after it
    }
    else if ( parent->left == current ) // link the child (left or right) and parent
    {
        parent->left = last_child;
    }
    else
    {
        parent->right = last_child;
    }

    free( current );
    return true;
}

void DeleteTreeHelper( TreeNode* node )
{
    if ( node == NULL )
    {
        return;
    }

    DeleteTreeHelper( node->left );
    DeleteTreeHelper( node->right );

    free( node );
}

void DeleteTree( TreeDS* descriptor )
{
    DeleteTreeHelper( descriptor->root );

    free( descriptor );
}

int RecursiveLinearSearch( int key, int pos, int array[], int size )
{
    if ( pos > size - 1 )
    {
        return -1; // no such element in the array
    }

    if ( key == array[ pos ] )
    {
        return pos; // found it
    }

    return RecursiveLinearSearch( key, pos + 1, array, size );
}

int RecursiveBinarySearch( int key, int array[], int size, int low, int high )
{
    if ( low > high )
    {
        return -1;
    }

    int mid = ( low + high ) / 2;

    if ( key == array[ mid ] )
    {
        return mid;
    }
    else if ( key > array[ mid ] )
    {
        return RecursiveBinarySearch( key, array, size, mid + 1, high );
    }
    else
    {
        return RecursiveBinarySearch( key, array, size, low, mid - 1 );
    }
}

int RecursiveInterpolarSearch( int key, int array[], int size, int low, int high )
{
    if ( size <= 1 )
    {
        return 0;
    }

    if ( low > high )
    {
        return -1;
    }

    int mid = low + ( high - low ) * ( ( key - array[ low ] ) / ( array[ high ] - array[ low ] ) );
    if ( array[ mid ] == key )
    {
        return mid;
    }
    else if ( array[ mid ] > key )
    {
        return RecursiveInterpolarSearch( key, array, size, low, mid - 1 );
    }
    else
    {
        return RecursiveInterpolarSearch( key, array, size, mid + 1, high );
    }
}

int ModuloBasedHash( const int input, const int modulus )
{
    return input % modulus;
}

int MultiplicativeHash( const int input, const int size )
{
    const double fi            = 0.6180339887;
    const double multiplicated = input * fi;
    double fractionalPart      = multiplicated - floor( multiplicated );
    int hash                   = fractionalPart * size;
    return hash;
}

int SquareHash( const int input, const int size )
  {
  int square = input * input;
  int result_size = 16;
  int shift = (32 - result_size) / 2;
  int hash_value = ((square >> shift) & 0xffff);
  return hash_value%size;
  }
