/* Intrusive links: a doubly linked list with its first and last node, and a tree whose
 * children are kept as a list of siblings. The links sit at the start of the game's objects. */
#ifndef CLEAN_AUTOLOAD_2_LINKS_H
#define CLEAN_AUTOLOAD_2_LINKS_H

#include "types.h"

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *first;
    ListNode *last;
} List;

typedef struct TreeNode {
    struct TreeNode *parent;
    struct TreeNode *first_child;
    struct TreeNode *prev;
    struct TreeNode *next;
} TreeNode;

/* A tree without a parent node: its single top node. */
typedef struct Tree {
    TreeNode *top;
} Tree;

BOOL List_PushFront(List *list, ListNode *node);
BOOL List_PushBack(List *list, ListNode *node);
BOOL List_Remove(List *list, ListNode *node);
BOOL List_InsertAfter(List *list, ListNode *node, ListNode *after);
BOOL Tree_Detach(Tree *tree, TreeNode *node);
BOOL Tree_Attach(Tree *tree, TreeNode *node, TreeNode *parent);
void TreeNode_Clear(TreeNode *node);
TreeNode *TreeNode_Init(TreeNode *node);

#endif
