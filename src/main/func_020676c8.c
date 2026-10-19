/* func_020676c8 @ 0x020676c8, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef enum NNSG2dAnimationPlayMode {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0x0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_MAX
} NNSG2dAnimationPlayMode;

typedef struct NNSG2dAnimFrameData {
    void *pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrameData;

typedef struct NNSG2dAnimSequenceData {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    NNSG2dAnimationPlayMode playMode;
    NNSG2dAnimFrameData *pAnmFrameArray;
} NNSG2dAnimSequenceData;

typedef struct NNSG2dAnimBankData {
    u16 numSequences;
    u16 numTotalFrames;
    NNSG2dAnimSequenceData *pSequenceArrayHead;
    NNSG2dAnimFrameData *pFrameArrayHead;
    void *pAnimContents;
    void *pStringBank;
    void *pExtendedData;
} NNSG2dAnimBankData;

typedef enum NNSG2dEntityType {
    NNS_G2D_ENTITYTYPE_INVALID = 0,
    NNS_G2D_ENTITYTYPE_CELL,
    NNS_G2D_ENTITYTYPE_MULTICELL,
    NNS_G2D_ENTITYTYPE_MAX
} NNSG2dEntityType;

typedef struct NNSG2dEntityAnimData {
    u16 numAnimSequence;
    u16 pad16;
    u16 *pAnimSequenceIdxArray;
} NNSG2dEntityAnimData;

typedef struct NNSG2dEntityData {
    NNSG2dEntityAnimData animData;
    NNSG2dEntityType type;
} NNSG2dEntityData;

typedef struct NNSG2dPaletteSwapTable {
    u16 paletteIndex[16];
} NNSG2dPaletteSwapTable;

typedef struct NNSG2dEntity {
    void *pDrawStuff;
    const NNSG2dEntityData *pEntityData;
    const NNSG2dAnimBankData *pAnimDataBank;
    u16 currentSequenceIdx;
    u16 pad_0E;
    NNSG2dPaletteSwapTable *pPaletteTbl;
} NNSG2dEntity;

void func_020676c8(NNSG2dEntity *pEntity);

void func_020676c8(NNSG2dEntity *pEntity)
{
    ((void) 0);
    pEntity->pPaletteTbl = ((void *) 0);
}
