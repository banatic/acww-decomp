/* A scene object of overlay 3 that stands for one of the town's eight villagers at their house
 * (class Obj_ov003_02238f28, vtable 0x02238f28, receiver part at 0xec). Its special character
 * code (the halfword at 0x136, 0x5001 to 0x5008) is the villager's index plus 0x5001 in main's
 * list of villagers at 0x021e5a2c; it is made with the villager's house textures and a
 * villager actor (profile 0x18) of that index.
 *
 * What is known so far are some of its vtable slots: two checks of the villager's status (0x8c,
 * and 0x9c at night) and the talk at a closed door (0x78: receiver "obj_etc_closed", or
 * "obj_etc_error", with a message by the villager's personality and the villager's name as
 * text). It is derived from overlay 9's scene actor (Obj_ov009_022658dc),
 * which runs the rest. */
#ifndef CLEAN_OV003_VILLAGER_HOUSE_H
#define CLEAN_OV003_VILLAGER_HOUSE_H

#include "types.h"

/* Bits of VillagerHouse.flags. */
#define VILLAGER_HOUSE_FLAG_ERROR 0x02 /* the talk is "obj_etc_error"'s */

typedef struct VillagerHouse {
    const void *vtable; /* data_ov003_02238f28 */
    u8 unk_04[0xec - 0x04];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable;
    char receiver_name[25]; /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x12c - 0x10b];
    void *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x136 - 0x130];
    u16 code; /* the special character's code: 0x5001 + the villager's index */
    u8 unk_138[0x236 - 0x138];
    u8 flags;       /* VILLAGER_HOUSE_FLAG_* */
    u8 message_set; /* nonzero: the messages of the second table */
} VillagerHouse;

int VillagerHouse_Slot98(void);
int VillagerHouse_Slot90(void);
int VillagerHouse_Slot9C(VillagerHouse *house);
int VillagerHouse_Slot8C(VillagerHouse *house);
void VillagerHouse_PrepareTalk(VillagerHouse *house);
void VillagerHouse_Slot68(void);

#endif
