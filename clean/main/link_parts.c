/* The small parts of the link state (link_parts.h). */
#include "link_parts.h"

#include "clean.h"
#include "link_scene.h"

#define STATUS_FIELD_ANSWER 0x07 /* bits 0-2 */
#define STATUS_FIELD_KIND 0xe0   /* bits 5-7 */
#define STATUS_SHIFT_KIND 5
#define STATUS_SHIFT_SLOT 3

/* func_020a7684: a status byte's answer, kind and slot served. The byte is read again for
 * each field, after the field before it is written. */
void LinkPart_UnpackStatusByte(const u8 *byte, u32 *answer, u32 *kind, u32 *slot)
{
    *answer = *byte & STATUS_FIELD_ANSWER;
    *kind = (u32) (*byte >> STATUS_SHIFT_KIND) & 7;
    *slot = (u32) (*byte >> STATUS_SHIFT_SLOT) & 3;
}
CLEAN_AS(func_020a7684, LinkPart_UnpackStatusByte)

/* func_020a76ac: a status byte made of an answer, a kind and the slot served.
 * QUIRK: the slot is not masked: a slot above 3 spills into the kind's bits. */
void LinkPart_PackStatusByte(u8 *byte, int answer, int kind, int slot)
{
    *byte = (u8) (((u32) answer & STATUS_FIELD_ANSWER) | (((u32) kind << STATUS_SHIFT_KIND) & STATUS_FIELD_KIND) |
                  ((u32) slot << STATUS_SHIFT_SLOT));
}
CLEAN_AS(func_020a76ac, LinkPart_PackStatusByte)

/* func_020a76c8: a status byte's destructor (nothing to do). */
void LinkPart_EndStatusByte(u8 *byte)
{
    (void) byte;
}
CLEAN_AS(func_020a76c8, LinkPart_EndStatusByte)

/* func_020a76cc: a status byte's constructor (nothing to do). */
void LinkPart_MakeStatusByte(u8 *byte)
{
    (void) byte;
}
CLEAN_AS(func_020a76cc, LinkPart_MakeStatusByte)

/* func_020a76d0 */
void LinkPart_ClearArrived(u32 *arrived)
{
    *arrived = 0;
}
CLEAN_AS(func_020a76d0, LinkPart_ClearArrived)

/* func_020a76d8 */
void LinkPart_GetArrived(const u32 *arrived, u32 *value)
{
    *value = *arrived;
}
CLEAN_AS(func_020a76d8, LinkPart_GetArrived)

/* func_020a76e0 */
void LinkPart_SetArrived(u32 *arrived, int value)
{
    *arrived = (u32) value;
}
CLEAN_AS(func_020a76e0, LinkPart_SetArrived)

/* func_020a76e4: an arrived word's destructor (nothing to do). */
void LinkPart_EndArrived(u32 *arrived)
{
    (void) arrived;
}
CLEAN_AS(func_020a76e4, LinkPart_EndArrived)

/* func_020a76e8: an arrived word's constructor: cleared. */
u32 *LinkPart_MakeArrived(u32 *arrived)
{
    LinkPart_ClearArrived(arrived);
    return arrived;
}
CLEAN_AS(func_020a76e8, LinkPart_MakeArrived)

/* func_020a76f8: a move emptied: no slot, no scene. */
void LinkPart_ResetMove(LinkStateMove *move)
{
    move->slot = LINK_STATE_SLOTS;
    move->scene = LINK_SCENE_NONE;
}
CLEAN_AS(func_020a76f8, LinkPart_ResetMove)

/* func_020a7704 */
void LinkPart_GetMove(const LinkStateMove *move, s32 *slot, u8 *scene)
{
    *slot = move->slot;
    *scene = move->scene;
}
CLEAN_AS(func_020a7704, LinkPart_GetMove)

/* func_020a7710 */
void LinkPart_SetMove(LinkStateMove *move, int slot, int scene)
{
    move->slot = slot;
    move->scene = (u8) scene;
}
CLEAN_AS(func_020a7710, LinkPart_SetMove)

/* func_020a7718: a move's destructor (nothing to do). */
void LinkPart_EndMove(LinkStateMove *move)
{
    (void) move;
}
CLEAN_AS(func_020a7718, LinkPart_EndMove)

/* func_020a771c: a move's constructor: emptied. */
LinkStateMove *LinkPart_MakeMove(LinkStateMove *move)
{
    LinkPart_ResetMove(move);
    return move;
}
CLEAN_AS(func_020a771c, LinkPart_MakeMove)

/* func_020a772c: a place emptied: no scene, not holding it, not moving. */
void LinkPart_ResetPlace(LinkStatePlace *place)
{
    place->scene = LINK_SCENE_NONE;
    place->holder = 0;
    place->moving = 0;
}
CLEAN_AS(func_020a772c, LinkPart_ResetPlace)

/* func_020a7738 */
void LinkPart_GetPlace(const LinkStatePlace *place, u8 *scene, u8 *holder, u8 *moving)
{
    *scene = place->scene;
    *holder = place->holder;
    *moving = place->moving;
}
CLEAN_AS(func_020a7738, LinkPart_GetPlace)

/* func_020a774c */
void LinkPart_SetPlace(LinkStatePlace *place, int scene, int holder, int moving)
{
    place->scene = (u8) scene;
    place->holder = (u8) holder;
    place->moving = (u8) moving;
}
CLEAN_AS(func_020a774c, LinkPart_SetPlace)

/* func_020a7754: a place's destructor (nothing to do). */
void LinkPart_EndPlace(LinkStatePlace *place)
{
    (void) place;
}
CLEAN_AS(func_020a7754, LinkPart_EndPlace)

/* func_020a7758: a place's constructor: emptied. */
LinkStatePlace *LinkPart_MakePlace(LinkStatePlace *place)
{
    LinkPart_ResetPlace(place);
    return place;
}
CLEAN_AS(func_020a7758, LinkPart_MakePlace)

/* func_020a7768: a pending change emptied: no scene, holder and moving 0, no field marked.
 * Byte 3 is left as it was. */
void LinkPart_ResetChange(LinkStatePlaceChange *change)
{
    change->scene = LINK_SCENE_NONE;
    change->holder = 0;
    change->moving = 0;
    change->mask = 0;
}
CLEAN_AS(func_020a7768, LinkPart_ResetChange)
