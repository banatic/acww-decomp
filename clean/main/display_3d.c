/* The 3D engine's set-up (display_3d.h). */
#include "display_3d.h"

#include <assert.h>

#include "clean.h"

#define REG16(addr) (*(volatile u16 *) (addr))
#define REG32(addr) (*(volatile u32 *) (addr))

#define REG_DISP3DCNT 0x04000060u
#define REG_ALPHA_TEST_REF 0x04000340u
#define REG_MTX_MODE 0x04000440u
#define REG_MTX_STORE 0x0400044cu
#define REG_MTX_IDENTITY 0x04000454u
#define REG_SWAP_BUFFERS 0x04000540u
#define REG_VIEWPORT 0x04000580u

/* DISP3DCNT */
#define DISP3D_HIGHLIGHT 0x0002 /* highlight shading instead of toon shading */
#define DISP3D_ALPHA_TEST 0x0004
#define DISP3D_ALPHA_BLEND 0x0008
#define DISP3D_ANTIALIAS 0x0010
#define DISP3D_EDGE_MARKING 0x0020
#define DISP3D_ACK_BITS 0x3000 /* writing 1 acknowledges an error: kept 0 by every write */

#define MTX_MODE_POSITION_VECTOR 2
#define MTX_MODE_TEXTURE 3
#define SWAP_MANUAL_SORT 1
#define SWAP_W_BUFFER 2

#define CLEAR_DEPTH_MAX 0x7fff
#define POLYGON_ID_OPAQUE 0x3f
#define FX32_ONE 0x1000

#define GX_VRAM_TEX_BC 6       /* VRAM banks B and C for textures */
#define GX_VRAM_TEXPLTT_F 0x10 /* bank F for texture palettes */

/* The toon table: 32 colours. */
typedef struct ToonTable {
    u16 colors[32];
} ToonTable;

static_assert(sizeof(ToonTable) == 0x40, "ToonTable layout");

extern u16 data_0213feac;             /* the clear colour */
extern int data_0213feb0;             /* the clear depth */
extern Mtx43 data_0213fee4;           /* the view matrix */
extern Mtx43 data_0213feb4;           /* its inverse */
extern const ToonTable data_020d5ca4; /* the game's toon table */
extern const Mtx43 data_02138f8c;     /* the view matrix at start-up */

extern void G3X_SetClearColor(u32 color, u32 alpha, u32 depth, u32 polygon_id, u32 fog);
extern void G3X_SetToonTable(const void *table);
extern void G3X_Reset(void);
extern void G3X_Init(void);
extern void G3X_InitTable(void);
extern void G3X_InitMtxStack(void);
extern void G3i_PerspectiveW_(u32 fovy_sin, u32 fovy_cos, u32 aspect, u32 near, u32 far, u32 scale_w, u32 load, u32 mtx);
extern void NNS_G3dInit(void);
extern void DC_FlushRange(const void *start, u32 size);
extern int MTX_Inverse43(const Mtx43 *mtx, Mtx43 *inverse);
extern void GX_SetBankForTex(int banks);
extern void GX_SetBankForTexPltt(int banks);
extern void OS_EnableDTCM(void);

/* func_02002e14: the clear colour and depth, transparent, with the opaque polygon ID and fog. */
void Display3D_ApplyClearColor(void)
{
    G3X_SetClearColor(data_0213feac, 0, (u32) data_0213feb0, POLYGON_ID_OPAQUE, 1);
}
CLEAN_AS(func_02002e14, Display3D_ApplyClearColor)

/* func_02002e3c: the colour Display3D_ApplyClearColor clears to. */
void Display3D_SetClearColor(u16 color)
{
    data_0213feac = color;
}
CLEAN_AS(func_02002e3c, Display3D_SetClearColor)

/* func_02002e48 */
void Display3D_SetClearDepth(int depth)
{
    data_0213feb0 = depth;
}
CLEAN_AS(func_02002e48, Display3D_SetClearDepth)

/* func_02002e54: toon shading, with the game's toon table (uploaded from a copy on the stack).
 * HW: DISP3DCNT is written before the table. */
void Display3D_LoadToonTable(void)
{
    ToonTable table = data_020d5ca4;

    DC_FlushRange(&table, sizeof(table));
    REG16(REG_DISP3DCNT) = REG16(REG_DISP3DCNT) & (u16) ~(DISP3D_ACK_BITS | DISP3D_HIGHLIGHT);
    G3X_SetToonTable(&table);
}
CLEAN_AS(func_02002e54, Display3D_LoadToonTable)

/* func_02002e98 */
void Display3D_SetViewMatrix(const Mtx43 *view)
{
    data_0213fee4 = *view;
    MTX_Inverse43(&data_0213fee4, &data_0213feb4);
}
CLEAN_AS(func_02002e98, Display3D_SetViewMatrix)

/* func_02002ec0: reset the 3D engine and load the identity as the texture matrix, leaving the
 * position and vector matrices current.
 * HW: in this order. */
void Display3D_Reset(void)
{
    G3X_Reset();
    REG32(REG_MTX_MODE) = MTX_MODE_TEXTURE;
    REG32(REG_MTX_IDENTITY) = 0;
    REG32(REG_MTX_MODE) = MTX_MODE_POSITION_VECTOR;
}
CLEAN_AS(func_02002ec0, Display3D_Reset)

/* func_02002ee8: at start-up: the engine, the texture VRAM, the DTCM, alpha testing (against
 * 0) and alpha blending, a black clear with polygon ID 0 (not stored for
 * Display3D_ApplyClearColor), and the view matrix.
 * HW: in this order. */
void Display3D_Init(void)
{
    Display3D_InitEngine();
    GX_SetBankForTex(GX_VRAM_TEX_BC);
    GX_SetBankForTexPltt(GX_VRAM_TEXPLTT_F);
    OS_EnableDTCM();
    REG16(REG_DISP3DCNT) = (REG16(REG_DISP3DCNT) & (u16) ~DISP3D_ACK_BITS) | DISP3D_ALPHA_TEST;
    REG16(REG_ALPHA_TEST_REF) = 0;
    REG16(REG_DISP3DCNT) = (REG16(REG_DISP3DCNT) & (u16) ~DISP3D_ACK_BITS) | DISP3D_ALPHA_BLEND;
    G3X_SetClearColor(0, 0, CLEAR_DEPTH_MAX, 0, 1);
    data_0213fee4 = data_02138f8c;
    MTX_Inverse43(&data_0213fee4, &data_0213feb4);
}
CLEAN_AS(func_02002ee8, Display3D_Init)

/* func_02002f68: initialise the 3D engine and NitroSystem's G3D: toon shading, anti-aliasing
 * and alpha blending without edge marking, the whole screen as the viewport, a perspective
 * projection (half the vertical field of view 20 degrees, aspect 4:3, near 1, far 1000) stored
 * in matrix stack slot 0, manual translucent sorting with W-buffering, the toon table, and a
 * black clear (stored as colour 0, depth 0x7fff for Display3D_ApplyClearColor).
 * HW: in this order. */
void Display3D_InitEngine(void)
{
    G3X_Init();
    G3X_InitTable();
    G3X_InitMtxStack();
    REG16(REG_DISP3DCNT) = REG16(REG_DISP3DCNT) & (u16) ~(DISP3D_ACK_BITS | DISP3D_HIGHLIGHT);
    REG16(REG_DISP3DCNT) = (REG16(REG_DISP3DCNT) & (u16) ~DISP3D_ACK_BITS) | DISP3D_ANTIALIAS;
    REG16(REG_DISP3DCNT) = (REG16(REG_DISP3DCNT) & (u16) ~DISP3D_ACK_BITS) | DISP3D_ALPHA_BLEND;
    REG16(REG_DISP3DCNT) = REG16(REG_DISP3DCNT) & (u16) ~(DISP3D_ACK_BITS | DISP3D_EDGE_MARKING);
    REG32(REG_VIEWPORT) = 191u << 24 | 255u << 16 | 0 << 8 | 0; /* x 0-255, y 0-191 */
    G3i_PerspectiveW_(0x579 /* sin 20 degrees */, 0xf09 /* cos */, 0x1555 /* 4/3 */, FX32_ONE, 1000 * FX32_ONE, FX32_ONE, 1,
                      0);
    REG32(REG_MTX_STORE) = 0;
    REG32(REG_SWAP_BUFFERS) = SWAP_MANUAL_SORT | SWAP_W_BUFFER;
    NNS_G3dInit();
    Display3D_LoadToonTable();
    G3X_SetClearColor(0, 0, CLEAR_DEPTH_MAX, POLYGON_ID_OPAQUE, 1);
    data_0213feac = 0;
    data_0213feb0 = CLEAR_DEPTH_MAX;
}
CLEAN_AS(func_02002f68, Display3D_InitEngine)
