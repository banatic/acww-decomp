/* The museum's display cases (museum_display.h). */
#include "museum_display.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/g3d_resource.h"
#include "main/model_object.h"
#include "main/museum_record.h"
#include "ov004/rmo_object_slots.h"
#include "rmo_object_base.h"

static_assert(offsetof(MuseumDisplay, nodes) == 0x290, "nodes");
static_assert(offsetof(MuseumDisplayHookState, hooks) == 0x0c, "hooks");
static_assert(offsetof(MuseumDisplayHookState, hook_timings) == 0x8c, "hook timings");
static_assert(offsetof(MuseumDisplayHookState, visible) == 0xb8, "visible");
static_assert(sizeof(MuseumDisplayKind) == 0x10, "MuseumDisplayKind size");

#define G3D_COMMAND_NODE 2 /* NitroSystem's NNS_G3D_SBC_NODE */
#define G3D_TIMING_B 2     /* NNS_G3D_SBC_CALLBACK_TIMING_B */

/* The class's vtable. */
extern const u8 data_ov004_02255200[];

/* The node names are built here ("p%d_%d": the exhibit, and 1 when it was given). */
extern char data_ov004_02258460[];
extern const char data_ov004_02255268[];

extern MuseumRecord data_021f38f8;
extern Heap *data_021c9b24;

extern const MuseumDisplayKind *func_ov004_0222f320(u32 kind);
extern void func_ov004_0222f304(MuseumDisplayHookState *state);  /* the node hook */
extern void func_ov004_0222f2f4(MuseumDisplayHookState *state);  /* sets it */
extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */

/* The RMO family's base class (rmo_object.h). */

/* The kind: a word in the scene object's bytes 8 to 11. */
static const MuseumDisplayKind *kind_of(const MuseumDisplay *self)
{
    u32 kind;
    memcpy(&kind, self->base.actor.unk_08, sizeof(kind));
    return func_ov004_0222f320(kind);
}

/* func_ov004_0222f17c: whether `node` is one of those drawn. QUIRK: the nodes are compared as
 * signed bytes, so a node past 127 (or one not found, -1) is never drawn. */
int MuseumDisplay_ShowsNode(MuseumDisplay *self, int node)
{
    const MuseumDisplayKind *kind = kind_of(self);
    u32 count = kind->count;
    for (u32 i = 0; i < count; i++) {
        if (node == self->nodes[i]) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0222f17c, MuseumDisplay_ShowsNode)

/* func_ov004_0222f1b4: for each exhibit, the node drawn: "p<i>_1" when the museum's record has
 * it, else "p<i>_0" (as a byte; -1 when the model has no such node). */
void MuseumDisplay_FindNodes(MuseumDisplay *self)
{
    const MuseumDisplayKind *kind = kind_of(self);
    self->nodes = Heap_Alloc(data_021c9b24, (int) kind->count);
    for (u32 i = 0; i < kind->count; i++) {
        u16 item = kind->item(i);
        int given = MuseumRecord_IsGiven(&data_021f38f8, &item) != 0;
        func_02064328(data_ov004_02258460, data_ov004_02255268, i, given);
        self->nodes[i] = (s8) G3dRes_NodeIndex(self->base.body.object.model, data_ov004_02258460);
    }
}
CLEAN_AS(func_ov004_0222f1b4, MuseumDisplay_FindNodes)

/* func_ov004_0222f234 (from the node hook): the node is visible when it is drawn; that, too,
 * is the result. */
int MuseumDisplay_SetNodeVisibility(MuseumDisplay *self, int node, MuseumDisplayHookState *state)
{
    int shown = MuseumDisplay_ShowsNode(self, node);
    *state->visible = (u32) shown;
    return shown;
}
CLEAN_AS(func_ov004_0222f234, MuseumDisplay_SetNodeVisibility)

/* func_ov004_0222f248 (vtable slot 0x0c): the archive released. The nodes' block stays (it is
 * the room's heap's). */
int MuseumDisplay_Release(MuseumDisplay *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    return 1;
}
CLEAN_AS(func_ov004_0222f248, MuseumDisplay_Release)

/* func_ov004_0222f258 (vtable slot 0x24) */
int MuseumDisplay_Draw(MuseumDisplay *self)
{
    AnimatedModel_Draw((AnimatedModel *) &self->base.body, NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222f258, MuseumDisplay_Draw)

/* func_ov004_0222f26c (vtable slot 0x18): nothing to do. */
int MuseumDisplay_Update(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0222f26c, MuseumDisplay_Update)

/* func_ov004_0222f270 (vtable slot 0x00): the case's archive loaded, the hook set that is run
 * before each draw (the game's func_ov004_0222f2f4), and the nodes looked up. */
int MuseumDisplay_Start(MuseumDisplay *self)
{
    const MuseumDisplayKind *kind = kind_of(self);
    RmoObjectSlots_Load(&self->base, kind->archive, kind->texture);
    ModelObject_SetInitHook(&self->base.body.object, (void *) func_ov004_0222f2f4, self);
    MuseumDisplay_FindNodes(self);
    return 1;
}
CLEAN_AS(func_ov004_0222f270, MuseumDisplay_Start)

/* func_ov004_0222f2a4 (vtable slot 0x44): taken down and freed. */
MuseumDisplay *MuseumDisplay_Delete(MuseumDisplay *self)
{
    self->base.actor.vtable = data_ov004_02255200;
    RmoObjectSlots_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222f2a4, MuseumDisplay_Delete)

/* func_ov004_0222f2c4 (vtable slot 0x40) */
MuseumDisplay *MuseumDisplay_Destruct(MuseumDisplay *self)
{
    self->base.actor.vtable = data_ov004_02255200;
    RmoObjectSlots_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_0222f2c4, MuseumDisplay_Destruct)

/* func_ov004_0222f2dc */
MuseumDisplay *MuseumDisplay_Construct(MuseumDisplay *self)
{
    RmoObjectBase_Construct(&self->base);
    self->base.actor.vtable = data_ov004_02255200;
    return self;
}
CLEAN_AS(func_ov004_0222f2dc, MuseumDisplay_Construct)

/* func_ov004_0222f2f4 (run before each draw): the nodes' hook (the game's func_ov004_0222f304)
 * set, run after each node's visibility is decided. */
void MuseumDisplay_SetModelHooks(MuseumDisplayHookState *state)
{
    state->hooks[G3D_COMMAND_NODE] = (u32) (uintptr_t) func_ov004_0222f304;
    state->hook_timings[G3D_COMMAND_NODE] = G3D_TIMING_B;
}
CLEAN_AS(func_ov004_0222f2f4, MuseumDisplay_SetModelHooks)

/* The model being drawn (NitroSystem's NNSG3dRenderObj): its user word is the display case,
 * set by ModelObject_SetInitHook in MuseumDisplay_Start. */
typedef struct MuseumDisplayRenderObject {
    u8 unk_00[0x2c];
    MuseumDisplay *user; /* 0x2c */
} MuseumDisplayRenderObject;

static_assert(offsetof(MuseumDisplayHookState, render_object) == 0x04, "render object");
static_assert(sizeof(MuseumDisplay) == 0x294, "the size MuseumDisplay_Create allocates");

/* The cases of data_ov004_022478a8: the paintings, then the insects. */
#define MUSEUM_DISPLAY_KINDS 2
#define MUSEUM_DISPLAY_PAINTINGS 20
/* The first painting's item code; each painting has four codes. */
#define MUSEUM_DISPLAY_PAINTING_FIRST 0x3894
#define MUSEUM_DISPLAY_PAINTING_CODES 4

extern const MuseumDisplayKind data_ov004_022478a8[MUSEUM_DISPLAY_KINDS];

/* func_ov004_0222f304 (the node hook MuseumDisplay_SetModelHooks sets): shows the node being
 * drawn (the command's byte 1) when it is one of the case's, else hides it; nothing for a
 * model without a case. */
void MuseumDisplay_NodeHook(MuseumDisplayHookState *state)
{
    MuseumDisplay *self = ((const MuseumDisplayRenderObject *) state->render_object)->user;
    if (self != NULL) {
        MuseumDisplay_SetNodeVisibility(self, state->command[1], state);
    }
}
CLEAN_AS(func_ov004_0222f304, MuseumDisplay_NodeHook)

/* func_ov004_0222f320: the case of `kind`; a kind past them gives the first (the paintings). */
const MuseumDisplayKind *MuseumDisplay_Kind(u32 kind)
{
    if (kind < MUSEUM_DISPLAY_KINDS) {
        return &data_ov004_022478a8[kind];
    }
    return &data_ov004_022478a8[0];
}
CLEAN_AS(func_ov004_0222f320, MuseumDisplay_Kind)

/* func_ov004_0222f334 (the paintings' MuseumDisplayKind.item): the item code of painting
 * `index`, its first of four; an index past them gives the first painting's. */
u16 MuseumDisplay_PaintingItem(u32 index)
{
    if (index < MUSEUM_DISPLAY_PAINTINGS) {
        return (u16) (MUSEUM_DISPLAY_PAINTING_FIRST + index * MUSEUM_DISPLAY_PAINTING_CODES);
    }
    return MUSEUM_DISPLAY_PAINTING_FIRST;
}
CLEAN_AS(func_ov004_0222f334, MuseumDisplay_PaintingItem)

/* func_ov004_0222f34c: a new display case from the room's heap; nothing when it has no room. */
void MuseumDisplay_Create(void)
{
    MuseumDisplay *self = Heap_AllocAuxZeroed(sizeof(MuseumDisplay));
    if (self != NULL) {
        MuseumDisplay_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222f34c, MuseumDisplay_Create)
