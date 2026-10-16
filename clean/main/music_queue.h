/* A process (vtable 0x020da334, profile 0x020da27c) owning an object of the field's sound and
 * talk state (data_021c526c points to it between its creation and deletion), whose first
 * member is a queue of music requests.
 *
 * The queue holds up to 16 requests kept in increasing order of priority; the request at its
 * head is the one played: when it becomes the head its music is asked of the sound system
 * (through the object at 0x2b4, which calls SoundSys_ChangeMusic) and it is marked current.
 * A request may run out after a number of frames, may be dropped as soon as it is not at the
 * head, and is taken out of the queue once marked done. */
#ifndef CLEAN_MAIN_MUSIC_QUEUE_H
#define CLEAN_MAIN_MUSIC_QUEUE_H

#include "autoload_2/process.h"
#include "types.h"

#define MUSIC_QUEUE_SIZE 16
#define MUSIC_NONE 0xffff

typedef struct MusicRequest {
    s32 priority; /* lower first; 0x25 when cleared */
    u16 music;    /* 0x04: MUSIC_NONE: none */
    u8 unk_06[2];
    s32 unk_08; /* 0x08: handed to the object at 0x2b4 by func_020350a4 */
    s32 unk_0c;
    u8 unk_10;
    u8 head_only;     /* 0x11: done once it is not at the head */
    u8 current;       /* 0x12: the one played */
    u8 done;          /* 0x13: to be taken out */
    u8 music_started; /* 0x14: its music was asked for */
    u8 unk_15[3];
    s32 timer; /* 0x18: frames left when above 0; done when it runs out */
} MusicRequest;

typedef struct MusicQueue {
    MusicRequest requests[MUSIC_QUEUE_SIZE];
    s32 count; /* 0x1c0 */
} MusicQueue;

/* The object at data_021c526c. */
typedef struct Obj021c526c {
    MusicQueue queue;
    u8 unk_1c4[0x88]; /* worked by the field actor (func_02036448 and the like) */
    u8 unk_24c[0x18];
    u8 unk_264[0x3c];
    u8 unk_2a0[0x14];
    u8 music_commands[0x1c]; /* 0x2b4: what the sound system is asked next frame */
    u8 unk_2d0[0x14];
    u8 unk_2e4[0x0c];
    u8 unk_2f0[0x04];
    u8 unk_2f4;
    u8 unk_2f5[3];
} Obj021c526c;

typedef struct Process020da334 {
    Process base;
    Obj021c526c object; /* 0x50 */
} Process020da334;

int Process020da334_Delete(Process020da334 *self);
int Process020da334_Execute(Process020da334 *self);
int Process020da334_Create(Process020da334 *self);
void *Process020da334_DestructDelete(Process020da334 *self);
void *Process020da334_Destruct(Process020da334 *self);
void *Process020da334_Construct(Process020da334 *self);
void Process020da334_New(void);
void Obj021c526c_EndUpdate(Obj021c526c *self);
void Obj021c526c_ApplyChange24c(Obj021c526c *self);
void MusicQueue_ForEach(MusicQueue *queue, MemberFn fn);
void MusicQueue_OpenAt(MusicQueue *queue, int index);
MusicRequest *MusicQueue_FirstNotDone(MusicRequest *requests, int count);
int MusicQueue_FindMusic(const MusicQueue *queue, u16 music);
int MusicQueue_FindPriority(const MusicQueue *queue, int priority);
int MusicQueue_FindCurrent(const MusicQueue *queue);
int MusicQueue_InsertIndex(const MusicQueue *queue, const MusicRequest *request);
void MusicQueue_Tick(MusicQueue *queue);
void MusicQueue_StartHead(Obj021c526c *self);
void MusicRequest_ClearCurrent(MusicRequest *request);

#endif
