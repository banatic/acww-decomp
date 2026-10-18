/* The museum's display cases (a room object of the RMO family, rmo_object.h; vtable
 * 0x02255200): one model holding a pair of nodes per exhibit, "p<i>_0" for the empty place
 * and "p<i>_1" for the exhibit, of which only the one matching the museum's record is drawn.
 *
 * The kind (RmoObject.actor.unk_08, read as a word) picks the case from the table
 * MuseumDisplay_Kind gives (data_ov004_022478a8): 0 the paintings (/roomObj/obj_ms_picture,
 * 20 exhibits), 1 the insects (/roomObj/obj_ms_insectA, 56 exhibits); a kind past them gives
 * the paintings. On starting it loads its archive, looks up the node to draw for each exhibit
 * (MuseumDisplay_FindNodes) and has its model's node hook (MuseumDisplay_NodeHook, set before
 * each draw by MuseumDisplay_SetModelHooks) hide every other node. */
#ifndef CLEAN_OV004_MUSEUM_DISPLAY_H
#define CLEAN_OV004_MUSEUM_DISPLAY_H

#include "rmo_object.h"
#include "types.h"

/* A case of data_ov004_022478a8. */
typedef struct MuseumDisplayKind {
    u16 (*item)(u32 index); /* 0x00: the exhibit's item code */
    u32 count;              /* 0x04: the exhibits */
    const char *archive;    /* 0x08 */
    const char *texture;    /* 0x0c */
} MuseumDisplayKind;

typedef struct MuseumDisplay {
    RmoObject base;
    s8 *nodes; /* 0x290: the node drawn for each exhibit (from the room's heap) */
} MuseumDisplay;

/* What the model's hooks get: the state of the model being drawn (NitroSystem's NNSG3dRS). */
typedef struct MuseumDisplayHookState {
    const u8 *command; /* the command being run: byte 1 is its node */
    void *render_object;
    u32 flags;
    u32 hooks[0x20]; /* the address of each command's hook, 0 for none */
    u8 hook_timings[0x20];
    u8 unk_ac[0xc];
    u32 *visible; /* 0xb8: the node's visibility */
} MuseumDisplayHookState;

int MuseumDisplay_ShowsNode(MuseumDisplay *self, int node);
void MuseumDisplay_FindNodes(MuseumDisplay *self);
int MuseumDisplay_SetNodeVisibility(MuseumDisplay *self, int node, MuseumDisplayHookState *state);
int MuseumDisplay_Release(MuseumDisplay *self);
int MuseumDisplay_Draw(MuseumDisplay *self);
int MuseumDisplay_Update(void);
int MuseumDisplay_Start(MuseumDisplay *self);
MuseumDisplay *MuseumDisplay_Delete(MuseumDisplay *self);
MuseumDisplay *MuseumDisplay_Destruct(MuseumDisplay *self);
MuseumDisplay *MuseumDisplay_Construct(MuseumDisplay *self);
void MuseumDisplay_SetModelHooks(MuseumDisplayHookState *state);

void MuseumDisplay_NodeHook(MuseumDisplayHookState *state);
const MuseumDisplayKind *MuseumDisplay_Kind(u32 kind);
u16 MuseumDisplay_PaintingItem(u32 index);
void MuseumDisplay_Create(void);

#endif
