/* main's screen sprite base (vtable data_020e20c8, 0xc bytes): the base class of the sprites drawn
 * over a screen, CellPairSprite (cell_pair_sprite.h) and SlidingWindow (sliding_window.h)
 * among them. It keeps a place relative to the screen's centre (0x80, 0x60); vtable slot 4
 * (ScreenSprite_SetPlace) moves it there. */
#ifndef CLEAN_MAIN_SCREEN_SPRITE_H
#define CLEAN_MAIN_SCREEN_SPRITE_H

#include "types.h"

#define SCREEN_SPRITE_CENTER_X 0x80
#define SCREEN_SPRITE_CENTER_Y 0x60

typedef struct ScreenSprite {
    const u32 *vtable; /* data_020e20c8, or a derived class's */
    int x;             /* 0x04: the place on the screen */
    int y;             /* 0x08 */
} ScreenSprite;

int ScreenSprite_Y(ScreenSprite *sprite);
int ScreenSprite_X(ScreenSprite *sprite);
void ScreenSprite_SetPlace(ScreenSprite *sprite, u32 x, u32 y);
void ScreenSprite_DestructBase(ScreenSprite *sprite);
ScreenSprite *ScreenSprite_Delete(ScreenSprite *sprite);
void ScreenSprite_Destruct(ScreenSprite *sprite);
void ScreenSprite_Construct(ScreenSprite *sprite);

#endif
