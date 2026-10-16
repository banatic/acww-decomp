/* main's screen sprite base (screen_sprite.h). */
#include "screen_sprite.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"

static_assert(sizeof(ScreenSprite) == 0xc, "ScreenSprite");

extern const u32 data_020e20c8[]; /* the class's vtable */

/* func_0208aeec */
int ScreenSprite_Y(ScreenSprite *sprite)
{
    return sprite->y;
}
CLEAN_AS(func_0208aeec, ScreenSprite_Y)

/* func_0208aef0 */
int ScreenSprite_X(ScreenSprite *sprite)
{
    return sprite->x;
}
CLEAN_AS(func_0208aef0, ScreenSprite_X)

/* func_0208aef4 (vtable slot 4): placed at (x, y) from the screen's centre. The original
 * declares both as byte pointers; they are plain numbers. */
void ScreenSprite_SetPlace(ScreenSprite *sprite, u32 x, u32 y)
{
    sprite->x = (int) (x + SCREEN_SPRITE_CENTER_X);
    sprite->y = (int) (y + SCREEN_SPRITE_CENTER_Y);
}
CLEAN_AS(func_0208aef4, ScreenSprite_SetPlace)

/* func_0208af00: the destructor, as a derived class's destructor calls it. */
void ScreenSprite_DestructBase(ScreenSprite *sprite)
{
    sprite->vtable = data_020e20c8;
}
CLEAN_AS(func_0208af00, ScreenSprite_DestructBase)

/* func_0208af0c (vtable slot 1): destructed and freed. */
ScreenSprite *ScreenSprite_Delete(ScreenSprite *sprite)
{
    sprite->vtable = data_020e20c8;
    Heap_OperatorDeleteB(sprite);
    return sprite;
}
CLEAN_AS(func_0208af0c, ScreenSprite_Delete)

/* func_0208af24 (vtable slot 0): the destructor. */
void ScreenSprite_Destruct(ScreenSprite *sprite)
{
    sprite->vtable = data_020e20c8;
}
CLEAN_AS(func_0208af24, ScreenSprite_Destruct)

/* func_0208af30: the constructor: at the screen's centre. */
void ScreenSprite_Construct(ScreenSprite *sprite)
{
    sprite->vtable = data_020e20c8;
    sprite->x = SCREEN_SPRITE_CENTER_X;
    sprite->y = SCREEN_SPRITE_CENTER_Y;
}
CLEAN_AS(func_0208af30, ScreenSprite_Construct)
