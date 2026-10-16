/* The buffers the field actors' face texture files ("/PFcTx/<number / 32>/<number>.nsbtx",
 * the textures "e.0" and "m.0") are read into (data_021c9e24, a global C++ object): four
 * buffers of FaceTexture_FileSize bytes taken from the scene's heap at data_021c9af0 when the
 * scene starts, for the session's players only.
 *
 * An actor names its buffer with one byte (FIELD_ACTOR_FACE), FACE_TEXTURE_COUNT for none
 * (data_020c75cc gives each player its buffer). */
#ifndef CLEAN_MAIN_FACE_TEXTURE_H
#define CLEAN_MAIN_FACE_TEXTURE_H

#include "autoload_2/heap.h"
#include "types.h"

/* The number of buffers, also a face byte's value for none. */
#define FACE_TEXTURE_COUNT 4

typedef struct FaceTextures {
    u8 *file[FACE_TEXTURE_COUNT]; /* 0x00 */
} FaceTextures;

unsigned long FaceTexture_SlotFile(unsigned char *face);
int FaceTexture_Load(unsigned char *face, int number);
void FaceTexture_SetSlot(unsigned char *face, int index);
void FaceTexture_Assign(unsigned char *face, int index);
void FaceTexture_DestructSlot(void *face);
void FaceTexture_ConstructSlot(unsigned char *face);
unsigned long FaceTexture_File(FaceTextures *textures, int index);
void FaceTexture_Clear(FaceTextures *textures);
void FaceTexture_AllocFiles(FaceTextures *textures);
void FaceTexture_Destruct(void *textures);
void FaceTexture_Construct(void *textures);
int FaceTexture_FileSize(void);
char *FaceTexture_Path(unsigned int number);
void FaceTexture_EndScene(void);
void FaceTexture_StartScene(Heap *parent);

#endif
