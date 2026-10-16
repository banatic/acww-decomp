/* The palettes of the players' skin ("skin_pl") and hair ("hair_pl"), a field actor's
 * FIELD_ACTOR_PALETTES byte naming one of four buffers of the table at data_021cacec (the
 * player's, data_020c75c4). Each buffer holds a skin palette file of func_0205f970 bytes
 * followed by a hair palette file of func_0205f96c bytes, both read from "/PPal/" ("/PPal/
 * <index / 32>/<index>.nsbtx"); FieldActor_SetPalettes picks the files from the face, the
 * hair colour and the sun level. */
#ifndef CLEAN_MAIN_ACTOR_PALETTES_H
#define CLEAN_MAIN_ACTOR_PALETTES_H

#include "autoload_2/heap.h"
#include "types.h"

int ActorPalettes_LoadHair(unsigned char *palettes, int index);
int ActorPalettes_LoadSkin(unsigned char *palettes, int index);
int ActorPalettes_HairFile(unsigned char *palettes);
unsigned long ActorPalettes_SkinFile(unsigned char *palettes);
void ActorPalettes_SetSlotByte(unsigned char *palettes, int entry);
void ActorPalettes_SetSlot(unsigned char *palettes, int entry);
void ActorPalettes_DestructSlot(void *palettes);

/* The number of buffers, also a palette byte's value for none. */
#define ACTOR_PALETTES_COUNT 4

/* The table at data_021cacec (a global C++ object): the buffers, each ActorPalettes_BufferSize
 * bytes taken from the scene's heap at data_021c9ae0 for one of the session's players. */
typedef struct ActorPaletteBuffers {
    u8 *buffer[ACTOR_PALETTES_COUNT]; /* 0x00 */
} ActorPaletteBuffers;

void ActorPalettes_ConstructSlot(unsigned char *palettes);
unsigned long ActorPalettes_Buffer(ActorPaletteBuffers *table, int entry);
void ActorPalettes_Clear(ActorPaletteBuffers *table);
void ActorPalettes_Create(ActorPaletteBuffers *table);
void ActorPalettes_Destruct(void *table);
void ActorPalettes_Construct(void *table);
int ActorPalettes_BufferSize(void);
int ActorPalettes_HairSize(void);
int ActorPalettes_SkinSize(void);
char *ActorPalettes_Path(unsigned int index);
void ActorPalettes_EndScene(void);
void ActorPalettes_StartScene(Heap *parent);

#endif
