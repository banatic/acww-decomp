/* The small parts of the link state (link_parts.h). */
#include "link_parts.h"

#include "clean.h"
#include "link_scene.h"
#include "packed_bytes.h"

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

/* The fields a change marks (LinkStatePlaceChange's mask). */
#define CHANGE_SCENE 0x1
#define CHANGE_HOLDER 0x2
#define CHANGE_MOVING 0x4

/* An entry's byte 0 carries holder and moving as the 2-bit number of the scene byte. */
#define ENTRY_HOLDER 0x1
#define ENTRY_MOVING 0x2
/* Its byte 1: the fields marked in bits 0-5, the slot in bits 6-7. */
#define ENTRY_MASK 0x3f
#define ENTRY_SHIFT_SLOT 6

/* func_020a7778: a pending change's values and the fields marked. */
void LinkPart_GetChange(const LinkStatePlaceChange *change, u8 *scene, u8 *holder, u8 *moving, u32 *mask)
{
    *scene = change->scene;
    *holder = change->holder;
    *moving = change->moving;
    *mask = change->mask;
}
CLEAN_AS(func_020a7778, LinkPart_GetChange)

/* func_020a7794: the values of the fields `mask` marks taken into a pending change, and those
 * fields marked too (the others keep their values and marks). */
void LinkPart_AddChange(LinkStatePlaceChange *change, u8 scene, u8 holder, u8 moving, u32 mask)
{
    if (mask & CHANGE_SCENE) {
        change->scene = scene;
    }
    if (mask & CHANGE_HOLDER) {
        change->holder = holder;
    }
    if (mask & CHANGE_MOVING) {
        change->moving = moving;
    }
    change->mask |= mask;
}
CLEAN_AS(func_020a7794, LinkPart_AddChange)

/* func_020a77c8: a pending change's destructor (nothing to do). */
void LinkPart_EndChange(LinkStatePlaceChange *change)
{
    (void) change;
}
CLEAN_AS(func_020a77c8, LinkPart_EndChange)

/* func_020a77cc: a pending change's constructor: emptied. */
LinkStatePlaceChange *LinkPart_MakeChange(LinkStatePlaceChange *change)
{
    LinkPart_ResetChange(change);
    return change;
}
CLEAN_AS(func_020a77cc, LinkPart_MakeChange)

/* func_020a77dc: an entry's slot, values and fields marked (LinkPart_UnpackEntry). */
void LinkPart_ReadEntry(const u8 *entry, s32 *slot, u8 *scene, u8 *holder, u8 *moving, s32 *mask)
{
    LinkPart_UnpackEntry(entry, slot, scene, holder, moving, mask);
}
CLEAN_AS(func_020a77dc, LinkPart_ReadEntry)

/* func_020a77f4: an entry made of a slot, values and fields marked (LinkPart_PackEntry). */
void LinkPart_WriteEntry(u8 *entry, int slot, int scene, int holder, u8 moving, int mask)
{
    LinkPart_PackEntry(entry, slot, scene, holder, moving, mask);
}
CLEAN_AS(func_020a77f4, LinkPart_WriteEntry)

/* func_020a7810: an entry's destructor (nothing to do). */
u8 *LinkPart_EndEntry(u8 *entry)
{
    LinkPart_EndEntryBytes();
    return entry;
}
CLEAN_AS(func_020a7810, LinkPart_EndEntry)

/* func_020a7820: an entry's constructor (nothing to do). */
u8 *LinkPart_MakeEntry(u8 *entry)
{
    LinkPart_MakeEntryBytes();
    return entry;
}
CLEAN_AS(func_020a7820, LinkPart_MakeEntry)

/* func_020a7830: an entry's values and fields marked; the slot is read and dropped. */
void LinkPart_ReadEntryChange(const u8 *entry, u8 *scene, u8 *holder, u8 *moving, s32 *mask)
{
    s32 slot;
    LinkPart_UnpackEntry(entry, &slot, scene, holder, moving, mask);
}
CLEAN_AS(func_020a7830, LinkPart_ReadEntryChange)

/* func_020a7850: an entry made of values and fields marked, for slot 0. */
void LinkPart_WriteEntryChange(u8 *entry, int scene, int holder, int moving, int mask)
{
    LinkPart_PackEntry(entry, 0, scene, holder, (u8) moving, mask);
}
CLEAN_AS(func_020a7850, LinkPart_WriteEntryChange)

/* func_020a7870: the destructor of the entry the slotless messages carry (nothing to do). */
u8 *LinkPart_EndEntryB(u8 *entry)
{
    LinkPart_EndEntryBytes();
    return entry;
}
CLEAN_AS(func_020a7870, LinkPart_EndEntryB)

/* func_020a7880: its constructor (nothing to do). */
u8 *LinkPart_MakeEntryB(u8 *entry)
{
    LinkPart_MakeEntryBytes();
    return entry;
}
CLEAN_AS(func_020a7880, LinkPart_MakeEntryB)

/* func_020a7890: an entry's slot, scene, holder and moving (each 0 or 1) and fields marked. */
void LinkPart_UnpackEntry(const u8 *entry, s32 *slot, u8 *scene, u8 *holder, u8 *moving, s32 *mask)
{
    u8 flags;

    PackedBytes_SplitScene(entry, scene, &flags);
    *holder = (flags & ENTRY_HOLDER) != 0;
    *moving = (flags & ENTRY_MOVING) != 0;
    *mask = entry[1] & ENTRY_MASK;
    *slot = (entry[1] >> ENTRY_SHIFT_SLOT) & 3;
}
CLEAN_AS(func_020a7890, LinkPart_UnpackEntry)

/* func_020a78ec: an entry made of a slot, a scene, holder and moving (as flags) and the fields
 * marked. QUIRK: the fields are not masked: bits above 5 spill into the slot's. */
void LinkPart_PackEntry(u8 *entry, int slot, int scene, int holder, u8 moving, int mask)
{
    u8 flags = 0;

    if (holder != 0) {
        flags |= ENTRY_HOLDER;
    }
    if (moving != 0) {
        flags |= ENTRY_MOVING;
    }
    PackedBytes_JoinScene(entry, (u8) scene, flags);
    entry[1] = (u8) ((u32) mask | (((u32) slot << ENTRY_SHIFT_SLOT) & 0xc0));
}
CLEAN_AS(func_020a78ec, LinkPart_PackEntry)

/* func_020a7930: the entry's bytes' destructor (nothing to do). */
void LinkPart_EndEntryBytes(void) {}
CLEAN_AS(func_020a7930, LinkPart_EndEntryBytes)

/* func_020a7934: the entry's bytes' constructor (nothing to do). */
void LinkPart_MakeEntryBytes(void) {}
CLEAN_AS(func_020a7934, LinkPart_MakeEntryBytes)

/* func_020a7938 */
void LinkPart_CopyByte(const u8 *src, u8 *dst)
{
    *dst = *src;
}
CLEAN_AS(func_020a7938, LinkPart_CopyByte)

/* func_020a7940 */
void LinkPart_SetByte(u8 *value, int byte)
{
    *value = (u8) byte;
}
CLEAN_AS(func_020a7940, LinkPart_SetByte)

/* func_020a7944: a one-byte value's destructor (nothing to do). */
void LinkPart_EndByte(u8 *value)
{
    (void) value;
}
CLEAN_AS(func_020a7944, LinkPart_EndByte)

/* func_020a7948: a one-byte value's constructor (nothing to do). */
void LinkPart_MakeByte(u8 *value)
{
    (void) value;
}
CLEAN_AS(func_020a7948, LinkPart_MakeByte)
