/* The message box of a talk (0x80 bytes, at 0x1c of a talk, talk_object.h): the window's
 * background on BG2 of the main screen, the arrow that waits for the player and the spinner.
 *
 * - Its background comes from /a_mes/: the screen (a_mes0a_bg_nsc.bin with the speaker's name
 *   plate, a_mes0b_bg_nsc.bin without), the palette (a_mes_bg_ncl.bin) and the characters
 *   (a_mes_bg_ncg.bin), read into the current heap (TalkBox_Load), recoloured by the talk's
 *   kind or the speaker, uploaded to BG2 (TalkBox_Upload) and freed again (TalkBox_FreeFiles).
 *   BG2 is scrolled by the box's place, and window 0 of the main screen follows it
 *   (TalkBox_SetPlace).
 * - The arrow (a CellPairSprite, cell_pair_sprite.h) shows that the talk waits for the player:
 *   hidden (pose 0), waiting (pose 1), then poses 2 and 3 as the player goes on, each played
 *   to its end before the talk takes the next step (func_02066dc4).
 * - The spinner (talk_spinner.h): while it spins, and for TALK_BOX_SPINNER_HOLD frames after
 *   it stops, the arrow's poses do not count as reached. */
#ifndef CLEAN_MAIN_TALK_BOX_H
#define CLEAN_MAIN_TALK_BOX_H

#include "cell_pair_sprite.h"
#include "talk_spinner.h"
#include "types.h"

/* The arrow's poses (CellPairSprite.pose). */
enum TalkBoxArrowPose {
    TALK_BOX_ARROW_HIDDEN = 0,
    TALK_BOX_ARROW_WAITING = 1,
    TALK_BOX_ARROW_POSE_2 = 2,
    TALK_BOX_ARROW_POSE_3 = 3,
};

/* TalkBox.spinner_hold: the frames the arrow still waits after the spinner stopped, and the
 * value it keeps while the spinner spins. */
#define TALK_BOX_SPINNER_HOLD 4
#define TALK_BOX_SPINNING (-1)

typedef struct TalkBox {
    u16 *screen;          /* 0x00: the screen of BG2 (0x800 bytes), or NULL */
    u16 *palette;         /* 0x04: the palette (0x180 bytes), or NULL */
    u8 *characters;       /* 0x08: the characters (0x2800 bytes), or NULL */
    CellPairSprite arrow; /* 0x0c */
    TalkSpinner spinner;  /* 0x50 */
    s32 x;                /* 0x74: the box's place, the scroll of BG2 */
    s32 y;                /* 0x78 */
    s32 spinner_hold;     /* 0x7c: TALK_BOX_SPINNING, or the frames left after the spinner stopped */
} TalkBox;

u8 TalkBox_TextColour(int colour);
int TalkBox_DrawSpinner(TalkBox *box);
void TalkBox_UpdateSpinner(TalkBox *box);
void TalkBox_StopSpinner(TalkBox *box);
void TalkBox_StartSpinner(TalkBox *box, int sound);
int TalkBox_ArrowPose3Done(TalkBox *box);
int TalkBox_ArrowPose2Done(TalkBox *box);
int TalkBox_ArrowWaiting(TalkBox *box);
int TalkBox_ArrowHidden(TalkBox *box);
void TalkBox_DrawArrow(TalkBox *box);
void TalkBox_UpdateArrow(TalkBox *box);
void TalkBox_SetArrowPose3(TalkBox *box);
void TalkBox_SetArrowPose2(TalkBox *box);
void TalkBox_ShowArrow(TalkBox *box);
void TalkBox_HideArrow(TalkBox *box);
void TalkBox_SetPlace(TalkBox *box, int x, int y);
void TalkBox_SetOffset(TalkBox *box, int y);
void TalkBox_Hide(TalkBox *box);
void TalkBox_Show(void);
void TalkBox_Upload(TalkBox *box);
void TalkBox_SetUpBg2(void);
void TalkBox_FreeFiles(TalkBox *box);
int TalkBox_Load(TalkBox *box, int kind, int nameless, int style, u8 no_villager);
void TalkBox_ColourText(TalkBox *box, int kind);
void TalkBox_ColourPlate(TalkBox *box, int style, int no_villager);
int TalkBox_LoadCharacters(TalkBox *box, void *file);
int TalkBox_LoadPalette(TalkBox *box, void *file);
int TalkBox_LoadScreen(TalkBox *box, void *file, int with_plate);
void TalkBox_Draw(TalkBox *box);
void TalkBox_Update(TalkBox *box);
TalkBox *TalkBox_Destruct(TalkBox *box);
TalkBox *TalkBox_Construct(TalkBox *box);

#endif
