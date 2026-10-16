/* The copies of the two engines' OBJ attribute memory (OAM) that the game fills each frame and
 * loads at the next blank (DisplayFrame), and the drawing of a cell's OBJs into them.
 *
 * Each copy holds 128 entries of 8 bytes: an OBJ's three attributes, then a halfword the
 * hardware uses for the affine parameters (four entries in a row give one group of PA, PB, PC
 * and PD in 8.8 fixed point). The OBJs of a copy are used from the start and counted; the
 * affine groups are used from the start too, apart from that count, and also counted (in
 * entries, four per group). An affine group is shared by every OBJ that wants the same four
 * parameters.
 *
 * A cell is a run of OBJs in the same 8-byte layout, positioned round the cell's point; the
 * fourth halfword of its last OBJ is 0xffff. */
#ifndef CLEAN_MAIN_OAM_BUFFER_H
#define CLEAN_MAIN_OAM_BUFFER_H

#include "types.h"

#define OAM_BUFFER_ENTRIES 128
#define OAM_BUFFER_CELL_LAST 0xffff

/* Which engine OamBuffer_IsMain is asked for. */
#define OAM_BUFFER_SCREEN_MAIN 0
#define OAM_BUFFER_SCREEN_SUB 1
#define OAM_BUFFER_SCREEN_3D 2    /* the engine on the 3D screen's side */
#define OAM_BUFFER_SCREEN_OTHER 3 /* the other one */

/* An OBJ: of the OAM, or of a cell. */
typedef struct OamEntry {
    u16 attr0;  /* y (0-7), affine mode (8-9), OBJ mode (10-11), mosaic (12), 256 colours (13), shape (14-15) */
    u16 attr1;  /* x (0-8), affine index (9-13) or flips (12-13), size (14-15) */
    u16 attr2;  /* tile (0-9), priority (10-11), palette (12-15) */
    u16 affine; /* an affine parameter; in a cell, OAM_BUFFER_CELL_LAST on its last OBJ */
} OamEntry;

/* The four affine parameters in 20.12 fixed point. */
typedef struct OamAffine {
    fx32 a;
    fx32 b;
    fx32 c;
    fx32 d;
} OamAffine;

int OamBuffer_IsMain(u32 screen);
int OamBuffer_FindAffine(OamEntry *oam, int *used, const OamAffine *params);
int OamBuffer_FindObjAt(const OamEntry *objs, int count, int x, int y, int margin_x, int margin_y);
int OamBuffer_ObjContains(const OamEntry *obj, int x, int y, int margin_x, int margin_y);
int OamBuffer_ObjY(const OamEntry *obj);
int OamBuffer_ObjX(const OamEntry *obj);
int OamBuffer_ObjHeight(const OamEntry *obj);
int OamBuffer_ShapeHeight(int shape, int size);
unsigned int OamBuffer_ObjWidth(const OamEntry *obj);
int OamBuffer_ShapeWidth(int shape, int size);
void OamBuffer_DrawCell(int screen, const OamEntry *objs, int x, int y, int palette, int priority, fx32 scale_x, fx32 scale_y,
                        int angle, int obj_mode, int flip_h, int flip_v);
OamEntry *OamBuffer_DrawObjRotated(int screen, const OamEntry *obj, int x, int y, int palette, int priority, fx32 scale,
                                   int angle, int rounded);
int OamBuffer_DrawObjAffine(int screen, const OamEntry *obj, int x, int y, int palette, int priority, const OamAffine *params);
void OamBuffer_Reset(void);
void OamBuffer_Flush(void);
void OamBuffer_Load(void);

#endif
