#ifndef PRACTICING_C__PRACTICING_H_
#define PRACTICING_C__PRACTICING_H_

#include <stdbool.h>
#include <stdio.h>

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

bool IsDoubleListEmpty( DoubleListNode* descriptor );

void MergeDoubleList( int start_left, int left_end, int right_end, DoubleListNode* descriptor );

void SortDoubleList( DoubleListNode* descriptor );

void DeleteDoubleList( DoubleListNode* descriptor );

// Stack

typedef struct StackNode
{
    struct StackNode* next;
    int data;
} StackNode;

StackNode* CreateStack();

void StackPush( StackNode* descriptor, int data );

void ShowStack( StackNode* descriptor );

int ReadAndDeleteTop( StackNode* descriptor );

void DeleteStack( StackNode* descriptor );

typedef struct QueueNode
{
    int data;
    int priority;
    struct QueueNode* next;
} QueueNode;

typedef struct QueueDesc
{
    struct QueueNode* last;
    struct QueueNode* first;
    int size;
} QueueDesc;

QueueDesc* CreateQueue();

void PriorityAdd( QueueDesc* descriptor, int data, int priority );

int PopFirst( QueueDesc* descriptor );

void DeleteQueue( QueueDesc* descriptor );

void ShowQueue( QueueDesc* descriptor );

typedef struct DequeNode
{
    struct DequeNode* next;
    struct DequeNode* prev;
    int *data;
} DequeNode;

DequeNode* CreateDeque( int size );

DequeNode* NewDequeNode( DequeNode* descriptor );

int DequeSize( DequeNode* descriptor );

void InitializeDeque( DequeNode* descriptor, const int array[], int size );

void DeleteDeque( DequeNode* descriptor );

typedef struct TreeNode
  {
  char data;
  struct TreeNode* left;
  struct TreeNode* right;
  } TreeNode;

typedef struct TreeDS
  {
  struct TreeNode* root;
  int size;
  } TreeDS;

void PreOrderDisplay( TreeNode* node );

void InOrderDisplay( TreeNode* node );

void PostOrderDisplay( TreeNode* node );

TreeDS* CreateTree();

void TreeInsert( const char* data, TreeNode* root_ptr, TreeDS* descriptor );

bool DeleteNode( const char* key, TreeNode* ptr );

bool FWriteTree( TreeNode* node, FILE* file );

bool FReadTree( TreeDS* descriptor, FILE* file );

void DeleteTreeHelper( TreeNode* node );

void DeleteTree( TreeDS* descriptor );

int RecursiveLinearSearch( int key, int pos, int array[], int size );

int RecursiveBinarySearch( int key, int array[], int size, int low, int high );

int RecursiveInterpolarSearch( int key, int array[], int size, int low, int high );

int ModuloBasedHash( int input, int modulus );

int MultiplicativeHash( int input, int size );

int SquareHash( const int input, const int size );

#endif // PRACTICING_C__PRACTICING_H_
