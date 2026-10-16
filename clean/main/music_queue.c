/* The process owning the field's sound and talk object, and its queue of music requests
 * (music_queue.h). */
#include "music_queue.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(sizeof(Process) == 0x50, "process size");
static_assert(sizeof(MusicRequest) == 0x1c, "request size");
static_assert(offsetof(MusicRequest, done) == 0x13, "request done");
static_assert(offsetof(MusicRequest, timer) == 0x18, "request timer");
static_assert(offsetof(MusicQueue, count) == 0x1c0, "queue count");
static_assert(offsetof(Obj021c526c, unk_24c) == 0x24c, "object 0x24c");
static_assert(offsetof(Obj021c526c, music_commands) == 0x2b4, "object 0x2b4");
static_assert(offsetof(Obj021c526c, unk_2f4) == 0x2f4, "object 0x2f4");
static_assert(sizeof(Process020da334) == 0x348, "process 0x020da334 size");

/* The class's vtable and the scene objects' root vtable. */
extern const u32 data_020da334[];
extern const u32 data_020da13c[];
/* MusicRequest_ClearCurrent as a member function pointer. */
extern const MemberFn data_020da26c;

/* The object's own: delete, execute, create, destructor, constructor. */
extern void func_0203539c(Obj021c526c *object);
extern void func_02035344(Obj021c526c *object);
extern void func_02035404(Obj021c526c *object);
extern void *func_02035494(Obj021c526c *object);
extern void *func_02035510(Obj021c526c *object);
/* The member at 0x24c: whether its bytes 0x07 and 0x13 differ, and whether its words 0x00 and
 * 0x0c do. */
extern int func_0203735c(void *member);
extern int func_0203734c(void *member);
/* A value of the current scene's table entry (data_020d2150) when the conditions on the
 * player's actor hold; func_020b6674 for the current scene; the byte data_021f4b18. */
extern int func_020b6840(int arg);
extern int func_020b6660(void);
extern u8 func_020b22b8(void);
/* The sound set at data_021cfbcc told again, and a delay of 0x190 or 0x14 frames set. */
extern void func_0206e9bc(int changed);
/* A request copied over another (clearing it first), and its timer counted down (whether it
 * ran out). */
extern void func_02037470(MusicRequest *to, const MusicRequest *from);
extern int func_02037458(MusicRequest *request);
/* The music asked of the sound system next frame. */
extern void func_02035fec(void *commands, int music);

/* ---- The process */

/* func_02034cec: vtable slot 3, the deletion. */
int Process020da334_Delete(Process020da334 *self)
{
    func_0203539c(&self->object);
    return 1;
}
CLEAN_AS(func_02034cec, Process020da334_Delete)

/* func_02034d00: vtable slot 6, the frame's work. */
int Process020da334_Execute(Process020da334 *self)
{
    func_02035344(&self->object);
    return 1;
}
CLEAN_AS(func_02034d00, Process020da334_Execute)

/* func_02034d14: vtable slot 0, the creation. */
int Process020da334_Create(Process020da334 *self)
{
    func_02035404(&self->object);
    return 1;
}
CLEAN_AS(func_02034d14, Process020da334_Create)

/* func_02034d28: the destructor that also frees the process. */
void *Process020da334_DestructDelete(Process020da334 *self)
{
    self->base.vtable = data_020da334;
    func_02035494(&self->object);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_02034d28, Process020da334_DestructDelete)

/* func_02034d58: the destructor. */
void *Process020da334_Destruct(Process020da334 *self)
{
    self->base.vtable = data_020da334;
    func_02035494(&self->object);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_02034d58, Process020da334_Destruct)

/* func_02034d84: the constructor. */
void *Process020da334_Construct(Process020da334 *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_020da334;
    func_02035510(&self->object);
    return self;
}
CLEAN_AS(func_02034d84, Process020da334_Construct)

/* func_02034dac: the profile's creation function: a new process from the auxiliary heap,
 * nothing when that fails.
 * QUIRK: the ROM's code leaves the new process (or NULL) in r0 for its caller; the matching
 * source declares no result, and so does this. */
void Process020da334_New(void)
{
    Process020da334 *self = Heap_AllocAuxZeroed(sizeof(Process020da334));

    if (self != NULL) {
        Process020da334_Construct(self);
    }
}
CLEAN_AS(func_02034dac, Process020da334_New)

/* ---- The object */

/* func_02034dc8: the last step of the object's frame (func_02035344); nothing to do. */
void Obj021c526c_EndUpdate(Obj021c526c *self)
{
    (void) self;
}
CLEAN_AS(func_02034dc8, Obj021c526c_EndUpdate)

/* func_02034dcc: when the member at 0x24c has changed, func_0206e9bc is told whether its
 * words 0x00 and 0x0c differ, unless func_020b6840(1) answers 0, func_020b6660 and
 * func_020b22b8 both answer not 0, or the byte at 0x2f4 is set. The three checks are all made
 * whatever the first ones answer. */
void Obj021c526c_ApplyChange24c(Obj021c526c *self)
{
    int apply = 1;

    if (func_0203735c(self->unk_24c) == 0) {
        return;
    }
    if (func_020b6840(1) == 0) {
        apply = 0;
    }
    if (func_020b6660() != 0 && func_020b22b8() != 0) {
        apply = 0;
    }
    if (self->unk_2f4 != 0) {
        apply = 0;
    }
    if (apply) {
        func_0206e9bc(func_0203734c(self->unk_24c));
    }
}
CLEAN_AS(func_02034dcc, Obj021c526c_ApplyChange24c)

/* ---- The queue */

/* func_02034e28: `fn` called on each request (the count is read again after each call). For
 * a virtual one the request's first word is its vtable. */
void MusicQueue_ForEach(MusicQueue *queue, MemberFn fn)
{
    int i;

    for (i = 0; i < queue->count; i++) {
        uintptr_t self = (uintptr_t) &queue->requests[i] + (uintptr_t) (intptr_t) ((fn.adj - (fn.adj & 1)) / 2);
        uintptr_t code = fn.ptr;
        if ((fn.adj & 1) != 0) {
            code = *(const u32 *) (*(const u32 *) self + fn.ptr);
        }
        ((void (*)(void *)) code)((void *) self);
    }
}
CLEAN_AS(func_02034e28, MusicQueue_ForEach)

/* func_02034e78: room made at `index`: the requests from there on moved one place down (from
 * the last), and the count one more.
 * REQUIRES: count < 16 (MusicQueue_InsertIndex answers -1 otherwise). */
void MusicQueue_OpenAt(MusicQueue *queue, int index)
{
    int count = queue->count;
    int i;

    if (count > 0) {
        for (i = count - 1; i >= index; i--) {
            func_02037470(&queue->requests[i + 1], &queue->requests[i]);
        }
    }
    queue->count++;
}
CLEAN_AS(func_02034e78, MusicQueue_OpenAt)

/* func_02034ebc: the first of the `count` requests not done, NULL when there is none. */
MusicRequest *MusicQueue_FirstNotDone(MusicRequest *requests, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (requests[i].done == 0) {
            return &requests[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_02034ebc, MusicQueue_FirstNotDone)

/* func_02034ee4: the index of the first request for `music`, -1 when there is none. */
int MusicQueue_FindMusic(const MusicQueue *queue, u16 music)
{
    int i;

    for (i = 0; i < queue->count; i++) {
        if (queue->requests[i].music == music) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02034ee4, MusicQueue_FindMusic)

/* func_02034f14: the index of the first request of `priority`, -1 when there is none. */
int MusicQueue_FindPriority(const MusicQueue *queue, int priority)
{
    int i;

    for (i = 0; i < queue->count; i++) {
        if (queue->requests[i].priority == priority) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02034f14, MusicQueue_FindPriority)

/* func_02034f44: the index of the current request, -1 when there is none. */
int MusicQueue_FindCurrent(const MusicQueue *queue)
{
    int i;

    for (i = 0; i < queue->count; i++) {
        if (queue->requests[i].current != 0) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02034f44, MusicQueue_FindCurrent)

/* func_02034f78: where `request` goes: before the first request of a higher priority, else at
 * the end; -1 when the queue is full. */
int MusicQueue_InsertIndex(const MusicQueue *queue, const MusicRequest *request)
{
    int count = queue->count;
    int i;

    if (count >= MUSIC_QUEUE_SIZE) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        if (queue->requests[i].priority > request->priority) {
            break;
        }
    }
    return i;
}
CLEAN_AS(func_02034f78, MusicQueue_InsertIndex)

/* func_02034fac: a frame on: a request whose timer runs out is done, and so is one past the
 * head that is only for the head. */
void MusicQueue_Tick(MusicQueue *queue)
{
    int count = queue->count;
    int i;

    for (i = 0; i < count; i++) {
        MusicRequest *request = &queue->requests[i];
        if (func_02037458(request) != 0) {
            request->done = 1;
        }
        if (i != 0 && request->head_only != 0) {
            request->done = 1;
        }
    }
}
CLEAN_AS(func_02034fac, MusicQueue_Tick)

/* func_02034fec: the head made current when it is not yet: its music asked for (when it has
 * one), every request's current mark cleared, then the head's set. */
void MusicQueue_StartHead(Obj021c526c *self)
{
    MusicRequest *head = &self->queue.requests[0];

    if (self->queue.count <= 0 || head->current != 0) {
        return;
    }
    if (head->music != MUSIC_NONE) {
        func_02035fec(self->music_commands, head->music);
        head->music_started = 1;
    }
    MusicQueue_ForEach(&self->queue, data_020da26c);
    head->current = 1;
}
CLEAN_AS(func_02034fec, MusicQueue_StartHead)

/* func_02035038: called on each request through data_020da26c. */
void MusicRequest_ClearCurrent(MusicRequest *request)
{
    request->current = 0;
}
CLEAN_AS(func_02035038, MusicRequest_ClearCurrent)
