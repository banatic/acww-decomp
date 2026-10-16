/* The checkpoint of overlay 3 (class Obj_ov003_02238934, vtable 0x02238934, receiver part
 * 0x022389f8, 0x5a0 bytes): an object whose model is "obj_check0", "obj_check1" or
 * "obj_check2" from "/str/chkp/", by the style main keeps after the town's single design
 * (DESIGN_KIND_RECORD_5 at data_021f34b0 + 4, design.h), and which wears that design on its
 * material "w". When the design changes, main calls Checkpoint_RefreshDesign on actor 0x500b.
 *
 * The design is put on through a CheckpointDesign at 0x2b4: a texture binding of main (built
 * by func_020b9e58, filled by func_020b9d3c) and a texture file the design is loaded into
 * (func_0203cff8). The receiver's slot 0x14 is overlay 9's, through WarpObject_ReceiverSlot14
 * (warp_object.h).
 *
 * When it is set up (vtable slot 0x70) it puts the design on and makes the five tiles of the
 * row before it (x - 2 to x + 2 at z - 1) solid; leaving the scene (slot 0x0c) takes the design
 * off again. It is derived from overlay 9's scene actor (Obj_ov009_022658dc), which runs the
 * rest. */
#ifndef CLEAN_OV003_CHECKPOINT_H
#define CLEAN_OV003_CHECKPOINT_H

#include "autoload_2/vector.h" /* Vec3 */
#include "types.h"

/* The design on the material (Member_ov003_0221c490). */
typedef struct CheckpointDesign {
    u8 binding[0x28];       /* puts a texture on a material of the model */
    u8 texture_file[0x2c4]; /* the design loaded as a texture; only its start is known */
} CheckpointDesign;

typedef struct Checkpoint {
    const void *vtable; /* data_ov003_02238934 */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    const void *receiver_vtable; /* data_ov003_022389f8 */
    u8 unk_F0[0x13c - 0xf0];
    u8 model_object[0x198 - 0x13c]; /* main's model object (Obj_020dd05c) */
    void *model;                    /* the model the design is put on: the model object's */
    u8 unk_19C[0x2b4 - 0x19c];
    CheckpointDesign design;
} Checkpoint;

void Checkpoint_ReleaseDesign(CheckpointDesign *design);
int Checkpoint_PutDesign(CheckpointDesign *design, void *model, void *source);
CheckpointDesign *Checkpoint_DestroyDesign(CheckpointDesign *design);
CheckpointDesign *Checkpoint_ConstructDesign(CheckpointDesign *design);
int Checkpoint_RefreshDesign(Checkpoint *checkpoint);
int Checkpoint_Slot94(void);
char *Checkpoint_LtTexturePath(void);
char *Checkpoint_TexturePath(void);
char *Checkpoint_ArchivePath(void);
const char *Checkpoint_ModelName(void);
int Checkpoint_Style(void);
int Checkpoint_Leave(Checkpoint *checkpoint);
int Checkpoint_Slot24(void);
int Checkpoint_Update(Checkpoint *checkpoint);
int Checkpoint_Init(Checkpoint *checkpoint);
Checkpoint *Checkpoint_DestroyAndFree(Checkpoint *checkpoint);
Checkpoint *Checkpoint_Destroy(Checkpoint *checkpoint);
Checkpoint *Checkpoint_Construct(Checkpoint *checkpoint);
void Checkpoint_New(void);
Checkpoint *Checkpoint_ReceiverDestroyAndFree(void *receiver);
Checkpoint *Checkpoint_ReceiverDestroy(void *receiver);

#endif
