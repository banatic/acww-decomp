/* The game's processes: C++ objects (base vtable data_0213e7b4) that the main loop runs in five
 * phases a frame, named by the ROM's own strings (Process_PhaseName):
 *
 *   CONNECT  every process in the tree of parents and children, in tree order: deletions
 *            asked for are started and changes of order and of the lists applied (func_01ffd1b4)
 *   CREATE   the processes whose creation is not finished yet, again
 *   EXECUTE  the active processes, by execute order
 *   DELETE   the processes being deleted, until each is gone
 *   DRAW     the active processes, by draw order
 *
 * A process is made from a profile (the table at data_021fd044, by class id) whose constructor
 * reads the spawn's arguments from globals (Process_SetConstructArgs). Each phase calls three
 * virtual functions through func_01ffd44c: a check before (0: not now), the phase's own work
 * (1: done, -1: failed, else: not done yet) and a function told the outcome (ProcessOutcome).
 *
 * A process may own a frame heap its resources go in, and a list of loading steps that must be
 * finished before it can be deleted (StepList). */
#ifndef CLEAN_AUTOLOAD_2_PROCESS_H
#define CLEAN_AUTOLOAD_2_PROCESS_H

#include "heap.h"
#include "links.h"
#include "types.h"

struct Process;

/* The phase the main loop is in (data_0213e7fc). */
enum ProcessPhase {
    PHASE_NULL = 0, /* between phases */
    PHASE_CONNECT = 1,
    PHASE_CREATE = 2,
    PHASE_EXECUTE = 3,
    PHASE_DELETE = 4,
    PHASE_DRAW = 5,
};

/* What a phase's last virtual function is told (func_01ffd44c). */
enum ProcessOutcome {
    OUTCOME_REFUSED = 0, /* the check before said not now */
    OUTCOME_PENDING = 1, /* the work is not done yet */
    OUTCOME_DONE = 2,
    OUTCOME_FAILED = 3,
};

/* A process's state. */
enum ProcessState {
    STATE_CREATING = 0, /* its creation is not finished */
    STATE_ACTIVE = 1,   /* in the execute and draw lists */
    STATE_DELETING = 2, /* in the delete list */
};

/* Flags (Process.flags). An ancestor's flags carry over to the child at its construction and
 * in each CONNECT phase. */
enum ProcessFlags {
    PROCESS_EXECUTE_STOPPED = 1 << 0,       /* set by the game for this process */
    PROCESS_EXECUTE_STOPPED_ABOVE = 1 << 1, /* this one's or an ancestor's: not executed */
    PROCESS_DRAW_STOPPED = 1 << 2,          /* set by the game for this process */
    PROCESS_DRAW_STOPPED_ABOVE = 1 << 3,    /* this one's or an ancestor's: not drawn */
};

/* A C++ pointer to member function (the ARM C++ ABI's): `ptr` is the function, or for a
 * virtual one its offset in the vtable; `adj` is the adjustment of `this` times two, plus 1 for a
 * virtual function. A null one has `ptr` 0. */
typedef struct MemberFn {
    u32 ptr;
    s32 adj;
} MemberFn;

/* A process's place in the tree of parents and children: the links and the process. */
typedef struct ProcessNode {
    TreeNode tree;
    struct Process *owner;
} ProcessNode;

/* A process's place in one of the lists, which are kept sorted by `order` (ProcessList_Insert).
 * A change of order is asked for in `wanted_order` and applied in the CONNECT phase. */
typedef struct ProcessLink {
    ListNode node;
    struct Process *owner;
    u16 order;
    u16 wanted_order;
} ProcessLink;

/* A list of processes and the member function its phase calls for each one. */
typedef struct ProcessList {
    List list;
    MemberFn each;
} ProcessList;

/* The tree of parents and children and the member function the CONNECT phase calls. */
typedef struct ProcessTree {
    Tree tree;
    MemberFn each;
} ProcessTree;

/* A list of loading steps run one after the other (StepList_Run) and undone in reverse when the
 * process is deleted (StepList_Undo). Its vtable has the step's run at slot 2 (the list's new
 * state) and its undo at slot 3. */
typedef struct StepList {
    const u32 *vtable;
    s16 state;        /* StepListState */
    s16 index;        /* the step under way; the number of steps done */
    const int *steps; /* ends with 0 */
    u8 unk_0C[6];
    s16 step_state; /* cleared when a step is done; the steps' own use */
} StepList;

enum StepListState {
    STEPS_NOT_STARTED = 0,
    STEPS_RUNNING = 1,
    STEPS_DONE = 2,
};

/* What a process class is made from (the table data_021fd044, by class id); subclasses' profiles
 * go on with fields of their own. */
typedef struct Profile {
    struct Process *(*create)(void);
    u16 execute_order;
    u16 draw_order;
} Profile;

typedef struct Process {
    const u32 *vtable;
    u32 id;       /* a serial number */
    u32 param;    /* the spawn's parameter */
    u16 class_id; /* its profile's index */
    u8 state;     /* ProcessState */
    u8 delete_requested;
    u8 activate_pending; /* created during the EXECUTE phase: made active in the CONNECT phase */
    u8 create_pending;   /* its creation was left pending during the CREATE phase: listed in the
                          * CONNECT phase */
    u8 unk_12;           /* the spawn's last argument, kept */
    u8 flags;            /* ProcessFlags */
    ProcessNode node;
    ProcessLink link;      /* in the create, execute or delete list */
    ProcessLink draw_link; /* in the draw list */
    StepList *steps;
    Heap *heap;
} Process;

struct Process *Process_SpawnRoot(int class_id, int param, int unk_12);
struct Process *Process_SpawnChild(int class_id, Process *parent, u32 param, u8 unk_12);
void Process_NotifyDeleted(int class_id);
int Process_NotifySpawn(int class_id);
Process *Process_Spawn(int class_id, TreeNode *parent, u32 param, u8 unk_12);
void Process_SetConstructArgs(u16 class_id, TreeNode *parent, u32 param, u8 unk_12);
int Process_IsAnyDescendantCreating(Process *self);
int Process_RunDelete(Process *self);
void Process_RunCreate(Process *self);
void Process_FirstCreate(Process *self);
int Process_FillHeapDefault(Process *self);
int Process_CreateHeap(Process *self, int size, Heap *parent);
int Process_CreateFittedHeap(Process *self, u32 size, Heap *parent);
void Process_SetDrawOrder(Process *self, u16 order);
void Process_SetExecuteOrder(Process *self, u16 order);
Process *Process_GetParent(Process *self);
void Process_RequestDelete(Process *self);
void Process_SetHeap(Process *self, Heap *heap);
void Process_OnDeleteRequested(Process *self);
void Process_AfterDelete(Process *self, int outcome);
int Process_CanDelete(Process *self);
int Process_DeleteDefault(Process *self);
void Process_AfterCreate(Process *self, int outcome);
int Process_CanCreateDefault(void);
int Process_CreateDefault(Process *self);
void Process_Destruct(Process *self);
Process *Process_DestructFree(Process *self);
Process *Process_Construct(Process *self);
ProcessLink *ProcessList_FindClass(List *list, int class_id, ProcessLink *after);
ProcessLink *ProcessList_FindId(List *list, int id);
int ProcessList_ForEach(ProcessList *list);
int ProcessList_Insert(List *list, ProcessLink *link);
void Process_RunFrame(int draw_only);
void Process_RunDrawPhase(void);
void Process_RunAllPhases(void);
const char *Process_PhaseName(u32 phase);
int ProcessTree_ForEach(ProcessTree *tree);
int StepList_IsIdle(StepList *list);
s16 StepList_Run(StepList *list, int all);
void StepList_Undo(StepList *list);

#endif
