/* The wireless signal icon (the object at data_0213ff98): while a wireless library is in use
 * (autoload_2/network.h: a mode other than 0 and 6) it slides in from the left over four steps
 * and shows the link level as one of four frames of animation 1 (data_020d5b3c), at (0x80,
 * 0x60) plus the slide. It has two sets of graphics, one for the Wi-Fi Connection (modes 3 and
 * 4) and one for the local wireless library, swapped while it is out of view.
 *
 * Like the animated screen icon (screen_icon.h), it goes out of view when state flag 4 is set
 * and may show again after a delay. func_0208af44, func_0208af60, func_0208af7c and
 * func_0208af98 draw, update, rewind and reset it with the game's other screen indicators. */
#ifndef CLEAN_MAIN_WIRELESS_ICON_H
#define CLEAN_MAIN_WIRELESS_ICON_H

#include "types.h"

#define WIRELESS_ICON_STEPS 4

typedef struct WirelessIcon {
    int frame;       /* 0x00: frame of the signal animation, 0 (link level 3) to 3 (none) */
    int slide_x;     /* 0x04: from the slide table, by `step` */
    u32 step;        /* 0x08: 0 out of view to 4 fully in */
    fx32 flag_value; /* 0x0c: StateFlags_ValueOrOne in the frame before */
    int delay;       /* 0x10: frames before the icon may show again */
    u8 flag4;        /* 0x14: state flag 4 in the frame before */
    u8 wfc_graphics; /* 0x15: the graphics loaded are the Wi-Fi Connection's */
} WirelessIcon;

void WirelessIcon_AfterUpdate(WirelessIcon *icon);
void WirelessIcon_Slide(WirelessIcon *icon);
void WirelessIcon_TrackFlag(WirelessIcon *icon);
int WirelessIcon_GraphicsMatch(WirelessIcon *icon);
int WirelessIcon_IsActive(WirelessIcon *icon);
void WirelessIcon_Draw(WirelessIcon *icon);
void WirelessIcon_Update(WirelessIcon *icon);
void WirelessIcon_Rewind(WirelessIcon *icon);
void WirelessIcon_Reset(WirelessIcon *icon);
void WirelessIcon_Destruct(WirelessIcon *icon);
void WirelessIcon_Construct(WirelessIcon *icon);
void WirelessIcons_Draw(void);
void WirelessIcons_Update(void);
void WirelessIcons_Rewind(void);
void WirelessIcons_Reset(void);

#endif
