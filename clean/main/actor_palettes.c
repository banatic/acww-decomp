/* The players' skin and hair palettes (actor_palettes.h). */
#include "actor_palettes.h"

#include "clean.h"
#include "scene_heaps.h"
#include "session.h"

extern u8 data_021cacec[]; /* the buffers' table */

/* The table's buffer `entry`, as an address. */
extern unsigned long func_0205f8e0(u8 *table, int entry);
/* The sizes of the hair and of the skin palette files, and the path of palette file `index`. */
extern int func_0205f96c(void);
extern int func_0205f970(void);
extern char *func_0205f974(unsigned int index);
extern int func_02064af4(const char *path, void *buffer, int size); /* read a file: its size, 0 on failure */

/* func_0205f848: palette file `index` read as the hair palette, at most its size; its size,
 * 0 on failure. */
int ActorPalettes_LoadHair(unsigned char *palettes, int index)
{
    int file = ActorPalettes_HairFile(palettes);
    char *path = func_0205f974((unsigned int) index);
    int size = func_0205f96c();
    return func_02064af4(path, (void *) (uintptr_t) file, size);
}
CLEAN_AS(func_0205f848, ActorPalettes_LoadHair)

/* func_0205f874: palette file `index` read as the skin palette, at most its size; its size,
 * 0 on failure. */
int ActorPalettes_LoadSkin(unsigned char *palettes, int index)
{
    unsigned long file = ActorPalettes_SkinFile(palettes);
    char *path = func_0205f974((unsigned int) index);
    int size = func_0205f970();
    return func_02064af4(path, (void *) (uintptr_t) file, size);
}
CLEAN_AS(func_0205f874, ActorPalettes_LoadSkin)

/* func_0205f8a0: the hair palette file, right after the skin's, as an address. */
int ActorPalettes_HairFile(unsigned char *palettes)
{
    int skin = (int) ActorPalettes_SkinFile(palettes);
    return skin + func_0205f970();
}
CLEAN_AS(func_0205f8a0, ActorPalettes_HairFile)

/* func_0205f8b4: the skin palette file, at the start of the buffer the byte names, as an
 * address. */
unsigned long ActorPalettes_SkinFile(unsigned char *palettes)
{
    return func_0205f8e0(data_021cacec, *palettes);
}
CLEAN_AS(func_0205f8b4, ActorPalettes_SkinFile)

/* func_0205f8c8: the byte set to name buffer `entry`. */
void ActorPalettes_SetSlotByte(unsigned char *palettes, int entry)
{
    *palettes = (unsigned char) entry;
}
CLEAN_AS(func_0205f8c8, ActorPalettes_SetSlotByte)

/* func_0205f8cc: ActorPalettes_SetSlotByte. */
void ActorPalettes_SetSlot(unsigned char *palettes, int entry)
{
    ActorPalettes_SetSlotByte(palettes, entry);
}
CLEAN_AS(func_0205f8cc, ActorPalettes_SetSlot)

/* func_0205f8d4: the byte's destructor, which does nothing. */
void ActorPalettes_DestructSlot(void *palettes)
{
    (void) palettes;
}
CLEAN_AS(func_0205f8d4, ActorPalettes_DestructSlot)

/* ---- The table of buffers ---- */

/* The sizes of a buffer's two palette files. */
#define ACTOR_PALETTES_SKIN_SIZE 228
#define ACTOR_PALETTES_HAIR_SIZE 212
#define ACTOR_PALETTES_ALIGN 4

static_assert(sizeof(ActorPaletteBuffers) == 0x10, "ActorPaletteBuffers");

extern Heap *data_021c9ae0;        /* the heap the buffers are taken from (SceneHeaps_Create021c9ae0) */
extern NetSession *data_020ccf94;  /* the session */
extern char data_021cacfc[];       /* the path buffer */
extern const char data_020dd7b0[]; /* "/PPal/%d/%d.nsbtx" */
extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */

/* The table, data_021cacec. */
static ActorPaletteBuffers *actor_palettes_table(void)
{
    return (ActorPaletteBuffers *) data_021cacec;
}

/* func_0205f8d8: a palette byte's constructor: it names none. */
void ActorPalettes_ConstructSlot(unsigned char *palettes)
{
    *palettes = ACTOR_PALETTES_COUNT;
}
CLEAN_AS(func_0205f8d8, ActorPalettes_ConstructSlot)

/* func_0205f8e0: buffer `entry`, as an address. */
unsigned long ActorPalettes_Buffer(ActorPaletteBuffers *table, int entry)
{
    return (unsigned long) (uintptr_t) table->buffer[entry];
}
CLEAN_AS(func_0205f8e0, ActorPalettes_Buffer)

/* func_0205f8e8: every buffer forgotten, then the heap they were taken from, if there is one,
 * emptied. */
void ActorPalettes_Clear(ActorPaletteBuffers *table)
{
    for (int i = 0; i < ACTOR_PALETTES_COUNT; i++) {
        table->buffer[i] = NULL;
    }
    Heap *heap = data_021c9ae0;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_0205f8e8, ActorPalettes_Clear)

/* func_0205f910: a buffer for each of the session's players, taken from the heap at
 * data_021c9ae0.
 * REQUIRES: the session has at most ACTOR_PALETTES_COUNT players (its count is 0-4). */
void ActorPalettes_Create(ActorPaletteBuffers *table)
{
    Heap *heap = data_021c9ae0;
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        table->buffer[i] = Heap_AllocAligned(heap, ActorPalettes_BufferSize(), ACTOR_PALETTES_ALIGN);
    }
}
CLEAN_AS(func_0205f910, ActorPalettes_Create)

/* func_0205f950: the table's destructor (registered by __sinit_020c5998), which does nothing. */
void ActorPalettes_Destruct(void *table)
{
    (void) table;
}
CLEAN_AS(func_0205f950, ActorPalettes_Destruct)

/* func_0205f954: the table's constructor (__sinit_020c5998), which does nothing: the table
 * starts zeroed, no buffer taken. */
void ActorPalettes_Construct(void *table)
{
    (void) table;
}
CLEAN_AS(func_0205f954, ActorPalettes_Construct)

/* func_0205f958: a buffer's size, the skin palette file's and then the hair's. */
int ActorPalettes_BufferSize(void)
{
    int skin = ActorPalettes_SkinSize();
    return skin + ActorPalettes_HairSize();
}
CLEAN_AS(func_0205f958, ActorPalettes_BufferSize)

/* func_0205f96c */
int ActorPalettes_HairSize(void)
{
    return ACTOR_PALETTES_HAIR_SIZE;
}
CLEAN_AS(func_0205f96c, ActorPalettes_HairSize)

/* func_0205f970 */
int ActorPalettes_SkinSize(void)
{
    return ACTOR_PALETTES_SKIN_SIZE;
}
CLEAN_AS(func_0205f970, ActorPalettes_SkinSize)

/* func_0205f974: the path of palette file `index`, "/PPal/<index / 32>/<index>.nsbtx", in the
 * buffer at data_021cacfc. */
char *ActorPalettes_Path(unsigned int index)
{
    func_02064328(data_021cacfc, data_020dd7b0, index >> 5, index);
    return data_021cacfc;
}
CLEAN_AS(func_0205f974, ActorPalettes_Path)

/* func_0205f994: when the scene ends, the buffers cleared and the heap they are taken from
 * destroyed. */
void ActorPalettes_EndScene(void)
{
    ActorPalettes_Clear(actor_palettes_table());
    SceneHeaps_Destroy021c9ae0();
}
CLEAN_AS(func_0205f994, ActorPalettes_EndScene)

/* func_0205f9ac: when the scene starts, the heap at data_021c9ae0 made from `parent`, the
 * buffers taken from it, and it, if made, shrunk to them. */
void ActorPalettes_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ae0(parent);
    ActorPalettes_Create(actor_palettes_table());
    Heap *heap = data_021c9ae0;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205f9ac, ActorPalettes_StartScene)
