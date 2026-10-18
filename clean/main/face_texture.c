/* The buffers of the field actors' face texture files (face_texture.h). */
#include "face_texture.h"

#include "clean.h"
#include "scene_heaps.h"
#include "session.h"
#include "c_library.h"
#include "rom_file.h"

/* Each buffer's size and alignment. */
#define FACE_TEXTURE_FILE_SIZE 11824
#define FACE_TEXTURE_ALIGN 4

static_assert(sizeof(FaceTextures) == 0x10, "FaceTextures");

extern FaceTextures data_021c9e24; /* the buffers */
extern Heap *data_021c9af0;        /* their heap (SceneHeaps_Create021c9af0) */
extern NetSession *data_020ccf94;  /* the session */
/* The path buffer of FaceTexture_Path, "/PFcTx/%d/%d.nsbtx" (the face's number / 32, then the
 * number). */
extern char data_021c9e34[];
extern const char data_020dd704[];

/* func_0205dc80: the buffer the byte `face` names, as an address. */
unsigned long FaceTexture_SlotFile(unsigned char *face)
{
    return FaceTexture_File(&data_021c9e24, *face);
}
CLEAN_AS(func_0205dc80, FaceTexture_SlotFile)

/* func_0205dc94: face `number`'s texture file read into the buffer the byte `face` names, at
 * most FaceTexture_FileSize bytes; the size read, 0 on failure. */
int FaceTexture_Load(unsigned char *face, int number)
{
    unsigned long file = FaceTexture_File(&data_021c9e24, *face);
    char *path = FaceTexture_Path((unsigned int) number);
    return RomFile_Read(path, (void *) (uintptr_t) file, FaceTexture_FileSize());
}
CLEAN_AS(func_0205dc94, FaceTexture_Load)

/* func_0205dcc8: the face byte set to name buffer `index`. */
void FaceTexture_SetSlot(unsigned char *face, int index)
{
    *face = (unsigned char) index;
}
CLEAN_AS(func_0205dcc8, FaceTexture_SetSlot)

/* func_0205dccc: the face byte set to name buffer `index` (the buffer is left as it is). */
void FaceTexture_Assign(unsigned char *face, int index)
{
    FaceTexture_SetSlot(face, index);
}
CLEAN_AS(func_0205dccc, FaceTexture_Assign)

/* func_0205dcd4: a face byte's destructor, which does nothing. */
void FaceTexture_DestructSlot(void *face)
{
    (void) face;
}
CLEAN_AS(func_0205dcd4, FaceTexture_DestructSlot)

/* func_0205dcd8: a face byte's constructor: it names none. */
void FaceTexture_ConstructSlot(unsigned char *face)
{
    *face = FACE_TEXTURE_COUNT;
}
CLEAN_AS(func_0205dcd8, FaceTexture_ConstructSlot)

/* func_0205dce0: buffer `index`, as an address. */
unsigned long FaceTexture_File(FaceTextures *textures, int index)
{
    return (unsigned long) (uintptr_t) textures->file[index];
}
CLEAN_AS(func_0205dce0, FaceTexture_File)

/* func_0205dce8: every buffer forgotten; then their heap, if there is one, emptied. */
void FaceTexture_Clear(FaceTextures *textures)
{
    for (int i = 0; i < FACE_TEXTURE_COUNT; i++) {
        textures->file[i] = NULL;
    }
    Heap *heap = data_021c9af0;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_0205dce8, FaceTexture_Clear)

/* func_0205dd10: a buffer for each of the session's players, from the heap at data_021c9af0.
 * REQUIRES: the session has at most FACE_TEXTURE_COUNT players (its count is 0-4). */
void FaceTexture_AllocFiles(FaceTextures *textures)
{
    Heap *heap = data_021c9af0;
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        textures->file[i] = Heap_AllocAligned(heap, FaceTexture_FileSize(), FACE_TEXTURE_ALIGN);
    }
}
CLEAN_AS(func_0205dd10, FaceTexture_AllocFiles)

/* func_0205dd50: the buffers' destructor (registered by __sinit_020c58d0), which does
 * nothing. */
void FaceTexture_Destruct(void *textures)
{
    (void) textures;
}
CLEAN_AS(func_0205dd50, FaceTexture_Destruct)

/* func_0205dd54: the buffers' constructor (__sinit_020c58d0), which does nothing: the object
 * starts zeroed, without buffers. */
void FaceTexture_Construct(void *textures)
{
    (void) textures;
}
CLEAN_AS(func_0205dd54, FaceTexture_Construct)

/* func_0205dd58 */
int FaceTexture_FileSize(void)
{
    return FACE_TEXTURE_FILE_SIZE;
}
CLEAN_AS(func_0205dd58, FaceTexture_FileSize)

/* func_0205dd60: the path of face `number`'s texture file, written into one shared buffer
 * (each call overwrites the last one's path). */
char *FaceTexture_Path(unsigned int number)
{
    CLib_SPrintf(data_021c9e34, data_020dd704, number >> 5, number);
    return data_021c9e34;
}
CLEAN_AS(func_0205dd60, FaceTexture_Path)

/* func_0205dd80: when the scene ends, the buffers cleared and their heap destroyed. */
void FaceTexture_EndScene(void)
{
    FaceTexture_Clear(&data_021c9e24);
    SceneHeaps_Destroy021c9af0();
}
CLEAN_AS(func_0205dd80, FaceTexture_EndScene)

/* func_0205dd98: when the scene starts, the buffers' heap made from `parent`, the buffers
 * allocated, and the heap, if made, shrunk to them. */
void FaceTexture_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9af0(parent);
    FaceTexture_AllocFiles(&data_021c9e24);
    Heap *heap = data_021c9af0;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205dd98, FaceTexture_StartScene)
