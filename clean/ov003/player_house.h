/* The player's house seen from outside, a scene object of overlay 3 (class Obj_ov003_02239254,
 * vtable 0x02239254, receiver part 0x02239318, 0x2bc bytes). It is derived from overlay 9's
 * scene actor (Obj_ov009_022658dc), which runs the rest.
 *
 * Its texture is "/str/plHsTex/home<look><letter>.nsbtx": the look is bits 6 to 9 of the word
 * that follows the five 0x450-byte room records of the house at data_021ebcd4, written as one
 * hexadecimal digit, and the letter is the one overlay 3 picks (func_ov003_022203dc). Set up
 * (slot 0x70), it loads that texture, binds it to its model, and makes the object of code
 * 0x501d (profile 0x24) two units along -x and one along z from the point overlay 9 gives
 * (func_ov009_0226321c); slot 0x24 draws that object's model. That object is the mailbox
 * (mailbox.h). */
#ifndef CLEAN_OV003_PLAYER_HOUSE_H
#define CLEAN_OV003_PLAYER_HOUSE_H

#include "types.h"

typedef struct PlayerHouse {
    const void *vtable; /* data_ov003_02239254 */
    u8 unk_04[0xec - 0x04];
    const void *receiver_vtable; /* data_ov003_02239318 */
    u8 unk_F0[0x198 - 0xf0];
    void *model; /* overlay 9's model object's model */
    u8 unk_19C[0x2b4 - 0x19c];
    void *texture;   /* the house's texture, loaded by PlayerHouse_LoadTexture */
    void *texture_2; /* bound with its palettes when set; nothing here sets it */
} PlayerHouse;

int PlayerHouse_Slot98(void);
int PlayerHouse_Slot8C(void);
void PlayerHouse_Slot9C(void);
int PlayerHouse_Slot90(void);
void PlayerHouse_BindTextures(PlayerHouse *house);
void PlayerHouse_LoadTexture(PlayerHouse *house);
char *PlayerHouse_TexturePath(void);
int PlayerHouse_Look(void);
int PlayerHouse_Draw(void);
int PlayerHouse_Init(PlayerHouse *house);
PlayerHouse *PlayerHouse_DestroyAndFree(PlayerHouse *house);
PlayerHouse *PlayerHouse_Destroy(PlayerHouse *house);
PlayerHouse *PlayerHouse_Construct(PlayerHouse *house);
void PlayerHouse_New(void);
PlayerHouse *PlayerHouse_ReceiverDestroyAndFree(void *receiver);
PlayerHouse *PlayerHouse_ReceiverDestroy(void *receiver);

#endif
