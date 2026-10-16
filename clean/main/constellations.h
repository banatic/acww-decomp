/* The players' constellations in the night sky ("menu/star"): up to 16 kept in the town's
 * save (data_021f2b04), a draft being designed (at 0x100 of data_021ee418), and the sky's
 * background map and palettes they are drawn into.
 *
 * A constellation is made of up to 16 pieces, each a group of up to four stars from the table
 * at data_020e42a0; a star sits in one of the sky's 64 columns and 32 rows of 8-pixel tiles.
 * The sky map is two 32 x 32 screens side by side, 0x200 pixels round. Overlay 127 judges a
 * draft before it is kept (Constellations_Add); a constellation kept that way is marked new
 * until Constellations_TakeNew or Constellations_ClearNew. */
#ifndef CLEAN_MAIN_CONSTELLATIONS_H
#define CLEAN_MAIN_CONSTELLATIONS_H

#include "main/calendar.h"
#include "main/design.h"
#include "types.h"

#define CONSTELLATIONS_COUNT 16
#define CONSTELLATIONS_PIECES 16
#define CONSTELLATIONS_NAME_LENGTH 6
/* A piece's place when empty. */
#define CONSTELLATIONS_NO_PIECE 0xffff

typedef struct Constellation {
    DesignCreator creator;                /* 0x00: the player who made it */
    u16 name[CONSTELLATIONS_NAME_LENGTH]; /* 0x1e */
    u16 pieces[CONSTELLATIONS_PIECES];    /* 0x2a: CONSTELLATIONS_NO_PIECE when empty */
} Constellation;

typedef struct ConstellationStore {
    Constellation list[CONSTELLATIONS_COUNT];
    u16 kept;   /* 0x4a0: one bit per constellation in the list */
    u16 unseen; /* 0x4a2: one bit per constellation kept since it was last looked at */
} ConstellationStore;

void Constellations_MarkSkyMap(u16 *map);
void Constellations_PaintAll(u16 *map);
void Constellations_Paint(u16 *map, const Constellation *constellation, int palette);
void Constellations_PaintPiece(u16 *map, int piece, int palette);
int Constellations_MapIndex(int column, int row);
int Constellations_IsStarTile(int tile);
int Constellations_NameTaken(const u16 *name, int except);
void Constellations_FileDraft(void);
void Constellations_DraftRandom(void);
int Constellations_Add(Constellation *constellation);
void Constellations_ReleaseJudge(void);
void Constellations_LoadJudge(void);
int Constellations_Nearest(void);
int Constellations_InView(int scroll_x, int scroll_y, int x, int y);
void Constellations_TimeInView(DateTime *when, int number);
void Constellations_ClearNew(void);
int Constellations_TakeNew(int *number);
int Constellations_NameToText(void *text, int number);
void Constellations_GetName(u16 *name, int number);
void Constellations_SetName(const u16 *name, int number);
void Constellations_SetCreator(DesignCreator *creator);
int Constellations_At(int number);
void Constellations_Remove(int number);
void Constellations_Put(const Constellation *constellation, int number, int is_new);
int Constellations_Get(int number);
int Constellations_CountFree(void);
int Constellations_FreeSlot(void);
int Constellations_StoreAddress(void);
void Constellations_Center(const u16 *pieces, int *x, int *y);
int Constellations_ColumnMarked(int column);
void Constellations_MarkColumn(int column);
void Constellations_ClearColumns(void);
const u8 *Constellations_PieceStars(unsigned int piece);

/* The two text classes of a constellation's name, on the game's text base (text_label.h): a
 * wide text of 6 characters (vtable data_020e4278, 0x1c bytes) and a label of 14 8-bit
 * characters (vtable data_020e4290, 0x20 bytes). */
#include "main/text_label.h"

#define CONSTELLATIONS_LABEL_CAPACITY 14

typedef struct ConstellationsWideName {
    const TextVtable *vtable; /* data_020e4278 */
    u8 base_04[0xa];          /* the text base's */
    u16 text[CONSTELLATIONS_NAME_LENGTH];
} ConstellationsWideName;

typedef struct ConstellationsLabel {
    const TextVtable *vtable; /* data_020e4290 */
    u8 base_04[0xe];          /* the text base's */
    char text[CONSTELLATIONS_LABEL_CAPACITY];
} ConstellationsLabel;

int ConstellationsWideName_Buffer(int text);
int ConstellationsWideName_Capacity(void);
ConstellationsWideName *ConstellationsWideName_DestructDelete(ConstellationsWideName *text);
ConstellationsWideName *ConstellationsWideName_Destruct(ConstellationsWideName *text);
ConstellationsWideName *ConstellationsWideName_Construct(ConstellationsWideName *text);
int ConstellationsLabel_Buffer(int label);
int ConstellationsLabel_Capacity(void);
ConstellationsLabel *ConstellationsLabel_DestructDelete(ConstellationsLabel *label);
ConstellationsLabel *ConstellationsLabel_Destruct(ConstellationsLabel *label);
ConstellationsLabel *ConstellationsLabel_Construct(ConstellationsLabel *label);
int Constellations_IsKept(const ConstellationStore *store, int number);
void Constellations_ClearKept(ConstellationStore *store, int number);
void Constellations_SetKept(ConstellationStore *store, int number);
void Constellations_ResetStore(ConstellationStore *store);
ConstellationStore *Constellations_DestructList(ConstellationStore *store);
int Constellations_ConstructList(int store);
Constellation *Constellations_Copy(Constellation *dst, const Constellation *src);
void Constellations_Clear(Constellation *constellation);
Constellation *Constellations_DestructOne(Constellation *constellation);
int Constellations_ConstructOne(int constellation);

#endif
