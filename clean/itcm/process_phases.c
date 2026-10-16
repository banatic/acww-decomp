/* The processes' code in the ITCM (process_phases.h).
 *
 * REQUIRES: processes and tree nodes at word-aligned addresses in main RAM, as every object of
 * the game is. */
#include "process_phases.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(offsetof(TreeNode, next) == 0xc, "the next sibling");
static_assert(offsetof(ProcessNode, owner) == 0x10, "the node's process");
static_assert(offsetof(Process, state) == 0x0e, "the process's state");
static_assert(offsetof(Process, delete_requested) == 0x0f, "the deletion asked for");
static_assert(offsetof(Process, activate_pending) == 0x10, "made active in CONNECT");
static_assert(offsetof(Process, create_pending) == 0x11, "listed in CONNECT");
static_assert(offsetof(Process, flags) == 0x13, "the process's flags");
static_assert(offsetof(ProcessLink, order) == 0x0c, "the link's order");
static_assert(sizeof(MemberFn) == 8, "a member pointer is two words");

/* The four lists (autoload_2/process.c): created, active by execute order, deleted, active by
 * draw order. */
extern ProcessList data_021fd014;
extern ProcessList data_021fd004;
extern ProcessList data_021fd034;
extern ProcessList data_021fd024;

/* The member functions of the DRAW phase (vtable slots 9, 10 and 11) and of the EXECUTE phase
 * (slots 6, 7 and 8): main, check and outcome. */
extern const MemberFn data_01ffd0bc, data_01ffd0c4, data_01ffd0dc;
extern const MemberFn data_01ffd0cc, data_01ffd0d4, data_01ffd0b4;

/* ---- The tree ---- */

/* func_01ffcfc0: the node after `node`'s subtree in tree order: its next sibling, else the next
 * sibling of its nearest ancestor that has one; NULL when there is none. */
TreeNode *TreeNode_NextSkipChildren(TreeNode *node)
{
    if (node->next != NULL) {
        return node->next;
    }
    for (TreeNode *above = node->parent; above != NULL; above = above->parent) {
        if (above->next != NULL) {
            return above->next;
        }
    }
    return NULL;
}
CLEAN_AS(func_01ffcfc0, TreeNode_NextSkipChildren)

/* func_01ffcffc: the node after `node` in tree order (parents before their children): its
 * first child, else the node after its subtree. */
TreeNode *TreeNode_Next(TreeNode *node)
{
    if (node->first_child != NULL) {
        return node->first_child;
    }
    return TreeNode_NextSkipChildren(node);
}
CLEAN_AS(func_01ffcffc, TreeNode_Next)

/* ---- Running a phase ---- */

/* The object a member function is called on: `object` moved by the adjustment (adj / 2). */
static void *member_object(const MemberFn *fn, void *object)
{
    return (void *) ((uintptr_t) object + (uintptr_t) (intptr_t) ((fn->adj - (fn->adj & 1)) / 2));
}

/* The address of the code a member function calls on `self`: its own, or for a virtual one
 * the entry `ptr` bytes into `self`'s vtable. */
static uintptr_t member_code(const MemberFn *fn, const void *self)
{
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) self;
        return *(const u32 *) (vtable + fn->ptr);
    }
    return fn->ptr;
}

static int call_int(const MemberFn *fn, void *object)
{
    void *self = member_object(fn, object);
    return ((int (*)(void *)) member_code(fn, self))(self);
}

static void call_with(const MemberFn *fn, void *object, int value)
{
    void *self = member_object(fn, object);
    ((void (*)(void *, int)) member_code(fn, self))(self, value);
}

/* func_01ffd44c: a phase run on a process: `check` first; when it allows (not 0), `main`; then
 * `outcome` is told how it went (ProcessOutcome: -1 from `main` is a failure, 1 done, anything
 * else not done yet). The result of `main`, or 0 when it was not called. */
int Process_RunPhase(Process *self, MemberFn main, MemberFn check, MemberFn outcome)
{
    int told;
    int result = call_int(&check, self);
    if (result != 0) {
        result = call_int(&main, self);
        if (result == -1) {
            told = OUTCOME_FAILED;
        } else if (result == 1) {
            told = OUTCOME_DONE;
        } else {
            told = OUTCOME_PENDING;
        }
    } else {
        told = OUTCOME_REFUSED;
    }
    call_with(&outcome, self, told);
    return result;
}
CLEAN_AS(func_01ffd44c, Process_RunPhase)

/* func_01ffd0e4: the draw list's member function: the DRAW phase run on the process (main,
 * check and outcome: vtable slots 9, 10 and 11). */
void Process_RunDraw(Process *self)
{
    Process_RunPhase(self, data_01ffd0bc, data_01ffd0c4, data_01ffd0dc);
}
CLEAN_AS(func_01ffd0e4, Process_RunDraw)

/* func_01ffd14c: the execute list's member function: the EXECUTE phase run on the process
 * (main, check and outcome: vtable slots 6, 7 and 8). */
void Process_RunExecute(Process *self)
{
    Process_RunPhase(self, data_01ffd0cc, data_01ffd0d4, data_01ffd0b4);
}
CLEAN_AS(func_01ffd14c, Process_RunExecute)

/* ---- The CONNECT phase ---- */

/* A stop flag of the parent's (set by the game or carried from above) carried to the child as
 * `above`, or cleared from it. */
static void carry_flag(Process *self, const Process *parent, u8 own, u8 above)
{
    if ((parent->flags & own) != 0 || (parent->flags & above) != 0) {
        self->flags |= above;
    } else if ((self->flags & above) != 0) {
        self->flags &= (u8) ~above;
    }
}

/* An active process's link moved to the place of its wanted order, when that changed. */
static void apply_order(ProcessList *list, ProcessLink *link)
{
    if (link->wanted_order != link->order) {
        List_Remove(&list->list, &link->node);
        link->order = link->wanted_order;
        ProcessList_Insert(&list->list, link);
    }
}

/* func_01ffd1b4: the tree's member function (the CONNECT phase), run on every process in tree
 * order. A process whose deletion was asked for leaves its lists for the front of the delete
 * list and asks the deletion of its children. Otherwise it takes its parent's stop flags, and
 * an active process is moved to the orders it wants, while one being created goes to the create
 * list (create_pending) or becomes active (activate_pending); the second is looked at only
 * without the first. TRUE. */
int Process_Connect(Process *self)
{
    if (self->delete_requested) {
        self->delete_requested = FALSE;
        if (self->state == STATE_ACTIVE) {
            List_Remove(&data_021fd004.list, &self->link.node);
            List_Remove(&data_021fd024.list, &self->draw_link.node);
        } else {
            List_Remove(&data_021fd014.list, &self->link.node);
        }
        List_PushFront(&data_021fd034.list, &self->link.node);
        self->state = STATE_DELETING;
        for (TreeNode *child = self->node.tree.first_child; child != NULL; child = child->next) {
            Process_RequestDelete(((ProcessNode *) child)->owner);
        }
        return TRUE;
    }

    Process *parent = Process_GetParent(self);
    if (parent != NULL) {
        carry_flag(self, parent, PROCESS_EXECUTE_STOPPED, PROCESS_EXECUTE_STOPPED_ABOVE);
        carry_flag(self, parent, PROCESS_DRAW_STOPPED, PROCESS_DRAW_STOPPED_ABOVE);
    }

    if (self->state == STATE_ACTIVE) {
        apply_order(&data_021fd004, &self->link);
        apply_order(&data_021fd024, &self->draw_link);
    } else if (self->state != STATE_DELETING) {
        if (self->create_pending) {
            self->create_pending = FALSE;
            List_PushBack(&data_021fd014.list, &self->link.node);
        } else if (self->activate_pending) {
            self->activate_pending = FALSE;
            ProcessList_Insert(&data_021fd004.list, &self->link);
            ProcessList_Insert(&data_021fd024.list, &self->draw_link);
            self->state = STATE_ACTIVE;
        }
    }
    return TRUE;
}
CLEAN_AS(func_01ffd1b4, Process_Connect)

/* ---- The base class's execute and draw (vtable slots 6 to 11) ---- */

/* func_01ffd3e4 (vtable slot 11): nothing to do after drawing. */
void Process_AfterDraw(Process *self)
{
    (void) self;
}
CLEAN_AS(func_01ffd3e4, Process_AfterDraw)

/* func_01ffd3e8 (vtable slot 10): a process is drawn unless its deletion was asked for or it
 * or an ancestor stopped drawing. */
int Process_CanDraw(Process *self)
{
    return !self->delete_requested && (self->flags & PROCESS_DRAW_STOPPED_ABOVE) == 0;
}
CLEAN_AS(func_01ffd3e8, Process_CanDraw)

/* func_01ffd410 (vtable slot 9): the base class's drawing is done at once. */
int Process_DrawDefault(Process *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_01ffd410, Process_DrawDefault)

/* func_01ffd418 (vtable slot 8): nothing to do after executing. */
void Process_AfterExecute(Process *self)
{
    (void) self;
}
CLEAN_AS(func_01ffd418, Process_AfterExecute)

/* func_01ffd41c (vtable slot 7): a process is executed unless its deletion was asked for or it
 * or an ancestor stopped executing. */
int Process_CanExecute(Process *self)
{
    return !self->delete_requested && (self->flags & PROCESS_EXECUTE_STOPPED_ABOVE) == 0;
}
CLEAN_AS(func_01ffd41c, Process_CanExecute)

/* func_01ffd444 (vtable slot 6): the base class's execution is done at once. */
int Process_ExecuteDefault(Process *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_01ffd444, Process_ExecuteDefault)
