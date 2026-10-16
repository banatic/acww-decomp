/* The panther of overlay 3 (class Obj_ov003_02238dbc, vtable 0x02238dbc, receiver part
 * 0x02238e80, 0x2b8 bytes), a special character whose message receiver is named
 * "sp_npc_panther"; Katrina the fortune teller is the game's panther, but nothing here names
 * her. It is derived from overlay 9's scene actor (Obj_ov009_022658dc), which runs the rest.
 *
 * Set up (vtable slot 0x70), it keeps the clock's hour. Before a talk (slot 0x78) it names the
 * receiver, picks message 0x12 when both that hour and the hour now are 6 or later (slot 0x8c),
 * else 0xf, and sets the speaker to name 10 of main's list of names (code 0xd00a). */
#ifndef CLEAN_OV003_PANTHER_H
#define CLEAN_OV003_PANTHER_H

#include "types.h"

typedef struct Panther {
    const void *vtable; /* data_ov003_02238dbc */
    u8 unk_04[0xec - 0x04];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_02238e80 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x2b4 - 0x10b];
    u8 hour; /* the hour Panther_KeepHour saw */
    u8 unk_2B5[3];
} Panther;

void Panther_PrepareTalk(Panther *panther);
int Panther_IsAfterSix(Panther *panther);
int Panther_Update(void);
int Panther_KeepHour(Panther *panther);
Panther *Panther_DestroyAndFree(Panther *panther);
Panther *Panther_Destroy(Panther *panther);
Panther *Panther_Construct(Panther *panther);
void Panther_New(void);
Panther *Panther_ReceiverDestroyAndFree(void *receiver);
Panther *Panther_ReceiverDestroy(void *receiver);

#endif
