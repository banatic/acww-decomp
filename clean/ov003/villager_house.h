/* A scene object of overlay 3 that stands for one of the town's eight villagers at their house
 * (class Obj_ov003_02238f28, vtable 0x02238f28, receiver part 0x02238fec, 0x38c bytes). Its
 * special character code (the halfword at 0x136, 0x5001 to 0x5008) is the villager's index
 * plus 0x5001 in main's list of villagers at 0x021e5a2c. It is derived from overlay 9's scene
 * actor (Obj_ov009_022658dc), which runs the rest.
 *
 * The villager's house look (the low 5 bits of the byte func_02080b64 gives) picks its files:
 * bits 2 to 4 are the house's kind, bits 0 and 1 its variant. Its files are named
 * "obj_house<kind>_<variant>" in "/str/npcHs/<kind>/", with a letter overlay 3 picks
 * (func_ov003_022203dc). Two sets of resources overlay 3 loads are shared by the houses:
 *
 *   - data_ov003_0223cea0: four house textures and four light textures by variant, and the
 *     joint animations "/str/obj_house_i.nsbca" and "/str/obj_house_o.nsbca";
 *   - data_ov003_0223ce80 ("/str/npcHsX.arc"): five second models "obj_x_house<kind>", their
 *     texture "obj_x_house0" and a texture pattern animation "obj_x_deco", with a byte that
 *     says the archive was loaded.
 *
 * Set up (slot 0x70), a house makes its villager (profile 0x18, the villager's index as the
 * group) at its position moved by (-2, 1, 2) units, binds the textures of its variant to its
 * model, and, with the archive, makes its second model of its kind (the X model) with the
 * pattern animation. The X model follows the house's placement each frame (slot 0x18) and is
 * drawn by slot 0x24. Overlay 3 keeps the houses by villager index at data_ov003_0223c928.
 *
 * Its other slots: two checks of the villager's status (0x8c, and 0x9c at night) and the talk at
 * a closed door (0x78: receiver "obj_etc_closed", or "obj_etc_error", with a message by the
 * villager's personality and the villager's name as text). */
#ifndef CLEAN_OV003_VILLAGER_HOUSE_H
#define CLEAN_OV003_VILLAGER_HOUSE_H

#include "autoload_2/matrix.h" /* Mtx43 */
#include "autoload_2/vector.h" /* Vec3 */
#include "types.h"

/* Bits of VillagerHouse.flags. */
#define VILLAGER_HOUSE_FLAG_ERROR 0x02 /* the talk is "obj_etc_error"'s */

/* A model object of main (Obj_020dd05c, 0xb8 bytes; destructor func_020551e0, constructor
 * func_02055210). */
typedef struct VillagerHouseModel {
    u8 unk_00[0x5c];
    void *resource; /* the model resource func_02055f2c gave it */
    void *texture;  /* the texture func_02055f2c gave it */
    Mtx43 matrix;   /* where and how it is drawn */
    u8 unk_94[0xb8 - 0x94];
} VillagerHouseModel;

/* An animation of main (Obj_020dd154, 0x20 bytes; destructor func_020565b0, constructor
 * func_020565c8): `frame` is copied to `target` once it is bound to a model. */
typedef struct VillagerHouseAnim {
    const void *vtable;
    u8 unk_04[4];
    u32 frame; /* in 20.12 fixed point */
    u8 unk_0C[0xc];
    u32 *target;
    u32 unk_1C;
} VillagerHouseAnim;

typedef struct VillagerHouse {
    const void *vtable; /* data_ov003_02238f28 */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_02238fec */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x12c - 0x10b];
    void *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x136 - 0x130];
    u16 code; /* the special character's code: 0x5001 + the villager's index */
    u8 unk_138[0x13c - 0x138];
    u8 model_object[0x198 - 0x13c]; /* overlay 9's model object (Obj_020dd05c) */
    void *model;                    /* that model object's model */
    u8 unk_19C[0x1a0 - 0x19c];
    Mtx43 matrix; /* that model object's placement (its matrix, 0x64 bytes in) */
    u8 unk_1D0[0x235 - 0x1d0];
    u8 flags_235;   /* bit 0: slot 0x18 leaves the X model's animation alone */
    u8 flags;       /* VILLAGER_HOUSE_FLAG_* */
    u8 message_set; /* nonzero: the messages of the second table */
    u8 unk_238[0x2b4 - 0x238];
    VillagerHouseModel x_model; /* the second model, from "/str/npcHsX.arc" */
    VillagerHouseAnim x_anim;   /* "obj_x_deco" on the X model */
} VillagerHouse;

int VillagerHouse_Slot98(void);
int VillagerHouse_Slot90(void);
int VillagerHouse_Slot9C(VillagerHouse *house);
int VillagerHouse_Slot8C(VillagerHouse *house);
void VillagerHouse_PrepareTalk(VillagerHouse *house);
void VillagerHouse_GetAnimO(void);
void VillagerHouse_GetAnimI(void);
int VillagerHouse_LtTexturePath(void);
char *VillagerHouse_TexturePath(VillagerHouse *house);
char *VillagerHouse_ArchivePath(VillagerHouse *house);
char *VillagerHouse_ModelName(VillagerHouse *house);
u8 VillagerHouse_Variant(VillagerHouse *house);
u8 VillagerHouse_Look(VillagerHouse *house);
int VillagerHouse_Leave(VillagerHouse *house);
int VillagerHouse_Draw(VillagerHouse *house);
int VillagerHouse_Update(VillagerHouse *house);
int VillagerHouse_Init(VillagerHouse *house);
VillagerHouse *VillagerHouse_DestroyAndFree(VillagerHouse *house);
VillagerHouse *VillagerHouse_Destroy(VillagerHouse *house);
VillagerHouse *VillagerHouse_Construct(VillagerHouse *house);
void VillagerHouse_New(void);
VillagerHouse *VillagerHouse_ReceiverDestroyAndFree(void *receiver);
VillagerHouse *VillagerHouse_ReceiverDestroy(void *receiver);

#endif
