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

/* The member at 0x2d0 (vtable data_020da2d4): a delay counted down each frame; when it runs
 * out a timer is set, and when that runs out the request of priority 7 is dropped. Its flags
 * are set by the field's events (func_0204141c, func_020414e0, Music2e4_PlayMusic41) and read
 * by the sound scene (func_020046c4) and Music2d0_Finish. */
typedef struct Music2d0 {
    const u32 *vtable;
    Obj021c526c *owner;
    u8 unk_08;
    u8 unk_09; /* the tracks are faded in for the scene change when it is cleared */
    u8 unk_0a;
    u8 unk_0b; /* 2 becomes 3 in Music2d0_Mark08Unless */
    s32 delay; /* 0x0c: frames left when above 0; below 0: chosen by Music2d0_Finish */
    s32 timer; /* 0x10: frames left when above 0 */
} Music2d0;

/* The member at 0x2e4 (vtable data_020da2b4): a music it asked for and whether it holds a
 * request of priority 10, both dropped when it is released. */
typedef struct Music2e4 {
    const u32 *vtable;
    Obj021c526c *owner;
    u16 music; /* 0x08: MUSIC_NONE: none */
    u8 active; /* 0x0a: a request of priority 10 was made */
    u8 unk_0b;
} Music2e4;

/* The member at 0x2f0 (vtable data_020da314): only a vtable. */
typedef struct Music2f0 {
    const u32 *vtable;
} Music2f0;

void MusicQueue_RemoveDone(MusicQueue *queue);
void Obj021c526c_SendRequestValue(Obj021c526c *self);
void Obj021c526c_UpdateQueue(Obj021c526c *self);
void MusicQueue_DropMusic(MusicQueue *queue, u16 music, int unused);
void MusicQueue_DropPriority(MusicQueue *queue, int priority);
void MusicQueue_Add(MusicQueue *queue, const MusicRequest *request);
MusicRequest *Music_CurrentRequest(void);
void Music_OnSceneEnd(void);
void Music_OnSceneStart(void);
void Music_Reset(void);
void Obj021c526c_Execute(Obj021c526c *self);
void Obj021c526c_Delete(Obj021c526c *self);
void Obj021c526c_Create(Obj021c526c *self);
void *Obj021c526c_Destruct(Obj021c526c *self);
Obj021c526c *Obj021c526c_Construct(Obj021c526c *self);
void Music_Set2f4(void);
void Music_Clear2f4(void);
u16 Music_CurrentMusic(void);
void Music_DropMusicFlagged(int music);
void Music_DropPriority(int priority);
void Music_DropMusic(int music);
void Music_AddHeadOnly(int priority, int music);
void Music_AddValue(int priority, int value, int frames);
void Music_Add(int priority, int music, int unk_0c, int unk_10);
void Music2f0_ApplyMode(Music2f0 *self);
void Music2f0_SetTracksForScene(void);
void Music2f0_Update(Music2f0 *self);
void Music2f0_OnMusic(Music2f0 *self, int music);
void Music2f0_FadeInForScene22(Music2f0 *self);
void Music2f0_SetTracksForScene22(Music2f0 *self);
void Music_FadeInForSceneChange(void);
void Music_SetTracksForSceneChange(void);
void *Music2f0_DestructDelete(Music2f0 *self);
void Music2f0_Destruct(Music2f0 *self);
void Music2f0_Construct(Music2f0 *self);
void Music2e4_Release(Music2e4 *self);
void Music2e4_Execute(Music2e4 *self);
void Music2e4_Delete(Music2e4 *self);
void Music2e4_Create(Music2e4 *self);
void Music2e4_End(Music2e4 *self);
void Music2e4_Begin(Music2e4 *self);
void Music2e4_PlayMusic41(Music2e4 *self);
Music2d0 *Music_Object2d0(void);
void *Music2e4_DestructDelete(Music2e4 *self);
void Music2e4_Destruct(Music2e4 *self);
void Music2e4_Construct(Music2e4 *self, Obj021c526c *owner);
void Music2d0_Tick(Music2d0 *self);
int Music2d0_Is0bSet(const Music2d0 *self);
int Music2d0_AnyFlag(const Music2d0 *self);
void Music2d0_Set0a(Music2d0 *self);
void Music2d0_SetDelay(Music2d0 *self, u8 index);
void Music2d0_Mark08Unless(Music2d0 *self, int a, int b);
void Music2d0_Mark08And0b(Music2d0 *self, int x, int y);
void Music2d0_Reset(Music2d0 *self);
void Music2d0_Execute(Music2d0 *self);
void Music2d0_Delete(Music2d0 *self);
void Music2d0_Create(Music2d0 *self);
void Music2d0_Finish(Music2d0 *self);
void *Music_Object2a0(void);
void *Music_Object264(void);

Music2f0 *Music_Object2f0(void);
void Music2d0_Start(Music2d0 *self);
void *Music2d0_DestructDelete(Music2d0 *self);
void Music2d0_Destruct(Music2d0 *self);
void Music2d0_Construct(Music2d0 *self, Obj021c526c *owner);

#endif
