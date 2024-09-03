#include "practicing.h"

#include <stdio.h>

int main()
{
    /*// creating array of random numbers
    int array_size = 10;
    int array[ array_size ];

    GenerateRandom( 1, 100, array, array_size );

    // opening file, writing unsorted data, closing
    FILE* file_ptr;

    file_ptr = fopen( "my_file.txt", "w" );
    if ( file_ptr == NULL )
    {
        printf( "Couldn't open file!" );
        return 1;
    }

    for ( int counter = 0; counter < array_size; ++counter )
    {
        fprintf( file_ptr, "%d ", array[ counter ] );
    }
    fprintf( file_ptr, "\n" );

    fclose( file_ptr );

    // creating single linked list, rewriting numbers from the file
    SingleListNode* descriptor = CreateSingleList();

    file_ptr = fopen( "my_file.txt", "r" );
    if ( file_ptr == NULL )
    {
        printf( "Couldn't open file!" );
        return 1;
    }

    for ( int temp; fscanf( file_ptr, "%d", &temp ) != EOF; )
    {
        AddBackNode( temp, descriptor );
    }

    fclose( file_ptr );

    ShowList( descriptor );

    IterativeMergeSort( descriptor ); // sorting numbers in the list

    ShowList( descriptor );

    file_ptr = fopen( "my_file.txt", "a" );
    if ( file_ptr == NULL )
    {
        printf( "Couldn't open file!" );
        return 1;
    }

    // writing sorted data from the list to the file
    for ( SingleListNode* ptr = descriptor->next; ptr; ptr = ptr->next )
    {
        fprintf( file_ptr, "%d ", ptr->data );
    }
    fprintf( file_ptr, "\n" );

    fclose( file_ptr );

    DeleteList( descriptor );*//*DoubleListNode* descriptor = CreateDoubleList();

    AddAt( descriptor, 0, 1 );
    AddAt( descriptor, 1, 2 );
    AddAt( descriptor, 2, 1 );
    AddAt( descriptor, 3, 4 );
    AddAt( descriptor, 4, 5 );

    printf( "Is Double Linked List empty: %d\n", IsDoubleListEmpty( descriptor ) );

    ShowDoubleList( descriptor );

    SortDoubleList( descriptor );

    ShowDoubleList( descriptor );

    DeleteDoubleList( descriptor );*//*StackNode* descriptor = CreateStack();
    printf( "Stack was created\n" );

    StackPush( descriptor, 1 );
    StackPush( descriptor, 2 );
    StackPush( descriptor, 3 );
    StackPush( descriptor, 4 );

    printf( "Deleted element: %d\n", ReadAndDeleteTop( descriptor ) );

    ShowStack( descriptor );

    DeleteStack( descriptor );
    printf( "Stack was deleted\n" );*//*QueueDesc* descriptor = CreateQueue();
    printf( "A queue was created\n" );

    PriorityAdd( descriptor, 1, 1 );
    PriorityAdd( descriptor, 1, 1 );
    PriorityAdd( descriptor, 2, 2 );
    PriorityAdd( descriptor, 3, 3 );
    PriorityAdd( descriptor, 4, 4 );

    PopFirst( descriptor );

    ShowQueue( descriptor );

    DeleteQueue( descriptor );
    printf( "A queue was deleted\n" );*/

    TreeDS* descriptor = CreateTree();

    TreeInsert( "D", descriptor );
    TreeInsert( "C", descriptor );
    TreeInsert( "B", descriptor );
    TreeInsert( "A", descriptor );
    TreeInsert( "J", descriptor );

    // writing

    FILE* file;
    file = fopen( "tree_file.bin", "wb" );
    if ( file == NULL )
    {
        perror( "Error opening file" );
        return 1;
    }

    // DeleteNode( "A", descriptor->root );

    InOrderDisplay( descriptor->root );

    FWriteTree( descriptor->root, file );

    DeleteTree( descriptor );

    fclose( file );

    // reading

    FILE* file_read;
    file_read = fopen( "tree_file.bin", "rb" );
    if ( file_read == NULL )
    {
        perror( "Error opening file" );
        return 0;
    }

    TreeDS* new_tree_ds = CreateTree();

    FReadTree( new_tree_ds, file_read );//rewrite data from the file to the new tree

    printf( "\n" );
    InOrderDisplay( new_tree_ds->root );

    fclose( file_read );

    DeleteTree( new_tree_ds );

    return 0;
}
