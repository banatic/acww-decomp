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

#include "main/g3d_render.h"
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

int MuseumDisplay_ShowsNode(MuseumDisplay *self, int node);
void MuseumDisplay_FindNodes(MuseumDisplay *self);
int MuseumDisplay_SetNodeVisibility(MuseumDisplay *self, int node, G3dRenderState *state);
int MuseumDisplay_Release(MuseumDisplay *self);
int MuseumDisplay_Draw(MuseumDisplay *self);
int MuseumDisplay_Update(void);
int MuseumDisplay_Start(MuseumDisplay *self);
MuseumDisplay *MuseumDisplay_Delete(MuseumDisplay *self);
MuseumDisplay *MuseumDisplay_Destruct(MuseumDisplay *self);
MuseumDisplay *MuseumDisplay_Construct(MuseumDisplay *self);
void MuseumDisplay_SetModelHooks(G3dRenderState *state);

void MuseumDisplay_NodeHook(G3dRenderState *state);
const MuseumDisplayKind *MuseumDisplay_Kind(u32 kind);
u16 MuseumDisplay_PaintingItem(u32 index);
void MuseumDisplay_Create(void);

#endif
