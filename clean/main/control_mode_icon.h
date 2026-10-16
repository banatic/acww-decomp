/* The control-mode object (data_021d369c, vtable data_020e246c, 0x2c bytes, derived from main's
 * screen sprite base, screen_sprite.h): it keeps whether the player controls the game with the
 * buttons (1) or the touch screen (2), or neither (0) (control_mode.h sets it), and shows an
 * icon of it: animation 0x43 (buttons) or 0x44 (touch) of the table data_020d6fcc, held on its
 * last frame, drawn on the other screen than the 3D one at the base class's place plus the
 * frame's offset. Nothing is drawn for mode 0, nor while flag 1 of the event queue is set
 * (event_queue.h).
 *
 * The talks' process draws, updates, takes down and sets up the object (talk_process.h); its
 * update changes the icon when the mode changed. */
#ifndef CLEAN_MAIN_CONTROL_MODE_ICON_H
#define CLEAN_MAIN_CONTROL_MODE_ICON_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum ControlModeIconMode {
    CONTROL_MODE_ICON_NONE = 0,
    CONTROL_MODE_ICON_BUTTONS = 1,
    CONTROL_MODE_ICON_TOUCH = 2,
};

typedef struct ControlModeIcon {
    ScreenSprite base; /* vtable data_020e246c */
    int mode;          /* 0x0c: ControlModeIconMode */
    int shown_mode;    /* 0x10: the mode the icon was last set for */
    CellAnim anim;     /* 0x14 */
    u8 shown;          /* 0x28: an icon is set (mode 1 or 2) */
    u8 pad_29[3];
} ControlModeIcon;

void ControlModeIcon_SetAnim(ControlModeIcon *icon);
void ControlModeIcon_Rewind(ControlModeIcon *icon);
void ControlModeIcon_Reset(ControlModeIcon *icon);
int ControlModeIcon_IsHidden(ControlModeIcon *icon);
ControlModeIcon *ControlModeIcon_Delete(ControlModeIcon *icon);
ControlModeIcon *ControlModeIcon_Destruct(ControlModeIcon *icon);
ControlModeIcon *ControlModeIcon_Construct(ControlModeIcon *icon);
void ControlModeIcon_Update(ControlModeIcon *icon);
void ControlModeIcon_Draw(ControlModeIcon *icon);
void ControlModeIcon_DrawInstance(void);
void ControlModeIcon_UpdateInstance(void);
void ControlModeIcon_RewindInstance(void);
void ControlModeIcon_ResetInstance(void);
int ControlModeIcon_IsTouch(void);
int ControlModeIcon_IsButtons(void);
void ControlModeIcon_SetTouch(void);
void ControlModeIcon_SetButtons(void);
void ControlModeIcon_SetNone(void);

#endif
