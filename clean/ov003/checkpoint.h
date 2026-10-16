/* The checkpoint of overlay 3 (class Obj_ov003_02238934, vtable 0x02238934, receiver part
 * 0x022389f8, 0x5a0 bytes): an object whose model is "obj_check0", "obj_check1" or
 * "obj_check2" from "/str/chkp/", by the style main keeps after the town's single design
 * (DESIGN_KIND_RECORD_5 at data_021f34b0 + 4, design.h), and which wears that design on its
 * material "w". When the design changes, main calls Checkpoint_RefreshDesign on actor 0x500b.
 *
 * The design is put on through a CheckpointDesign at 0x2b4: a texture binding of main (built
 * by func_020b9e58, filled by func_020b9d3c) and a texture file the design is loaded into
 * (func_0203cff8). The receiver's slot 0x14 is overlay 9's, through WarpObject_ReceiverSlot14
 * (warp_object.h). */
#ifndef CLEAN_OV003_CHECKPOINT_H
#define CLEAN_OV003_CHECKPOINT_H

#include "types.h"

/* The design on the material (Member_ov003_0221c490). */
typedef struct CheckpointDesign {
    u8 binding[0x28];     /* puts a texture on a material of the model */
    u8 texture_file[0x4]; /* the design loaded as a texture; only its start is known */
} CheckpointDesign;

typedef struct Checkpoint {
    const void *vtable; /* data_ov003_02238934 */
    u8 unk_04[0x198 - 0x04];
    void *model; /* the model the design is put on */
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

#endif
