#ifndef PRACTICING_C__PRACTICING_H_
#define PRACTICING_C__PRACTICING_H_

#include <stdbool.h>

typedef struct SingleListNode
{
    int data;
    struct SingleListNode* next;
} SingleListNode;

SingleListNode* CreateSingleList();

void AddBackNode( int data, SingleListNode* descriptor );

bool IsListEmpty( SingleListNode* descriptor );

bool AddBefore( int position, int data, SingleListNode* );

bool AddAfter( int position, int data, SingleListNode* descriptor );

SingleListNode* ModifyListAt( SingleListNode* descriptor, int position );

bool FindShow( int data, SingleListNode* descriptor );

bool ShowFirst( SingleListNode* descriptor );

void ShowLast( SingleListNode* descriptor );

void ShowList( SingleListNode* descriptor );

bool DeleteAt( int position, SingleListNode* descriptor );

SingleListNode* MergeSortList( SingleListNode* descriptor );

void RewriteFromList( SingleListNode* from, int to[], int start, int end );

void IterativeMergeSort( SingleListNode* descriptor );

void IterativeMerge( int start_left, int left_end, int right_end, SingleListNode* descriptor );

int HowMuchNodes( SingleListNode* descriptor );

void DeleteList( SingleListNode* descriptor );

int* GenerateRandom( int min, int max, int destination[], int size );

// Double linked list

typedef struct DoubleListNode
{
    int data;
    struct DoubleListNode* prev;
    struct DoubleListNode* next;
} DoubleListNode;

DoubleListNode* CreateDoubleList();

bool AddAt( DoubleListNode* descriptor, int number, int data );

void ShowDoubleList( DoubleListNode* descriptor );

bool DoubleDeleteAt( DoubleListNode* descriptor, int position );

int DoubleListSize( DoubleListNode* descriptor );

bool IsDoubleListEmpty(DoubleListNode* descriptor);

void MergeDoubleList( int start_left, int left_end, int right_end, DoubleListNode* descriptor );

void SortDoubleList( DoubleListNode* descriptor );

void DeleteDoubleList( DoubleListNode* descriptor );
#endif // PRACTICING_C__PRACTICING_H_
