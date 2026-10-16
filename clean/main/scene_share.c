/* A scene object's state shared with the other systems of a session (scene_share.h). */
#include "scene_share.h"

#include "clean.h"
#include "packed_bytes.h"
#include "session.h"
#include "session_record.h"

static_assert(offsetof(SceneShareEntry, place) == 0x04, "SceneShareEntry layout");
static_assert(offsetof(SceneShareEntry, extra) == 0x0b, "SceneShareEntry layout");
static_assert(offsetof(SceneShareEntry, note) == 0x11, "SceneShareEntry layout");
static_assert(sizeof(SceneShareEntry) == 0x1e, "SceneShareEntry layout");

extern NetSession *data_020ccf94;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The person's shared record, or null (scene_share.h). */
extern SceneShareEntry *func_02085148(u16 *person);
/* Its entry's in-use byte set, the scene, the place, the angle, the 15 bytes of the motion's
 * note and the four extra bytes written. */
extern int func_020851a0(u16 *person, int scene, const Vec3 *position, int angle, const void *note, const void *extra);
/* Its entry's in-use byte set and the owner and holder written. */
extern int func_02085174(u16 *person, int owner, int holder);
/* As func_02085174, then, while this system's slot is taken, the record updated (with
 * `value`'s address). */
extern void func_020850e8(int value, int owner, int holder, u16 *person);
/* The record's owner and holder, when it is in use. */
extern int func_020850b8(int *owner, int *holder, u16 *person);
/* The person's index (the object's halfword at 0x632). */
extern u16 func_0201c444(void *object);
/* The scene shown. */
extern u8 func_020b65c4(void);
/* Nonzero always without a session slot. */
extern int func_020a7278(void);

/* The object's parts used here. */
#define SCENE_SHARE_OBJECT_POSITION 0x5c /* Vec3 */
#define SCENE_SHARE_OBJECT_ANGLE 0x8e    /* s16 */
#define SCENE_SHARE_OBJECT_PERSON 0xea   /* u16 */
#define SCENE_SHARE_OBJECT_LOCAL 0x563   /* u8: nonzero: not shared */
#define SCENE_SHARE_OBJECT_NOTE 0x568    /* the motion's note (its member at 0x564, from 0x04) */
#define SCENE_SHARE_OBJECT_EXTRA 0x62d   /* u8[4] */

/* The first session record of each kind of person. */
#define SCENE_SHARE_RECORDS_E 12
#define SCENE_SHARE_RECORDS_D 32

static u16 *scene_share_person(u8 *object)
{
    return (u16 *) (void *) (object + SCENE_SHARE_OBJECT_PERSON);
}

static int scene_share_kind(u8 *object)
{
    return (*scene_share_person(object) & 0xf000) >> 12;
}

/* The person's record updated with `value`'s address (none for other kinds of person). */
static void scene_share_send(u8 *object, int *value)
{
    int kind = scene_share_kind(object);
    if (kind == SCENE_SHARE_KIND_E) {
        SessionRecord_Update(func_0201c444(object) + SCENE_SHARE_RECORDS_E, value, 0, 0);
    } else if (kind == SCENE_SHARE_KIND_D) {
        SessionRecord_Update(func_0201c444(object) + SCENE_SHARE_RECORDS_D, value, 0, 0);
    }
}

/* Whether this system's slot is taken in the session. */
static int scene_share_slot_taken(void)
{
    NetSession *session = data_020ccf94;
    return Session_IsSlotTaken(session, session->local_slot) != 0;
}

/* func_0201beb0: the kind, the priority and the 13 bytes of the motion noted in the record.
 * 0 without a record. */
int SceneShare_ReadNote(u8 *object, int *kind, int *priority, u8 *note)
{
    SceneShareEntry *entry = func_02085148(scene_share_person(object));
    if (entry == NULL) {
        return 0;
    }
    *kind = entry->note_kind;
    *priority = entry->note_priority;
    MI_CpuCopy8(entry->note, note, SCENE_SHARE_NOTE_SIZE);
    return 1;
}
CLEAN_AS(func_0201beb0, SceneShare_ReadNote)

/* func_0201bee0: the x and z of the place in the record (the y is left) and its angle. 0 when
 * the object is not shared or has no record. */
int SceneShare_ReadPlace(u8 *object, Vec3 *point, s16 *angle)
{
    if (object[SCENE_SHARE_OBJECT_LOCAL] != 0) {
        return 0;
    }
    SceneShareEntry *entry = func_02085148(scene_share_person(object));
    if (entry == NULL) {
        return 0;
    }
    PackedBytes_UnpackPoint(entry->place, (u32 *) (void *) &point->x, (u32 *) (void *) &point->z);
    MI_CpuCopy8(entry->angle, angle, sizeof(*angle));
    return 1;
}
CLEAN_AS(func_0201bee0, SceneShare_ReadPlace)

/* func_0201bf24: the person's entry gets the scene shown, the object's position and angle, its
 * motion's note and its extra bytes; while this system's slot is taken and the object is ours,
 * the record is updated with `value`'s address. */
void SceneShare_Publish(u8 *object, int value)
{
    int scene = func_020b65c4();
    func_020851a0(scene_share_person(object), scene, (const Vec3 *) (const void *) (object + SCENE_SHARE_OBJECT_POSITION),
                  *(const s16 *) (const void *) (object + SCENE_SHARE_OBJECT_ANGLE), object + SCENE_SHARE_OBJECT_NOTE,
                  object + SCENE_SHARE_OBJECT_EXTRA);
    if (!scene_share_slot_taken() || SceneShare_IsOurs(object) == 0) {
        return;
    }
    scene_share_send(object, &value);
}
CLEAN_AS(func_0201bf24, SceneShare_Publish)

/* func_0201bfbc: up to four of `bytes` into the object's extra bytes.
 * QUIRK: a negative `size` is handed to MI_CpuCopy8 as it is. */
void SceneShare_SetExtra(u8 *object, const u8 *bytes, int size)
{
    if (size > SCENE_SHARE_EXTRA_SIZE) {
        size = SCENE_SHARE_EXTRA_SIZE;
    }
    MI_CpuCopy8(bytes, object + SCENE_SHARE_OBJECT_EXTRA, (u32) size);
}
CLEAN_AS(func_0201bfbc, SceneShare_SetExtra)

/* func_0201bfd8: up to four of the record's extra bytes into `out`. 0 when the object is not
 * shared or has no record. */
int SceneShare_ReadExtra(u8 *object, u8 *out, u32 size)
{
    if (object[SCENE_SHARE_OBJECT_LOCAL] != 0) {
        return 0;
    }
    SceneShareEntry *entry = func_02085148(scene_share_person(object));
    if (size > SCENE_SHARE_EXTRA_SIZE) {
        size = SCENE_SHARE_EXTRA_SIZE;
    }
    if (entry == NULL) {
        return 0;
    }
    MI_CpuCopy8(entry->extra, out, size);
    return 1;
}
CLEAN_AS(func_0201bfd8, SceneShare_ReadExtra)

/* func_0201c014: whether the record in use names a system holding the object. */
int SceneShare_IsHeld(u8 *object)
{
    int owner = SCENE_SHARE_NO_SLOT;
    int holder = SCENE_SHARE_NO_SLOT;
    if (SceneShare_ReadSlots(object, &owner, &holder) == 0) {
        return 0;
    }
    return holder < SCENE_SHARE_NO_SLOT;
}
CLEAN_AS(func_0201c014, SceneShare_IsHeld)

/* func_0201c040: the record's owner and holder, when it is in use (else 0, and nothing
 * written). */
int SceneShare_ReadSlots(u8 *object, int *owner, int *holder)
{
    return func_020850b8(owner, holder, scene_share_person(object));
}
CLEAN_AS(func_0201c040, SceneShare_ReadSlots)

/* func_0201c054: the owner and holder into the person's entry; while this system's slot is
 * taken and the object is ours, the record is updated with `value`'s address. */
void SceneShare_SetSlotsIfOurs(u8 *object, int value, int owner, int holder)
{
    func_02085174(scene_share_person(object), owner, holder);
    if (!scene_share_slot_taken() || SceneShare_IsOurs(object) == 0) {
        return;
    }
    scene_share_send(object, &value);
}
CLEAN_AS(func_0201c054, SceneShare_SetSlotsIfOurs)

/* func_0201c0c8: the owner and holder into the person's entry, and the record updated while
 * this system's slot is taken, ours or not (func_020850e8). */
void SceneShare_SetSlots(u8 *object, u32 value, u32 owner, u32 holder)
{
    func_020850e8((int) value, (int) owner, (int) holder, scene_share_person(object));
}
CLEAN_AS(func_0201c0c8, SceneShare_SetSlots)

/* func_0201c0e0: whether this system runs the object: always without a link or when the
 * object is not shared; else when the record is in use and its owner is this system's slot,
 * or it has no owner and func_020a7278 answers nonzero. */
int SceneShare_IsOurs(u8 *object)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) == 0 || object[SCENE_SHARE_OBJECT_LOCAL] != 0) {
        return 1;
    }
    SceneShareEntry *entry = func_02085148(scene_share_person(object));
    if (entry == NULL || entry->in_use == 0) {
        return 0;
    }
    if (entry->owner == SCENE_SHARE_NO_SLOT && func_020a7278() != 0) {
        return 1;
    }
    return entry->owner == session->local_slot;
}
CLEAN_AS(func_0201c0e0, SceneShare_IsOurs)
