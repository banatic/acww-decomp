/* The screen indicators' last sprite (the object at data_021d35f8, vtable data_020e236c, 0x24
 * bytes, derived from main's screen sprite base, screen_sprite.h): a cell drawn on the main
 * engine's screen, appearing with the animation entry 2 of data_020d5b3c and hiding with entry 3.
 * What the cell shows is not known.
 *
 * Its states (ScreenMarkState), stepped by its update (func_0208ee20, through a table of member
 * functions): hidden, until it should show; appearing, until its animation is done; shown, while
 * it should; hiding, until its animation is done. It should show while the main engine is on
 * the bottom screen, no event runs, the scene query's current scene is not 6 and the scene
 * number (func_020960d8(4)) is not 8 to 15 or 0x24 to 0x2c. */
#ifndef CLEAN_MAIN_SCREEN_MARK_H
#define CLEAN_MAIN_SCREEN_MARK_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum ScreenMarkState {
    SCREEN_MARK_HIDDEN = 0,
    SCREEN_MARK_APPEARING = 1,
    SCREEN_MARK_SHOWN = 2,
    SCREEN_MARK_HIDING = 3,
};

typedef struct ScreenMark {
    ScreenSprite base; /* vtable data_020e236c */
    CellAnim anim;     /* 0x0c */
    int state;         /* 0x20: ScreenMarkState */
} ScreenMark;

int ScreenMark_ShouldShow(void);
void ScreenMark_StepHiding(ScreenMark *mark);
void ScreenMark_StepShown(ScreenMark *mark);
void ScreenMark_StepAppearing(ScreenMark *mark);
void ScreenMark_StepHidden(ScreenMark *mark);
void ScreenMark_DrawInstance(void);
void ScreenMark_UpdateInstance(void);
void ScreenMark_RewindInstance(void);

#endif
