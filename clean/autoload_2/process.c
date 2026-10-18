/* The game's processes (process.h).
 *
 * REQUIRES: processes, links and step lists at word-aligned addresses in main RAM, as every
 * object of the game is; the ARM reads a word at an unaligned address rotated. */
#include "process.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "itcm/process_phases.h"

static_assert(sizeof(ProcessNode) == 0x14, "the tree links and the process");
static_assert(sizeof(ProcessLink) == 0x10, "list links, the process and two orders");
static_assert(sizeof(ProcessList) == 0x10, "a list and its member function");
static_assert(sizeof(ProcessTree) == 0xc, "the tree and its member function");
static_assert(offsetof(StepList, step_state) == 0x12, "the steps' own state");
static_assert(offsetof(Process, node) == 0x14, "the tree links");
static_assert(offsetof(Process, link) == 0x28, "the main list links");
static_assert(offsetof(Process, draw_link) == 0x38, "the draw list links");
static_assert(sizeof(Process) == 0x50, "the base process");

/* The phase the main loop is in (ProcessPhase), and the ROM's names of the phases. */
extern int data_0213e7fc;
extern const char *const data_02138fbc[];

/* The tree of every process (CONNECT) and the four lists: the processes being created
 * (CREATE), the active ones by execute order (EXECUTE), the ones being deleted (DELETE) and the
 * active ones by draw order (DRAW). A process is in one of the first three lists by its `link`
 * and, while active, in the draw list by its `draw_link`. */
extern ProcessTree data_021fcff8;
extern ProcessList data_021fd014;
extern ProcessList data_021fd004;
extern ProcessList data_021fd034;
extern ProcessList data_021fd024;

/* The link a list walk is at (ProcessList_ForEach); a debug display (func_02001610) shows its
 * process's class, or else the class being spawned. */
extern ProcessLink *data_021fcff4;

/* The spawn under way: its stage (SpawnStage) and class id (NO_CLASS when none), both shown by
 * the debug display. */
extern u8 data_021fcfd4;
extern u16 data_021fcfdc;
enum SpawnStage {
    SPAWN_IDLE = 0,
    SPAWN_HOOK = 1,      /* in the spawn hook */
    SPAWN_ARGS = 2,      /* setting the constructor's arguments */
    SPAWN_CONSTRUCT = 3, /* in the profile's create function */
    SPAWN_CREATE = 4,    /* creating the new process */
};
#define NO_CLASS 0xffff

/* The constructor's arguments (Process_SetConstructArgs): the parameter, the class id, the last
 * spawn argument and the parent's tree node (NULL: a process at the top). */
extern u32 data_021fcff0;
extern u16 data_021fcfe0;
extern u8 data_021fcfd8;
extern TreeNode *data_021fcfe4;

/* The next process id. */
extern u32 data_0213e778;

/* The profiles by class id (set at start-up to data_020e3134). */
extern Profile **data_021fd044;

/* Hooks called with the class id before a spawn and after a deletion; nothing in the game is
 * known to set them. */
extern int (*data_021fcfe8)(int class_id);
extern void (*data_021fcfec)(int class_id);

/* The base class's vtable; its slots are the functions of this file:
 *  0 Process_CreateDefault       1 Process_CanCreateDefault   2 Process_AfterCreate
 *  3 Process_DeleteDefault       4 Process_CanDelete          5 Process_AfterDelete
 *  6-8 execute and 9-11 draw (in the ITCM)
 * 12 Process_OnDeleteRequested  13 Process_CreateFittedHeap  14 Process_CreateHeap
 * 15 Process_FillHeapDefault    16 (none)                    17 Process_DestructFree */
extern const u32 data_0213e7b4[];
#define SLOT_ON_DELETE_REQUESTED 12
#define SLOT_FILL_HEAP 15
#define SLOT_DESTRUCT_FREE 17

/* The three member functions of the create phase (main, check, outcome: vtable slots 0, 1, 2)
 * and of the delete phase (slots 3, 4, 5). */
extern MemberFn data_0213e794;
extern MemberFn data_0213e78c;
extern MemberFn data_0213e77c;
extern MemberFn data_0213e784;
extern MemberFn data_0213e79c;
extern MemberFn data_0213e7a4;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

typedef int ProcessMethod(Process *self);
typedef void ProcessProcedure(Process *self);
typedef s16 StepRun(StepList *list, int step);
typedef void StepUndo(StepList *list, int step);

/* The function in vtable slot `slot` of an object whose first word is its vtable. */
static uintptr_t virtual_slot(const void *object, int slot)
{
    return (*(const u32 *const *) object)[slot];
}

/* `fn` called on `object`. */
static void call_member(const MemberFn *fn, void *object)
{
    uintptr_t self = (uintptr_t) object + (uintptr_t) (intptr_t) (fn->adj >> 1);
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) self;
        target = *(const u32 *) (vtable + fn->ptr);
    }
    ((void (*)(void *)) target)((void *) self);
}

static Process *owner_of(TreeNode *node)
{
    return ((ProcessNode *) node)->owner;
}

/* ---- Spawning ---- */

/* func_020edba4: a process of `class_id` spawned at the top of the tree; NULL when its profile
 * made none. */
Process *Process_SpawnRoot(int class_id, int param, int unk_12)
{
    return Process_Spawn(class_id, NULL, (u32) param, (u8) unk_12);
}
CLEAN_AS(func_020edba4, Process_SpawnRoot)

/* func_020edbbc: a process of `class_id` spawned as a child of `parent`; NULL without a
 * parent. */
Process *Process_SpawnChild(int class_id, Process *parent, u32 param, u8 unk_12)
{
    if (parent == NULL) {
        return NULL;
    }
    return Process_Spawn(class_id, &parent->node.tree, param, unk_12);
}
CLEAN_AS(func_020edbbc, Process_SpawnChild)

/* func_020edbec: the deletion hook told a process of `class_id` is gone. */
void Process_NotifyDeleted(int class_id)
{
    if (data_021fcfec == NULL) {
        return;
    }
    data_021fcfec(class_id);
}
CLEAN_AS(func_020edbec, Process_NotifyDeleted)

/* func_020edc20: the spawn hook told a process of `class_id` is to be made; what it answers, 2
 * without a hook. */
int Process_NotifySpawn(int class_id)
{
    if (data_021fcfe8 == NULL) {
        return 2;
    }
    return data_021fcfe8(class_id);
}
CLEAN_AS(func_020edc20, Process_NotifySpawn)

/* func_020edc58: a process of `class_id` made by its profile, under the tree node `parent`, and
 * its creation started (Process_FirstCreate); NULL when the profile made none. The spawn hook's
 * answer is not used. */
Process *Process_Spawn(int class_id, TreeNode *parent, u32 param, u8 unk_12)
{
    data_021fcfdc = (u16) class_id;
    data_021fcfd4 = SPAWN_HOOK;
    Process_NotifySpawn(class_id);
    data_021fcfd4 = SPAWN_ARGS;
    Process_SetConstructArgs((u16) class_id, parent, param, unk_12);
    data_021fcfd4 = SPAWN_CONSTRUCT;
    Process *process = data_021fd044[class_id]->create();
    if (process != NULL) {
        data_021fcfd4 = SPAWN_CREATE;
        Process_FirstCreate(process);
    }
    data_021fcfd4 = SPAWN_IDLE;
    data_021fcfdc = NO_CLASS;
    return process;
}
CLEAN_AS(func_020edc58, Process_Spawn)

/* func_020edd30: the arguments the next process's constructor reads (Process_Construct). */
void Process_SetConstructArgs(u16 class_id, TreeNode *parent, u32 param, u8 unk_12)
{
    data_021fcff0 = param;
    data_021fcfe0 = class_id;
    data_021fcfd8 = unk_12;
    data_021fcfe4 = parent;
}
CLEAN_AS(func_020edd30, Process_SetConstructArgs)

/* func_020edd74: TRUE when a process below `self` in the tree is still being created. */
int Process_IsAnyDescendantCreating(Process *self)
{
    TreeNode *end = TreeNode_NextSkipChildren(&self->node.tree);
    for (TreeNode *node = self->node.tree.first_child; node != NULL && node != end; node = TreeNode_Next(node)) {
        if (owner_of(node)->state == STATE_CREATING) {
            return TRUE;
        }
    }
    return FALSE;
}
CLEAN_AS(func_020edd74, Process_IsAnyDescendantCreating)

/* func_020edddc: the delete phase run on the process (Process_CanDelete, its delete, then
 * Process_AfterDelete, which destroys it when it is done); when it is done the deletion hook is
 * told its class, read before. The delete's result. */
int Process_RunDelete(Process *self)
{
    u16 class_id = self->class_id;
    int result = Process_RunPhase(self, data_0213e784, data_0213e79c, data_0213e7a4);
    if (result == 1) {
        Process_NotifyDeleted(class_id);
    }
    return result;
}
CLEAN_AS(func_020edddc, Process_RunDelete)

/* func_020ede60: the create phase run on the process. */
void Process_RunCreate(Process *self)
{
    Process_RunPhase(self, data_0213e794, data_0213e78c, data_0213e77c);
}
CLEAN_AS(func_020ede60, Process_RunCreate)

/* func_020edec8: a new process's creation tried at once. If it is not finished (nor its
 * deletion asked for), it goes to the create list to be tried again each frame; while that
 * list is walked (the CREATE phase) this waits for the CONNECT phase. */
void Process_FirstCreate(Process *self)
{
    Process_RunCreate(self);
    if (self->delete_requested || self->activate_pending || self->state != STATE_CREATING) {
        return;
    }
    if (data_0213e7fc == PHASE_CREATE) {
        self->create_pending = TRUE;
        return;
    }
    List_PushBack(&data_021fd014.list, &self->link.node);
}
CLEAN_AS(func_020edec8, Process_FirstCreate)

/* ---- The process's heap ---- */

/* func_020edfc4 (vtable slot 15): what fills a process's new heap; the base class has nothing
 * to put there. */
int Process_FillHeapDefault(Process *self)
{
    (void) self;
    return TRUE;
}
CLEAN_AS(func_020edfc4, Process_FillHeapDefault)

/* The process's new frame heap filled (vtable slot 15) while it is the current heap, with a
 * 16-byte block taken from it besides: first when the heap's memory starts 16 bytes past a
 * 32-byte boundary, else last. TRUE when the filling and the block succeeded (the first block's
 * result is not looked at). */
static int fill_heap(Process *self, Heap *heap)
{
    BOOL pad_first = ((uintptr_t) heap->start & 0x10) != 0;
    if (pad_first) {
        Heap_AllocBlock(heap, 0x10, 0x10);
    }
    int ok = ((ProcessMethod *) virtual_slot(self, SLOT_FILL_HEAP))(self);
    if (!pad_first && Heap_AllocBlock(heap, 0x10, 0x10) == NULL) {
        ok = FALSE;
    }
    return ok;
}

/* The size a heap's allocations take, rounded up to `unit`. */
static u32 used_size(Heap *heap, u32 unit)
{
    u32 used = heap->size - (u32) Heap_GetFreeSize(heap);
    return (used + unit - 1) & ~(unit - 1);
}

/* func_020edfcc (vtable slot 14): a frame heap of `size` bytes in `parent` (NULL: the current
 * heap) made for the process and filled; TRUE when the process has one (already, or now). When
 * none could be made or filled the process's deletion is asked for.
 * QUIRK: the heap's free size is asked and not used. */
int Process_CreateHeap(Process *self, int size, Heap *parent)
{
    if (self->heap != NULL) {
        return TRUE;
    }
    if (size != 0) {
        Heap *heap = Heap_PushFrameHeap(size, parent);
        if (heap != NULL) {
            int ok = fill_heap(self, heap);
            Heap_GetFreeSize(heap);
            Heap_PopThreadHeap();
            if (ok) {
                self->heap = heap;
                return TRUE;
            }
            Heap_Destroy(heap);
        }
    }
    Process_RequestDelete(self);
    return FALSE;
}
CLEAN_AS(func_020edfcc, Process_CreateHeap)

/* func_020ee0a4 (vtable slot 13): a frame heap made for the process, filled, and shrunk to what
 * it holds; TRUE when the process has one (already, or now), else its deletion is asked for.
 *
 * The heap is first made of `size` bytes; when that is exactly what the filling took (rounded
 * up to 32 bytes) it is kept. Otherwise (size 0, no room, a failed filling, or a size that does
 * not fit) the process is filled into a heap of all the room `parent` has, unless the first
 * heap was filled but did not fit: that one goes on. Then, when `parent` has room enough
 * besides, a second heap of exactly the size needed is made, and if it lies lower in memory it
 * takes the place of the first and is filled again (without the 16-byte block). The heap kept is
 * shrunk to what it holds (Heap_Adjust).
 * REQUIRES: `parent` has room for a frame heap when the first one is not kept; the original
 * goes on with a NULL heap. */
int Process_CreateFittedHeap(Process *self, u32 size, Heap *parent)
{
    Heap *heap = NULL;
    u32 needed;
    if (self->heap != NULL) {
        return TRUE;
    }
    if (size != 0) {
        heap = Heap_PushFrameHeap((int) size, parent);
    }
    if (heap != NULL) {
        int ok = fill_heap(self, heap);
        Heap_PopThreadHeap();
        if (!ok) {
            Heap_Destroy(heap);
            heap = NULL;
        } else {
            needed = used_size(heap, 0x20);
            if (size == needed) {
                Heap_Adjust(heap);
                self->heap = heap;
                return TRUE;
            }
        }
    }
    if (heap == NULL) {
        heap = Heap_PushFrameHeap(-1, parent);
        int ok = fill_heap(self, heap);
        Heap_PopThreadHeap();
        if (!ok) {
            Heap_Destroy(heap);
            Process_RequestDelete(self);
            return FALSE;
        }
        needed = used_size(heap, 0x20);
    }

    Heap *lower = NULL;
    u32 held = used_size(heap, 0x10);
    u32 room = (u32) Heap_GetFreeSize(parent);
    if (held + 0x30 < room) {
        lower = Heap_PushFrameHeap((int) needed, parent);
    }
    if (lower != NULL) {
        if ((uintptr_t) lower < (uintptr_t) heap) {
            Heap_Destroy(heap);
            heap = NULL;
            int ok = ((ProcessMethod *) virtual_slot(self, SLOT_FILL_HEAP))(self);
            Heap_PopThreadHeap();
            if (!ok) {
                Heap_Destroy(lower);
                lower = NULL;
            }
        } else {
            Heap_PopThreadHeap();
            Heap_Destroy(lower);
            lower = NULL;
        }
    }
    if (lower != NULL) {
        Heap_Adjust(lower);
        self->heap = lower;
        return TRUE;
    }
    if (heap != NULL) {
        Heap_Adjust(heap);
        self->heap = heap;
        return TRUE;
    }
    Process_RequestDelete(self);
    return FALSE;
}
CLEAN_AS(func_020ee0a4, Process_CreateFittedHeap)

/* ---- Orders ---- */

/* The order of an active process changed in a list: outside the list's own phase the link is
 * taken out and put back in its place now; during it only the wanted order is set, and the
 * CONNECT phase moves it. A process not active only has both orders set. */
static void set_order(Process *self, ProcessLink *link, ProcessList *list, int list_phase, u16 order)
{
    if (self->state == STATE_ACTIVE) {
        if (data_0213e7fc == list_phase) {
            link->wanted_order = order;
            return;
        }
        List_Remove(&list->list, &link->node);
        link->order = order;
        link->wanted_order = order;
        ProcessList_Insert(&list->list, link);
        return;
    }
    link->order = order;
    link->wanted_order = order;
}

/* func_020ee324 */
void Process_SetDrawOrder(Process *self, u16 order)
{
    set_order(self, &self->draw_link, &data_021fd024, PHASE_DRAW, order);
}
CLEAN_AS(func_020ee324, Process_SetDrawOrder)

/* func_020ee3c0 */
void Process_SetExecuteOrder(Process *self, u16 order)
{
    set_order(self, &self->link, &data_021fd004, PHASE_EXECUTE, order);
}
CLEAN_AS(func_020ee3c0, Process_SetExecuteOrder)

/* ---- The base class ---- */

/* func_020ee45c: the parent process, NULL at the top. */
Process *Process_GetParent(Process *self)
{
    TreeNode *parent = self->node.tree.parent;
    return parent != NULL ? owner_of(parent) : NULL;
}
CLEAN_AS(func_020ee45c, Process_GetParent)

/* func_020ee470: the process's deletion asked for, once, and not while it is being deleted; it
 * starts in the next CONNECT phase. The process is told first (vtable slot 12). */
void Process_RequestDelete(Process *self)
{
    if (self->delete_requested || self->state == STATE_DELETING) {
        return;
    }
    self->delete_requested = TRUE;
    ((ProcessProcedure *) virtual_slot(self, SLOT_ON_DELETE_REQUESTED))(self);
}
CLEAN_AS(func_020ee470, Process_RequestDelete)

/* func_020ee4cc: the heap the process owns (destroyed with it). */
void Process_SetHeap(Process *self, Heap *heap)
{
    self->heap = heap;
}
CLEAN_AS(func_020ee4cc, Process_SetHeap)

/* func_020ee4d4 (vtable slot 12): nothing to do when the deletion is asked for. */
void Process_OnDeleteRequested(Process *self)
{
    (void) self;
}
CLEAN_AS(func_020ee4d4, Process_OnDeleteRequested)

/* func_020ee4d8 (vtable slot 5): once deleted, the process leaves the tree and the delete list,
 * its heap and its loading steps are undone, and the object is destroyed (vtable slot 17).
 * QUIRK: the process is tested for NULL after it was used. */
void Process_AfterDelete(Process *self, int outcome)
{
    if (outcome != OUTCOME_DONE) {
        return;
    }
    Tree_Detach(&data_021fcff8.tree, &self->node.tree);
    List_Remove(&data_021fd034.list, &self->link.node);
    if (self->heap != NULL) {
        Heap_Delete(self->heap);
    }
    if (self->steps != NULL) {
        StepList_Undo(self->steps);
    }
    if (self == NULL) {
        return;
    }
    ((ProcessProcedure *) virtual_slot(self, SLOT_DESTRUCT_FREE))(self);
}
CLEAN_AS(func_020ee4d8, Process_AfterDelete)

/* func_020ee550 (vtable slot 4): a process can be deleted once its loading steps are idle and
 * it has no children left. */
int Process_CanDelete(Process *self)
{
    if (self->steps != NULL && !StepList_IsIdle(self->steps)) {
        return FALSE;
    }
    return self->node.tree.first_child == NULL;
}
CLEAN_AS(func_020ee550, Process_CanDelete)

/* func_020ee594 (vtable slot 3): the base class's deletion is done at once. */
int Process_DeleteDefault(Process *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_020ee594, Process_DeleteDefault)

/* func_020ee59c (vtable slot 2): once created, the process leaves the create list and becomes
 * active in the execute and draw lists; while the execute list is walked this waits for the
 * CONNECT phase. */
void Process_AfterCreate(Process *self, int outcome)
{
    if (outcome != OUTCOME_DONE) {
        return;
    }
    List_Remove(&data_021fd014.list, &self->link.node);
    if (data_0213e7fc == PHASE_EXECUTE) {
        self->activate_pending = TRUE;
        return;
    }
    ProcessList_Insert(&data_021fd004.list, &self->link);
    ProcessList_Insert(&data_021fd024.list, &self->draw_link);
    self->state = STATE_ACTIVE;
}
CLEAN_AS(func_020ee59c, Process_AfterCreate)

/* func_020ee61c (vtable slot 1): the base class can always be created. */
int Process_CanCreateDefault(void)
{
    return TRUE;
}
CLEAN_AS(func_020ee61c, Process_CanCreateDefault)

/* func_020ee624 (vtable slot 0): the base class's creation is done at once. */
int Process_CreateDefault(Process *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_020ee624, Process_CreateDefault)

/* func_020ee62c: the destructor: the base class's vtable put back. */
void Process_Destruct(Process *self)
{
    self->vtable = data_0213e7b4;
}
CLEAN_AS(func_020ee62c, Process_Destruct)

/* func_020ee63c (vtable slot 17): the destructor, and the object freed to the auxiliary heap
 * processes are allocated from (Heap_AllocAuxZeroed). */
Process *Process_DestructFree(Process *self)
{
    self->vtable = data_0213e7b4;
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020ee63c, Process_DestructFree)

/* func_020ee660: the constructor. The process takes the next id and the spawn's arguments
 * (Process_SetConstructArgs), joins the tree under the parent given there, and takes its orders
 * from its profile. It stops executing or drawing when its parent does. */
Process *Process_Construct(Process *self)
{
    self->vtable = data_0213e7b4;
    TreeNode_Init(&self->node.tree);
    self->node.owner = self;
    self->link = (ProcessLink){.owner = self};
    self->draw_link = (ProcessLink){.owner = self};

    self->id = data_0213e778++;
    self->param = data_021fcff0;
    self->class_id = data_021fcfe0;
    self->unk_12 = data_021fcfd8;
    Tree_Attach(&data_021fcff8.tree, &self->node.tree, data_021fcfe4);

    const Profile *profile = data_021fd044[self->class_id];
    self->link.order = profile->execute_order;
    self->link.wanted_order = profile->execute_order;
    self->draw_link.order = profile->draw_order;
    self->draw_link.wanted_order = profile->draw_order;

    Process *parent = Process_GetParent(self);
    if (parent != NULL) {
        if ((parent->flags & (PROCESS_EXECUTE_STOPPED | PROCESS_EXECUTE_STOPPED_ABOVE)) != 0) {
            self->flags |= PROCESS_EXECUTE_STOPPED_ABOVE;
        }
        if ((parent->flags & (PROCESS_DRAW_STOPPED | PROCESS_DRAW_STOPPED_ABOVE)) != 0) {
            self->flags |= PROCESS_DRAW_STOPPED_ABOVE;
        }
    }
    return self;
}
CLEAN_AS(func_020ee660, Process_Construct)

/* ---- The lists ---- */

/* func_020ee7a4: the first link after `after` (NULL: from the start) whose process is of
 * `class_id`; NULL when none is. */
ProcessLink *ProcessList_FindClass(List *list, int class_id, ProcessLink *after)
{
    ListNode *node = after != NULL ? after->node.next : list->first;
    for (; node != NULL; node = node->next) {
        if (((ProcessLink *) node)->owner->class_id == class_id) {
            return (ProcessLink *) node;
        }
    }
    return NULL;
}
CLEAN_AS(func_020ee7a4, ProcessList_FindClass)

/* func_020ee7f0: the link whose process has the id `id`; NULL when none has. */
ProcessLink *ProcessList_FindId(List *list, int id)
{
    for (ListNode *node = list->first; node != NULL; node = node->next) {
        if ((int) ((ProcessLink *) node)->owner->id == id) {
            return (ProcessLink *) node;
        }
    }
    return NULL;
}
CLEAN_AS(func_020ee7f0, ProcessList_FindId)

/* func_020ee834: the list's member function called on each of its processes, in order (the
 * next link is read before, so a process may leave the list); TRUE. */
int ProcessList_ForEach(ProcessList *list)
{
    if (list->each.ptr == 0) {
        return TRUE;
    }
    ProcessLink *link = (ProcessLink *) list->list.first;
    data_021fcff4 = link;
    while (link != NULL) {
        Process *process = link->owner;
        ProcessLink *next = (ProcessLink *) link->node.next;
        call_member(&list->each, process);
        link = next;
        data_021fcff4 = link;
    }
    return TRUE;
}
CLEAN_AS(func_020ee834, ProcessList_ForEach)

/* func_020ee8a8: the link put in the list by its order, after those of the same order; FALSE
 * without a link. */
int ProcessList_Insert(List *list, ProcessLink *link)
{
    if (link == NULL) {
        return FALSE;
    }
    ProcessLink *first = (ProcessLink *) list->first;
    if (first == NULL) {
        return List_PushBack(list, &link->node);
    }
    if (first->order > link->order) {
        return List_InsertAfter(list, &link->node, NULL);
    }
    ProcessLink *after = first;
    while (after->node.next != NULL && ((ProcessLink *) after->node.next)->order <= link->order) {
        after = (ProcessLink *) after->node.next;
    }
    return List_InsertAfter(list, &link->node, &after->node);
}
CLEAN_AS(func_020ee8a8, ProcessList_Insert)

/* func_020ee934: the processes run for a frame (the main loop): all the phases, or only DRAW. */
void Process_RunFrame(int draw_only)
{
    if (draw_only) {
        Process_RunDrawPhase();
    } else {
        Process_RunAllPhases();
    }
}
CLEAN_AS(func_020ee934, Process_RunFrame)

/* func_020ee964 */
void Process_RunDrawPhase(void)
{
    data_0213e7fc = PHASE_DRAW;
    ProcessList_ForEach(&data_021fd024);
    data_0213e7fc = PHASE_NULL;
}
CLEAN_AS(func_020ee964, Process_RunDrawPhase)

/* func_020ee9a0 */
void Process_RunAllPhases(void)
{
    data_0213e7fc = PHASE_DELETE;
    ProcessList_ForEach(&data_021fd034);
    data_0213e7fc = PHASE_CREATE;
    ProcessList_ForEach(&data_021fd014);
    data_0213e7fc = PHASE_EXECUTE;
    ProcessList_ForEach(&data_021fd004);
    data_0213e7fc = PHASE_DRAW;
    ProcessList_ForEach(&data_021fd024);
    data_0213e7fc = PHASE_CONNECT;
    ProcessTree_ForEach(&data_021fcff8);
    data_0213e7fc = PHASE_NULL;
}
CLEAN_AS(func_020ee9a0, Process_RunAllPhases)

/* func_020eea3c: the phase's name ("NULL", "CONNECT", "CREATE", "EXECUTE", "DELETE", "DRAW"),
 * for the debug display.
 * REQUIRES: `phase` is a ProcessPhase. */
const char *Process_PhaseName(u32 phase)
{
    return data_02138fbc[phase];
}
CLEAN_AS(func_020eea3c, Process_PhaseName)

/* func_020eea4c: the tree's member function called on every process in tree order (the next
 * node is found before, so a process may leave the tree); TRUE. */
int ProcessTree_ForEach(ProcessTree *tree)
{
    if (tree->each.ptr == 0) {
        return TRUE;
    }
    TreeNode *node = tree->tree.top;
    while (node != NULL) {
        TreeNode *next = TreeNode_Next(node);
        call_member(&tree->each, owner_of(node));
        node = next;
    }
    return TRUE;
}
CLEAN_AS(func_020eea4c, ProcessTree_ForEach)

/* ---- Loading steps ---- */

/* func_020eeacc: a running list advanced by one step; TRUE unless it is still running. */
int StepList_IsIdle(StepList *list)
{
    if (list->state == STEPS_RUNNING) {
        list->state = StepList_Run(list, FALSE);
    }
    return list->state != STEPS_RUNNING;
}
CLEAN_AS(func_020eeacc, StepList_IsIdle)

/* func_020eeb04: the steps run from the one under way, while each is done (vtable slot 2
 * returns STEPS_DONE), one only unless `all`; the list's state, STEPS_DONE without steps. The
 * state is left as it was when no step is left. */
s16 StepList_Run(StepList *list, int all)
{
    if (list->steps == NULL || list->state == STEPS_DONE) {
        return STEPS_DONE;
    }
    while (list->steps[list->index] != 0) {
        list->state = ((StepRun *) virtual_slot(list, 2))(list, list->steps[list->index]);
        if (list->state != STEPS_DONE) {
            break;
        }
        list->index++;
        list->step_state = 0;
        if (!all) {
            break;
        }
    }
    return list->state;
}
CLEAN_AS(func_020eeb04, StepList_Run)

/* func_020eebb4: the steps done undone in reverse order (vtable slot 3); `index` ends at -1. */
void StepList_Undo(StepList *list)
{
    if (list->steps == NULL || list->state == STEPS_NOT_STARTED) {
        return;
    }
    for (list->index--; list->index >= 0; list->index--) {
        ((StepUndo *) virtual_slot(list, 3))(list, list->steps[list->index]);
    }
}
CLEAN_AS(func_020eebb4, StepList_Undo)
