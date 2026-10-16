/* The activity process (class vtable data_020e3ae8; created by func_020a503c, which makes it
 * the current activity, data_021f3c3c): it saves the state block to the card and runs the
 * exchanges of a linked session, each as a numbered step state, and talks to the player
 * through a message receiver of its own (vtable data_020e3b38) in talk 0 (func_020a1954).
 * Its layout past the receiver is only partly known. */
#ifndef CLEAN_MAIN_ACTIVITY_H
#define CLEAN_MAIN_ACTIVITY_H

#include "autoload_2/process.h"
#include "session.h"
#include "types.h"

#define ACTIVITY_SLOTS 4

struct TownPackBuffer;
struct TownPackThread;

typedef struct Activity {
    Process process;
    u32 unk_50;
    u8 receiver[0x4c];                  /* 0x54: its message receiver (func_020a256c destructs it) */
    u8 unk_a0;                          /* 0xa0 */
    u8 state;                           /* 0xa1: the step of the current exchange */
    u8 unk_a2[0xb8 - 0xa2];             /* 0xa2 */
    u8 *block_copy;                     /* 0xb8: room for a copy of the state block (0x173fc bytes) */
    u8 unk_bc[4];                       /* 0xbc */
    u8 *exchange_block;                 /* 0xc0: an exchange block (0x950 bytes) for data_021ee418 */
    u8 *letters;                        /* 0xc4: the block of letters kept (letter_store.h) */
    struct TownPackBuffer *pack_buffer; /* 0xc8: town_pack.h */
    struct TownPackThread *pack_thread; /* 0xcc: town_pack.h */
    u8 unk_d0[4];                       /* 0xd0 */
    u16 slot_mask;                      /* 0xd4: set by system packet 0 (func_020a1284) */
    u8 byte_d6;                         /* 0xd6 */
    u8 byte_d7;                         /* 0xd7: set by system packet 0 (func_020a127c) */
    u8 unk_d8;                          /* 0xd8 */
    u8 flag_d9;                         /* 0xd9: set by system packet 9 */
    u8 flag_da;                         /* 0xda: set by system packet 10 */
    u8 unk_db;                          /* 0xdb */
    u8 date_time[8];                    /* 0xdc: the DateTime of system packet 10 */
    u8 flag_e4;                         /* 0xe4: set by system packet 11 */
    u8 flag_e5;                         /* 0xe5: set by system packet 18 */
    u8 flag_e6;                         /* 0xe6: set by a session message (func_020a1264) */
    u8 slot_e7[ACTIVITY_SLOTS];         /* 0xe7: set for a slot by a session message */
    u8 slot_eb[ACTIVITY_SLOTS];         /* 0xeb: set for a slot by a session message */
    u8 slot_answer[ACTIVITY_SLOTS];     /* 0xef: the byte a slot sent in system packet 14 */
    u8 flag_f3;                         /* 0xf3: set by a session message (func_020a1210) */
    u8 slot_ack[ACTIVITY_SLOTS];        /* 0xf4: set for a slot by system packet 19 or a message */
    u8 slot_reported[ACTIVITY_SLOTS];   /* 0xf8: set for a slot by system packet 16 (func_020a1200) */
    u8 slot_fc[ACTIVITY_SLOTS];         /* 0xfc: set for a slot by system packet 17 */
    u8 slot_100;                        /* 0x100: the slot that sent system packet 20; 4 for none */
    u8 flag_101;                        /* 0x101: set by system packet 23 */
    u8 byte_102;                        /* 0x102: func_020a245c */
    u8 block_source[ACTIVITY_SLOTS];    /* 0x103: the slot whose exchange block each slot gets; 4 for none */
    u8 slot_107[ACTIVITY_SLOTS];        /* 0x107: func_020a242c */
    u8 unk_10b[3];                      /* 0x10b */
    u8 card_parts;                      /* 0x10e: the card part read (bits 0-3) and written (bits 4-7) */
} Activity;

Activity *Activity_Destruct(Activity *activity);
Activity *Activity_DestructFree(Activity *activity);
void Activity_TalkSequence2(Activity *activity);
void Activity_TalkGatekeeper(Activity *activity, int quiet);
void Activity_StepSendReport(Activity *activity, u8 *step, int first);
int Activity_AllPeersReported(Activity *activity);
void Activity_StepRequestMode1(Activity *activity, u8 *step, int first, int scene_a, int scene_b);

/* activity_fields.c: the fields of an activity, and of the current one (data_021f3c3c). */
Activity *Activity_Current(void);
struct TownPackThread *Activity_CurrentPackThread(void);
struct TownPackBuffer *Activity_CurrentPackBuffer(void);
u8 *Activity_CurrentLetters(void);
int Activity_CurrentByteD6(void);
int Activity_CurrentSlot100(void);
void Activity_SetCurrentSlot100(u8 slot);
void Activity_SetCurrentFlagF3(u8 value);
void Activity_SetFlag101(Activity *activity, u8 value);
void Activity_SetSlotFC(Activity *activity, int slot, int value);
void Activity_SetSlotReported(Activity *activity, int slot, int value);
void Activity_SetSlotAck(Activity *activity, int slot, int value);
void Activity_ClearAnswers(Activity *activity);
void Activity_SetSlotAnswer(Activity *activity, int slot, int value);
void Activity_SetSlotEB(Activity *activity, int slot, int value);
void Activity_SetSlotE7(Activity *activity, int slot, int value);
u8 *Activity_DateTime(Activity *activity);
void Activity_SetFlagDA(Activity *activity, u8 value);
void Activity_SetFlagD9(Activity *activity, u8 value);
void Activity_SetFlagE6(Activity *activity, u8 value);
void Activity_SetFlagE5(Activity *activity, u8 value);
void Activity_SetFlagE4(Activity *activity, u8 value);
void Activity_SetByteD7(Activity *activity, u8 value);
void Activity_SetSlotMask(Activity *activity, u16 mask);

#endif
