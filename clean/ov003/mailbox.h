/* The mailbox in front of the player's house, a scene object of overlay 3 (class
 * Obj_ov003_0223948c, vtable 0x0223948c, receiver part 0x02239550, 0x2f8 bytes; profile 0x24,
 * code 0x501d, made by the house: player_house.h). It counts the player's filled entries of the
 * ten 0x100-byte entries of the player's block at data_021ef8ec (func_ov003_0221e6ac), and opens
 * group 9 in mode 0x27; that it holds the player's letters is read from this. It is derived
 * from overlay 9's scene actor (Obj_ov009_022658dc), which runs the rest.
 *
 * Its model plays two joint animations, A (overlay 9's first animation file, vtable slot 0x64)
 * and B (the second, slot 0x68), and a texture pattern animation (overlay 9's animation file 0)
 * on the model's render object. Its mode (overlay 9's byte at 0x134) runs through two tables of
 * member pointers (ov004/member_pointer.h); "moves on" below is func_020b2800, which sets a
 * mode through vtable slot 0x6c and tells the others in a wireless session. A mode moves on
 * only while the byte at 0x2f4 is set and once A or B is at its end. A joint animation plays in
 * mode 1 from its first frame, or in mode 3 from its last frame (backwards, by all signs):
 *
 *   0 empty:    A from its start, the pattern in mode 1; moves to 1 once there are letters.
 *   1 arriving: A from its start, then 2.
 *   2 full:     A held at its last frame, the pattern in mode 0.
 *   3 opening:  B from its start with sound 0x819, then 4.
 *   4 open:     B held at its last frame.
 *   5 closing:  B from its last frame in mode 3 with sound 0x81a, then 2 while there are letters,
 *               else 6.
 *   6 emptying: A from its last frame in mode 3 with sound 0x81b, then 0.
 *
 * In every mode, the pattern at its frame 18 plays sound 0x7de. Its other machine (the word at
 * 0x2b4, five states) is run by func_ov003_0221e4e8; entering its state 4 moves the mode on to
 * closing (func_ov003_0221e424). */
#ifndef CLEAN_OV003_MAILBOX_H
#define CLEAN_OV003_MAILBOX_H

#include "types.h"

enum MailboxMode {
    MAILBOX_EMPTY,
    MAILBOX_ARRIVING,
    MAILBOX_FULL,
    MAILBOX_OPENING,
    MAILBOX_OPEN,
    MAILBOX_CLOSING,
    MAILBOX_EMPTYING,
    MAILBOX_MODES
};

/* An animation of main (Obj_020dd154, 0x20 bytes; destructor func_020565b0, constructor
 * func_020565c8): `frame` is copied to `target` once it is bound to a model. */
typedef struct MailboxAnim {
    const void *vtable;
    u8 unk_04[4];
    u32 frame; /* in 20.12 fixed point */
    u8 unk_0C[0xc];
    u32 *target;
    u32 unk_1C;
} MailboxAnim;

/* A joint animation file: its number of frames. */
typedef struct MailboxAnimFile {
    u32 tag;
    u16 frames;
} MailboxAnimFile;

typedef struct Mailbox {
    const void *vtable; /* data_ov003_0223948c */
    u8 unk_04[0xec - 0x04];
    const void *receiver_vtable; /* data_ov003_02239550 */
    u8 unk_F0[0x134 - 0xf0];
    u8 mode; /* enum MailboxMode */
    u8 unk_135;
    u16 code; /* the special character's code main keeps the mode under */
    u8 unk_138[0x13c - 0x138];
    /* Overlay 9's model object (Obj_020dd05c), and the frame control of its joint animation,
     * its part at 0x9c. */
    u8 model_object[0x1d8 - 0x13c];
    u8 model_frames[0x238 - 0x1d8];
    u8 sound[0x2b4 - 0x238]; /* overlay 9's sound source: func_ov009_02262ef0 plays on it */
    int state;               /* the other machine's (func_ov003_0221e4e8) */
    MailboxAnim pattern;     /* the texture pattern animation */
    u8 unk_2D8[0x2f4 - 0x2d8];
    u8 moves_on; /* nonzero: the modes move on (func_ov003_0221e6a0) */
    u8 unk_2F5[3];
} Mailbox;

void Mailbox_RunClose(Mailbox *mailbox);
int Mailbox_SetMode(Mailbox *mailbox, unsigned int mode);
void Mailbox_RunMode(Mailbox *mailbox);
int Mailbox_EnterEmpty(Mailbox *mailbox);
void Mailbox_RunEmpty(Mailbox *mailbox);
int Mailbox_EnterArriving(Mailbox *mailbox);
void Mailbox_RunArriving(Mailbox *mailbox);
int Mailbox_EnterFull(Mailbox *mailbox);
void Mailbox_RunFull(Mailbox *mailbox);
int Mailbox_EnterOpening(Mailbox *mailbox);
void Mailbox_RunOpening(Mailbox *mailbox);
int Mailbox_EnterOpen(Mailbox *mailbox);
void Mailbox_RunOpen(Mailbox *mailbox);
int Mailbox_EnterClosing(Mailbox *mailbox);
void Mailbox_RunClosing(Mailbox *mailbox);
int Mailbox_EnterEmptying(Mailbox *mailbox);
void Mailbox_RunEmptying(Mailbox *mailbox);

#endif
