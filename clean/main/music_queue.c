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

/* ---- The object's members at 0x2d0, 0x2e4 and 0x2f0, and the calls made on the object
 * through data_021c526c */

#include "sound.h"

static_assert(sizeof(Music2d0) == 0x14, "member 0x2d0 size");
static_assert(offsetof(Music2d0, delay) == 0x0c, "member 0x2d0 delay");
static_assert(sizeof(Music2e4) == 0x0c, "member 0x2e4 size");
static_assert(offsetof(Music2e4, active) == 0x0a, "member 0x2e4 active");
static_assert(offsetof(Obj021c526c, unk_2d0) == 0x2d0, "object 0x2d0");
static_assert(offsetof(Obj021c526c, unk_2e4) == 0x2e4, "object 0x2e4");
static_assert(offsetof(Obj021c526c, unk_2f0) == 0x2f0, "object 0x2f0");

#define ITEM_NONE 0xfff1 /* no item */
#define PLAYER_ACTOR 4   /* the player's field actor (func_02096718(4)) */

/* The object of the running process 0x020da334, NULL when there is none. */
extern Obj021c526c *data_021c526c;
/* 0 or 1: which of the members at 0x264 and 0x2a0 the scene's start and end are told of. */
extern u8 data_020e54a8;
/* Frames of delay for the member at 0x2d0, by index. */
extern const u8 data_020c9f14[];
/* An object whose halfword at 0x0c is 5 while Music2d0_Finish does nothing. */
typedef struct Obj021f42f4 {
    u8 unk_00[0x0c];
    u16 unk_0c;
} Obj021f42f4;
extern Obj021f42f4 *data_021f42f4;

/* The vtables of the members at 0x2e4 and 0x2f0. */
extern const u32 data_020da2b4[];
extern const u32 data_020da314[];

/* A request reset (priority 0x25, no music, all else 0; bytes 0x15-0x17 are left), its
 * destructor (nothing) and default constructor (the reset), and a request made of a priority,
 * a music, the words 0x0c and 0x08 and the byte 0x10. */
extern void func_020374ac(MusicRequest *request);
extern void func_020374cc(void *request);
extern void *func_020374fc(void *request);
extern MusicRequest *func_020374d0(MusicRequest *request, int priority, int music, int unk_0c, int unk_08, int unk_10);
/* The member at 0x2b4: the word handed next frame to SoundSys_Call020f1c00 set, what it asks
 * of the sound system done, its fields cleared, constructed, destructed. */
extern void func_02035fe4(void *commands, int value);
extern void func_02035f6c(void *commands);
extern void func_02035fc0(void *commands);
extern void *func_02035ff8(void *commands, Obj021c526c *owner);
extern void func_02035ff4(void *commands);
/* The member at 0x1c4: frame, reset, delete, create, construct, destruct. */
extern void func_020364c0(void *member);
extern void func_02036490(void *member);
extern void func_020364e8(void *member);
extern void func_020364ec(void *member);
extern void *func_0203652c(void *member, Obj021c526c *owner);
extern void *func_02036510(void *member);
/* The member at 0x24c: the same. */
extern void func_02037430(void *member);
extern void func_0203741c(void *member);
extern void func_02037438(void *member);
extern void func_0203743c(void *member);
extern void func_02037454(void *member);
extern void func_02037450(void *member);
/* The member at 0x264: the same, what the scene's end and start tell it, and a value handed
 * to its three parts. */
extern void func_02036940(void *member);
extern void func_02036920(void *member);
extern void func_02036960(void *member);
extern void func_02036980(void *member);
extern void *func_020369fc(void *member, Obj021c526c *owner);
extern void *func_020369d0(void *member);
extern void func_020368c0(void *member);
extern void func_020368f0(void *member);
extern void func_02036894(void *member, void *value);
/* The member at 0x2a0: the same, and its byte 0x10 set. */
extern void func_0203680c(void *member);
extern void func_020367ec(void *member);
extern void func_02036828(void *member);
extern void func_02036830(void *member);
extern void func_02036870(void *member, Obj021c526c *owner);
extern void func_02036864(void *member);
extern void func_02036788(void *member);
extern void func_020367cc(void *member);
extern void func_02036784(void *member, int value);
/* The member at 0x2d0: construct and destruct. */
extern void func_02035f50(Music2d0 *member, Obj021c526c *owner);
extern void func_02035f44(Music2d0 *member);
/* The address of the member at 0x2f0. */
extern int func_02035e7c(void);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* The current scene, the one before it, and whether the current scene is 0x31. */
extern u8 func_020b65c4(void);
extern u8 func_020b65b8(void);
extern int func_020b6640(void);
/* The scene table at data_021f69d0 and its first byte: the scene being gone to. */
extern void *func_020b5e10(void);
extern int func_020b5e84(u8 *table);
/* A kind (word 0x34 of data_021f8ab0) and its two words 0x24 and 0x28. */
extern int func_020ba4b8(void);
extern void func_020ba4c4(s32 *out0, s32 *out1);
/* The item held by a field actor (ITEM_NONE without one); whether an item code converts, and
 * the conversion. */
extern void func_02095764(u16 *item, int actor);
extern int func_0204bcdc(u16 *item);
extern int func_0204bc64(u16 *item);
/* The player's field actor's state (word 0x7f0, else bits 22-29 of word 0x08; 0x93 without
 * an actor). */
extern int func_02095f90(void);

static Music2d0 *member_2d0(Obj021c526c *self)
{
    return (Music2d0 *) (void *) self->unk_2d0;
}

static Music2e4 *member_2e4(Obj021c526c *self)
{
    return (Music2e4 *) (void *) self->unk_2e4;
}

static Music2f0 *member_2f0(Obj021c526c *self)
{
    return (Music2f0 *) (void *) self->unk_2f0;
}

/* func_02035040: the requests marked done taken out, from the last one back: those after one
 * are moved up a place, the last place is reset and the count is one less. */
void MusicQueue_RemoveDone(MusicQueue *queue)
{
    int i;

    for (i = queue->count - 1; i >= 0; i--) {
        if (queue->requests[i].done != 0) {
            int last = queue->count - 1;
            int j;
            for (j = i; j < last; j++) {
                func_02037470(&queue->requests[j], &queue->requests[j + 1]);
            }
            func_020374ac(&queue->requests[last]);
            queue->count = last;
        }
    }
}
CLEAN_AS(func_02035040, MusicQueue_RemoveDone)

/* func_020350a4: when the current request has a music, a word 0x08 handed on (to
 * SoundSys_Call020f1c00 next frame): that of the first request ahead of it not done, else its
 * own when it is done. */
void Obj021c526c_SendRequestValue(Obj021c526c *self)
{
    int index = MusicQueue_FindCurrent(&self->queue);
    MusicRequest *current;

    if (index < 0) {
        return;
    }
    current = &self->queue.requests[index];
    if (current->music == MUSIC_NONE) {
        return;
    }
    if (index > 0) {
        MusicRequest *ahead = MusicQueue_FirstNotDone(self->queue.requests, index);
        if (ahead != NULL) {
            func_02035fe4(self->music_commands, ahead->unk_08);
            return;
        }
    }
    if (current->done != 0) {
        func_02035fe4(self->music_commands, current->unk_08);
    }
}
CLEAN_AS(func_020350a4, Obj021c526c_SendRequestValue)

/* func_02035104: the queue's frame: the word handed on, the done requests taken out, the head
 * started, the members at 0x1c4, 0x2b4 and 0x2f0 run, then the timers counted. */
void Obj021c526c_UpdateQueue(Obj021c526c *self)
{
    Obj021c526c_SendRequestValue(self);
    MusicQueue_RemoveDone(&self->queue);
    MusicQueue_StartHead(self);
    func_020364c0(self->unk_1c4);
    func_02035f6c(self->music_commands);
    Music2f0_Update(member_2f0(self));
    MusicQueue_Tick(&self->queue);
}
CLEAN_AS(func_02035104, Obj021c526c_UpdateQueue)

/* func_02035148: the first request for `music` marked done. The third argument is not read. */
void MusicQueue_DropMusic(MusicQueue *queue, u16 music, int unused)
{
    int index = MusicQueue_FindMusic(queue, music);

    (void) unused;
    if (index >= 0 && index < queue->count) {
        queue->requests[index].done = 1;
    }
}
CLEAN_AS(func_02035148, MusicQueue_DropMusic)

/* func_02035170: the first request of `priority` marked done. */
void MusicQueue_DropPriority(MusicQueue *queue, int priority)
{
    int index = MusicQueue_FindPriority(queue, priority);

    if (index >= 0 && index < queue->count) {
        queue->requests[index].done = 1;
    }
}
CLEAN_AS(func_02035170, MusicQueue_DropPriority)

/* func_02035198: a copy of `request` put in its place by priority; nothing when the queue is
 * full. */
void MusicQueue_Add(MusicQueue *queue, const MusicRequest *request)
{
    int index = MusicQueue_InsertIndex(queue, request);

    if (index < 0) {
        return;
    }
    MusicQueue_OpenAt(queue, index);
    func_02037470(&queue->requests[index], request);
}
CLEAN_AS(func_02035198, MusicQueue_Add)

/* func_020351c4: the current request, NULL when there is none. */
MusicRequest *Music_CurrentRequest(void)
{
    int index = MusicQueue_FindCurrent(&data_021c526c->queue);

    return index >= 0 ? &data_021c526c->queue.requests[index] : NULL;
}
CLEAN_AS(func_020351c4, Music_CurrentRequest)

/* func_020351ec: at the end of a scene (func_020b6ae0), the member at 0x264 told when
 * data_020e54a8 is 0, the one at 0x2a0 when it is 1. */
void Music_OnSceneEnd(void)
{
    if (data_020e54a8 == 0) {
        func_020368c0(data_021c526c->unk_264);
    } else if (data_020e54a8 == 1) {
        func_02036788(data_021c526c->unk_2a0);
    }
}
CLEAN_AS(func_020351ec, Music_OnSceneEnd)

/* func_02035240: at the start of a scene (func_020b6d20), the same with their other call. */
void Music_OnSceneStart(void)
{
    if (data_020e54a8 == 0) {
        func_020368f0(data_021c526c->unk_264);
    } else if (data_020e54a8 == 1) {
        func_020367cc(data_021c526c->unk_2a0);
    }
}
CLEAN_AS(func_02035240, Music_OnSceneStart)

/* func_02035294: every member reset, from the last to the first, and the queue emptied. */
void Music_Reset(void)
{
    Obj021c526c *self = data_021c526c;
    int i;

    Music2e4_Release(member_2e4(self));
    Music2d0_Reset(member_2d0(self));
    func_02035fc0(self->music_commands);
    func_020367ec(self->unk_2a0);
    func_02036920(self->unk_264);
    func_0203741c(self->unk_24c);
    func_02036490(self->unk_1c4);
    for (i = 0; i < MUSIC_QUEUE_SIZE; i++) {
        func_020374ac(&self->queue.requests[i]);
    }
    self->queue.count = 0;
    self->unk_2f4 = 0;
}
CLEAN_AS(func_02035294, Music_Reset)

/* func_02035344: the object's frame (Process020da334_Execute). */
void Obj021c526c_Execute(Obj021c526c *self)
{
    Music2e4_Execute(member_2e4(self));
    Music2d0_Execute(member_2d0(self));
    func_02037430(self->unk_24c);
    func_02036940(self->unk_264);
    func_0203680c(self->unk_2a0);
    Obj021c526c_UpdateQueue(self);
    Obj021c526c_ApplyChange24c(self);
    Obj021c526c_EndUpdate(self);
}
CLEAN_AS(func_02035344, Obj021c526c_Execute)

/* func_0203539c: the object's deletion: its members told, then data_021c526c cleared. */
void Obj021c526c_Delete(Obj021c526c *self)
{
    Music2e4_Delete(member_2e4(self));
    Music2d0_Delete(member_2d0(self));
    func_02035fc0(self->music_commands);
    func_02036828(self->unk_2a0);
    func_02036960(self->unk_264);
    func_02037438(self->unk_24c);
    func_020364e8(self->unk_1c4);
    data_021c526c = NULL;
}
CLEAN_AS(func_0203539c, Obj021c526c_Delete)

/* func_02035404: the object's creation: it becomes data_021c526c, its queue is emptied and
 * its members told. */
void Obj021c526c_Create(Obj021c526c *self)
{
    int i;

    data_021c526c = self;
    for (i = 0; i < MUSIC_QUEUE_SIZE; i++) {
        func_020374ac(&self->queue.requests[i]);
    }
    self->queue.count = 0;
    func_020364ec(self->unk_1c4);
    func_0203743c(self->unk_24c);
    func_02036980(self->unk_264);
    func_02036830(self->unk_2a0);
    func_02035fc0(self->music_commands);
    Music2d0_Create(member_2d0(self));
    Music2e4_Create(member_2e4(self));
    self->unk_2f4 = 0;
}
CLEAN_AS(func_02035404, Obj021c526c_Create)

/* func_02035494: the destructor: the members from the last to the first, then the requests
 * (with the game's request destructor). */
void *Obj021c526c_Destruct(Obj021c526c *self)
{
    Music2f0_Destruct(member_2f0(self));
    Music2e4_Destruct(member_2e4(self));
    func_02035f44(member_2d0(self));
    func_02035ff4(self->music_commands);
    func_02036864(self->unk_2a0);
    func_020369d0(self->unk_264);
    func_02037450(self->unk_24c);
    func_02036510(self->unk_1c4);
    __cxa_vec_cleanup(self->queue.requests, MUSIC_QUEUE_SIZE, sizeof(MusicRequest),
                      (void (*)(void *))(uintptr_t) func_020374cc);
    return self;
}
CLEAN_AS(func_02035494, Obj021c526c_Destruct)

/* func_02035510: the constructor: the requests (with the game's request constructor and
 * destructor), then the members, each told its owner where it takes one. */
Obj021c526c *Obj021c526c_Construct(Obj021c526c *self)
{
    __cxa_vec_ctor(self->queue.requests, MUSIC_QUEUE_SIZE, sizeof(MusicRequest), (void (*)(void *))(uintptr_t) func_020374fc,
                   (void (*)(void *))(uintptr_t) func_020374cc);
    self->queue.count = 0;
    func_0203652c(self->unk_1c4, self);
    func_02037454(self->unk_24c);
    func_020369fc(self->unk_264, self);
    func_02036870(self->unk_2a0, self);
    func_02035ff8(self->music_commands, self);
    func_02035f50(member_2d0(self), self);
    Music2e4_Construct(member_2e4(self), self);
    Music2f0_Construct(member_2f0(self));
    self->unk_2f4 = 0;
    return self;
}
CLEAN_AS(func_02035510, Obj021c526c_Construct)

/* func_020355b8: the byte at 0x2f4 set (Obj021c526c_ApplyChange24c then does nothing). */
void Music_Set2f4(void)
{
    data_021c526c->unk_2f4 = 1;
}
CLEAN_AS(func_020355b8, Music_Set2f4)

/* func_020355cc: the byte at 0x2f4 cleared. */
void Music_Clear2f4(void)
{
    data_021c526c->unk_2f4 = 0;
}
CLEAN_AS(func_020355cc, Music_Clear2f4)

/* func_020355e0: the current request's music, MUSIC_NONE when there is none. */
u16 Music_CurrentMusic(void)
{
    int index = MusicQueue_FindCurrent(&data_021c526c->queue);

    return index >= 0 ? data_021c526c->queue.requests[index].music : MUSIC_NONE;
}
CLEAN_AS(func_020355e0, Music_CurrentMusic)

/* func_02035610: the request for `music` dropped (passing 1 as the unread argument).
 * REQUIRES: music fits in 16 bits (the original hands the whole word on). */
void Music_DropMusicFlagged(int music)
{
    MusicQueue_DropMusic(&data_021c526c->queue, (u16) music, 1);
}
CLEAN_AS(func_02035610, Music_DropMusicFlagged)

/* func_02035624: the request of `priority` dropped. */
void Music_DropPriority(int priority)
{
    MusicQueue_DropPriority(&data_021c526c->queue, priority);
}
CLEAN_AS(func_02035624, Music_DropPriority)

/* func_02035638: the request for `music` dropped.
 * REQUIRES: music fits in 16 bits (the original hands the whole word on). */
void Music_DropMusic(int music)
{
    MusicQueue_DropMusic(&data_021c526c->queue, (u16) music, 0);
}
CLEAN_AS(func_02035638, Music_DropMusic)

/* func_0203564c: a request for `music` at `priority` (word 0x0c 0x7f) dropped as soon as it
 * is not at the head. */
void Music_AddHeadOnly(int priority, int music)
{
    MusicRequest request;

    func_020374d0(&request, priority, music, 0x7f, 0, 0);
    request.head_only = 1;
    MusicQueue_Add(&data_021c526c->queue, &request);
    func_020374cc(&request);
}
CLEAN_AS(func_0203564c, Music_AddHeadOnly)

/* func_02035684: a request without music at `priority` with `value` as its word 0x08, running
 * out after `frames` frames when that is above 0. */
void Music_AddValue(int priority, int value, int frames)
{
    MusicRequest request;

    func_020374d0(&request, priority, MUSIC_NONE, 0, value, 0);
    if (frames > 0) {
        request.timer = frames;
    }
    MusicQueue_Add(&data_021c526c->queue, &request);
    func_020374cc(&request);
}
CLEAN_AS(func_02035684, Music_AddValue)

/* func_020356c4: a request for `music` at `priority` with the word 0x0c and the byte 0x10. */
void Music_Add(int priority, int music, int unk_0c, int unk_10)
{
    MusicRequest request;

    func_020374d0(&request, priority, music, unk_0c, 0, unk_10);
    MusicQueue_Add(&data_021c526c->queue, &request);
    func_020374cc(&request);
}
CLEAN_AS(func_020356c4, Music_Add)

/* func_020356fc: the sound system's mode: 0x0c when the kind is 1 and the second word is at
 * least 3, 0x0d when the kind is 2 and it is, else 0x0b. */
void Music2f0_ApplyMode(Music2f0 *self)
{
    int kind = func_020ba4b8();
    s32 first, second;
    int mode = 0x0b;

    (void) self;
    func_020ba4c4(&first, &second);
    if (second >= 3 && kind == 1) {
        mode = 0x0c;
    } else if (second >= 3 && kind == 2) {
        mode = 0x0d;
    }
    SoundSys_SetMode(mode);
}
CLEAN_AS(func_020356fc, Music2f0_ApplyMode)

/* func_02035750: the tracks set for the current scene; none changed in a scene not listed. */
void Music2f0_SetTracksForScene(void)
{
    int set = 0;

    switch (func_020b65c4()) {
        case 0x20:
            set = 6;
            break;
        case 0x23:
        case 0x24:
        case 0x27:
        case 0x28:
            set = 0x0b;
            break;
        case 0x29:
            set = 0x0c;
            break;
        case 0x25:
        case 0x26:
            set = 0x0d;
            break;
        case 0x22:
            set = 0x0e;
            break;
    }
    if (set != 0) {
        SoundSys_SetTracks(set);
    }
}
CLEAN_AS(func_02035750, Music2f0_SetTracksForScene)

/* func_02035800: each frame, in scene 0 or 0x31, the sound system's mode chosen. */
void Music2f0_Update(Music2f0 *self)
{
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        Music2f0_ApplyMode(self);
    }
}
CLEAN_AS(func_02035800, Music2f0_Update)

/* func_02035820: told of each music asked of the sound system (func_02035f6c): for music 0x62
 * the tracks are set for the scene. */
void Music2f0_OnMusic(Music2f0 *self, int music)
{
    (void) self;
    if (music == 0x62) {
        Music2f0_SetTracksForScene();
    }
}
CLEAN_AS(func_02035820, Music2f0_OnMusic)

/* func_02035834: in scene 0x22, track set 5 faded in (from overlay 129). */
void Music2f0_FadeInForScene22(Music2f0 *self)
{
    (void) self;
    if (func_020b65c4() == 0x22) {
        SoundSys_FadeInTracks(5);
    }
}
CLEAN_AS(func_02035834, Music2f0_FadeInForScene22)

/* func_0203584c: in scene 0x22, track set 5 set (from overlay 129). */
void Music2f0_SetTracksForScene22(Music2f0 *self)
{
    (void) self;
    if (func_020b65c4() == 0x22) {
        SoundSys_SetTracks(5);
    }
}
CLEAN_AS(func_0203584c, Music2f0_SetTracksForScene22)

/* The track set for going from scene `from` to scene `to`: 1 into 0x20 from 0x22, 0x23, 0x25,
 * 0x27 or 0x29; 2, 3 or 4 from 0x20 into 0x29, 0x25 or 0x22; else 0. */
static int music_tracks_for_change(int from, int to)
{
    if (to == 0x20 && (from == 0x22 || from == 0x23 || from == 0x25 || from == 0x27 || from == 0x29)) {
        return 1;
    }
    if (from != 0x20) {
        return 0;
    }
    switch (to) {
        case 0x29:
            return 2;
        case 0x25:
            return 3;
        case 0x22:
            return 4;
        default:
            return 0;
    }
}

/* func_02035864: the tracks faded in for the change from the previous scene to the current
 * one. */
void Music_FadeInForSceneChange(void)
{
    int previous = func_020b65b8();
    int current = func_020b65c4();
    int set = music_tracks_for_change(previous, current);

    if (set != 0) {
        SoundSys_FadeInTracks(set);
    }
}
CLEAN_AS(func_02035864, Music_FadeInForSceneChange)

/* func_02035930: the tracks set as the current scene is left for the one being gone to: the
 * same table read the other way round (the scene gone to in the place of the previous one). */
void Music_SetTracksForSceneChange(void)
{
    int current = func_020b65c4();
    int next = func_020b5e84(func_020b5e10());
    int set = music_tracks_for_change(next, current);

    if (set != 0) {
        SoundSys_SetTracks(set);
    }
}
CLEAN_AS(func_02035930, Music_SetTracksForSceneChange)

/* func_02035a00: the member at 0x2f0's destructor that also frees it (vtable slot 1). */
void *Music2f0_DestructDelete(Music2f0 *self)
{
    self->vtable = data_020da314;
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_02035a00, Music2f0_DestructDelete)

/* func_02035a18: its destructor (vtable slot 0). */
void Music2f0_Destruct(Music2f0 *self)
{
    self->vtable = data_020da314;
}
CLEAN_AS(func_02035a18, Music2f0_Destruct)

/* func_02035a24: its constructor. */
void Music2f0_Construct(Music2f0 *self)
{
    self->vtable = data_020da314;
}
CLEAN_AS(func_02035a24, Music2f0_Construct)

/* func_02035a30: the member at 0x2e4's music and request of priority 10 dropped. */
void Music2e4_Release(Music2e4 *self)
{
    if (self->music != MUSIC_NONE) {
        Music_DropMusic(self->music);
        self->music = MUSIC_NONE;
    }
    if (self->active != 0) {
        Music_DropPriority(10);
        self->active = 0;
    }
}
CLEAN_AS(func_02035a30, Music2e4_Release)

/* func_02035a60: its frame: nothing. */
void Music2e4_Execute(Music2e4 *self)
{
    (void) self;
}
CLEAN_AS(func_02035a60, Music2e4_Execute)

/* func_02035a64: its deletion. */
void Music2e4_Delete(Music2e4 *self)
{
    Music2e4_Release(self);
}
CLEAN_AS(func_02035a64, Music2e4_Delete)

/* func_02035a6c: its creation: nothing. */
void Music2e4_Create(Music2e4 *self)
{
    (void) self;
}
CLEAN_AS(func_02035a6c, Music2e4_Create)

/* func_02035a70: like Music2e4_Release (from the field actor), with a request of priority 10
 * and word 5 lasting 5 frames added before the music is dropped, or after the request of
 * priority 10 is. */
void Music2e4_End(Music2e4 *self)
{
    if (self->music != MUSIC_NONE) {
        Music_AddValue(10, 5, 5);
        Music_DropMusic(self->music);
        self->music = MUSIC_NONE;
    }
    if (self->active != 0) {
        Music_DropPriority(10);
        Music_AddValue(10, 5, 5);
        self->active = 0;
    }
}
CLEAN_AS(func_02035a70, Music2e4_End)

/* func_02035ab4: a request of priority 10 with word 0x0f made (field actor states 0x3c and
 * 0x6d). */
void Music2e4_Begin(Music2e4 *self)
{
    self->active = 1;
    Music_AddValue(10, 0x0f, 0);
}
CLEAN_AS(func_02035ab4, Music2e4_Begin)

/* func_02035ac8: music 0x41 asked for at priority 11, and the member at 0x2d0's byte 0x0a
 * set. */
void Music2e4_PlayMusic41(Music2e4 *self)
{
    self->music = 0x41;
    Music_Add(0x0b, 0x41, 0x7f, 1);
    Music2d0_Set0a(Music_Object2d0());
}
CLEAN_AS(func_02035ac8, Music2e4_PlayMusic41)

/* func_02035ae8: the member at 0x2d0 of the object. */
Music2d0 *Music_Object2d0(void)
{
    return member_2d0(data_021c526c);
}
CLEAN_AS(func_02035ae8, Music_Object2d0)

/* func_02035afc: the member at 0x2e4's destructor that also frees it (vtable slot 1). */
void *Music2e4_DestructDelete(Music2e4 *self)
{
    self->vtable = data_020da2b4;
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_02035afc, Music2e4_DestructDelete)

/* func_02035b14: its destructor (vtable slot 0). */
void Music2e4_Destruct(Music2e4 *self)
{
    self->vtable = data_020da2b4;
}
CLEAN_AS(func_02035b14, Music2e4_Destruct)

/* func_02035b20: its constructor. */
void Music2e4_Construct(Music2e4 *self, Obj021c526c *owner)
{
    self->vtable = data_020da2b4;
    self->owner = owner;
    self->music = MUSIC_NONE;
    self->active = 0;
}
CLEAN_AS(func_02035b20, Music2e4_Construct)

/* func_02035b38: the member at 0x2d0's frame. When the delay runs out the timer is set to
 * 0x14 frames while, with data_020e54a8 0 and in scene 0, the player holds an item, else to
 * 1; when the timer runs out the request of priority 7 is dropped. */
void Music2d0_Tick(Music2d0 *self)
{
    if (self->delay > 0) {
        self->delay--;
        if (self->delay <= 0) {
            int frames = 1;
            if (data_020e54a8 == 0 && func_020b6660() != 0) {
                u16 item[2];
                int empty;
                func_02095764(&item[0], PLAYER_ACTOR);
                if (func_0204bcdc(item) != 0) {
                    int held;
                    item[1] = ITEM_NONE;
                    held = func_0204bc64(&item[0]);
                    empty = held == func_0204bc64(&item[1]);
                } else {
                    empty = item[0] == ITEM_NONE;
                }
                if (!empty) {
                    frames = 0x14;
                }
            }
            self->timer = frames;
        }
    }
    if (self->timer > 0) {
        self->timer--;
        if (self->timer <= 0) {
            Music_DropPriority(7);
        }
    }
}
CLEAN_AS(func_02035b38, Music2d0_Tick)

/* func_02035bdc: whether its byte 0x0b is set. */
int Music2d0_Is0bSet(const Music2d0 *self)
{
    return self->unk_0b != 0;
}
CLEAN_AS(func_02035bdc, Music2d0_Is0bSet)

/* func_02035bec: whether any of its bytes 0x08, 0x09 and 0x0a is set (then the sound scene
 * sets data_021fd21c[2]). */
int Music2d0_AnyFlag(const Music2d0 *self)
{
    return self->unk_08 != 0 || self->unk_09 != 0 || self->unk_0a != 0;
}
CLEAN_AS(func_02035bec, Music2d0_AnyFlag)

/* func_02035c08: its byte 0x0a set. */
void Music2d0_Set0a(Music2d0 *self)
{
    self->unk_0a = 1;
}
CLEAN_AS(func_02035c08, Music2d0_Set0a)

/* func_02035c10: its delay taken from the table data_020c9f14 (from overlay 9). */
void Music2d0_SetDelay(Music2d0 *self, u8 index)
{
    self->delay = data_020c9f14[index];
}
CLEAN_AS(func_02035c10, Music2d0_SetDelay)

/* func_02035c1c: (from func_0204141c) a byte 0x0b of 2 becomes 3; otherwise the byte 0x08 is
 * set unless `a` is 2 and `b` is 6. */
void Music2d0_Mark08Unless(Music2d0 *self, int a, int b)
{
    if (self->unk_0b == 2) {
        self->unk_0b = 3;
        return;
    }
    if (!(a == 2 && b == 6)) {
        self->unk_08 = 1;
    }
}
CLEAN_AS(func_02035c1c, Music2d0_Mark08Unless)

/* func_02035c64: (from func_020414e0) the byte 0x08 set unless the event may pass, and the
 * byte 0x0b set outside scene 0 or for `x` 2 with `y` 6. Outside scene 0 it passes; in it the
 * current request decides, "plain" when it is of priority 0x1a or has no music (no current
 * request counts as plain):
 *   x 1: passes for y 6; for y 9 when plain or of priority 0x24 with music 0x2c or 0x2d;
 *        else when plain;
 *   x 2: passes for y 6; not for y 9; else when plain;
 *   x 0: passes when plain; any other x: does not. */
void Music2d0_Mark08And0b(Music2d0 *self, int x, int y)
{
    int pass = 0;
    int mark_0b = 0;

    if (func_020b6660() == 0) {
        pass = 1;
        mark_0b = 1;
    } else {
        MusicRequest *current = Music_CurrentRequest();
        u16 music = current != NULL ? current->music : MUSIC_NONE;
        s32 priority = current != NULL ? current->priority : 0x25;
        int plain = priority == 0x1a || music == MUSIC_NONE;

        if (x == 1) {
            if (y == 6) {
                pass = 1;
            } else if (y == 9) {
                pass = plain || (priority == 0x24 && (music == 0x2c || music == 0x2d));
            } else {
                pass = plain;
            }
        } else if (x == 2) {
            if (y == 6) {
                pass = 1;
                mark_0b = 1;
            } else if (y != 9) {
                pass = plain;
            }
        } else if (x == 0) {
            pass = plain;
        }
    }
    if (!pass) {
        self->unk_08 = 1;
    }
    if (mark_0b) {
        self->unk_0b = 1;
    }
}
CLEAN_AS(func_02035c64, Music2d0_Mark08And0b)

/* func_02035d8c: its flags cleared, and when the delay or the timer is running both are
 * stopped and the request of priority 7 dropped. */
void Music2d0_Reset(Music2d0 *self)
{
    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0a = 0;
    self->unk_0b = 0;
    if (self->delay != 0 || self->timer != 0) {
        Music_DropPriority(7);
        self->delay = 0;
        self->timer = 0;
    }
}
CLEAN_AS(func_02035d8c, Music2d0_Reset)

/* func_02035db8: its frame. */
void Music2d0_Execute(Music2d0 *self)
{
    Music2d0_Tick(self);
}
CLEAN_AS(func_02035db8, Music2d0_Execute)

/* func_02035dc0: its deletion. */
void Music2d0_Delete(Music2d0 *self)
{
    Music2d0_Reset(self);
}
CLEAN_AS(func_02035dc0, Music2d0_Delete)

/* func_02035dc8: its creation: nothing. */
void Music2d0_Create(Music2d0 *self)
{
    (void) self;
}
CLEAN_AS(func_02035dc8, Music2d0_Create)

/* func_02035dcc: (from func_02041c88) unless data_021f42f4's halfword 0x0c is 5: a delay below
 * 0 chosen by the player's state (left for 0x3c; 0x21 for 0x8b, 0x8e, 0x43 and 0x44; 0x19
 * for 2; else 0x14), the tracks faded in for the scene change when byte 0x09 is set, the
 * bytes 0x08-0x0a cleared, and the members at 0x264 and 0x2a0 handed 0.
 * QUIRK: the address of the member at 0x2f0 (func_02035e7c) is asked for and not used. */
void Music2d0_Finish(Music2d0 *self)
{
    if (data_021f42f4->unk_0c == 5) {
        return;
    }
    if (self->delay < 0) {
        switch (func_02095f90()) {
            case 0x3c:
                break;
            case 0x8b:
            case 0x8e:
            case 0x43:
            case 0x44:
                self->delay = 0x21;
                break;
            case 0x02:
                self->delay = 0x19;
                break;
            default:
                self->delay = 0x14;
                break;
        }
    }
    if (self->unk_09 != 0) {
        func_02035e7c();
        Music_FadeInForSceneChange();
    }
    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0a = 0;
    func_02036894(Music_Object264(), NULL);
    func_02036784(Music_Object2a0(), 0);
}
CLEAN_AS(func_02035dcc, Music2d0_Finish)

/* func_02035e54: the member at 0x2a0 of the object. */
void *Music_Object2a0(void)
{
    return data_021c526c->unk_2a0;
}
CLEAN_AS(func_02035e54, Music_Object2a0)

/* func_02035e68: the member at 0x264 of the object. */
void *Music_Object264(void)
{
    return data_021c526c->unk_264;
}
CLEAN_AS(func_02035e68, Music_Object264)
