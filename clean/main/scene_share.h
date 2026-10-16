/* A scene object's state shared with the other systems of a multiplayer session (class
 * 0x020d8c64, obj_020d8c64.h; session.h, session_record.h).
 *
 * The object is a person: its code at 0xea has the kind in its top four bits and an index in
 * the rest (func_0201c444 gives the index, kept at 0x632). A person of kind 0xe has shared
 * record 12 + index (index below 8), one of kind 0xd record 32 + index (below 38); other kinds
 * have none. func_02085148 finds the record in the session's table (a SceneShareEntry), and
 * the writers func_020851a0 and func_02085174 fill the person's entry, from which
 * SessionRecord_Update copies the record and sends it when it changed.
 *
 * The record says which system runs the object (`owner`) and which holds it (`holder`), the
 * scene it is in, its place and angle, four bytes kept at 0x62d of the object, and the note of
 * the motion it plays (scene_motion_core.h). The object is ours (SceneShare_IsOurs) when it is
 * not shared at all (no link, or its byte 0x563 set) or this system is the owner; the object's
 * frame (func_0201b910) publishes it then and otherwise plays the motion the record notes. */
#ifndef CLEAN_MAIN_SCENE_SHARE_H
#define CLEAN_MAIN_SCENE_SHARE_H

#include "autoload_2/vector.h"
#include "types.h"

/* The kinds of persons that have a shared record (the person code's top four bits). */
#define SCENE_SHARE_KIND_E 0xe
#define SCENE_SHARE_KIND_D 0xd

/* A slot of `owner` and `holder` that names no system. */
#define SCENE_SHARE_NO_SLOT 4

#define SCENE_SHARE_EXTRA_SIZE 4
#define SCENE_SHARE_NOTE_SIZE 13

/* A person's shared record (30 bytes). */
typedef struct SceneShareEntry {
    u8 in_use;                        /* 0x00 */
    u8 owner;                         /* 0x01: the session slot running the object */
    u8 holder;                        /* 0x02: the session slot holding it */
    u8 scene;                         /* 0x03: the scene it is in (packed_bytes.h) */
    u8 place[5];                      /* 0x04: its x and z, packed */
    u8 angle[2];                      /* 0x09: s16, as bytes */
    u8 extra[SCENE_SHARE_EXTRA_SIZE]; /* 0x0b: the object's bytes at 0x62d */
    u8 note_kind;                     /* 0x0f: the motion's note (its bytes 0x04-0x12) */
    u8 note_priority;                 /* 0x10 */
    u8 note[SCENE_SHARE_NOTE_SIZE];   /* 0x11 */
} SceneShareEntry;

int SceneShare_ReadNote(u8 *object, int *kind, int *priority, u8 *note);
int SceneShare_ReadPlace(u8 *object, Vec3 *point, s16 *angle);
void SceneShare_Publish(u8 *object, int value);
void SceneShare_SetExtra(u8 *object, const u8 *bytes, int size);
int SceneShare_ReadExtra(u8 *object, u8 *out, u32 size);
int SceneShare_IsHeld(u8 *object);
int SceneShare_ReadSlots(u8 *object, int *owner, int *holder);
void SceneShare_SetSlotsIfOurs(u8 *object, int value, int owner, int holder);
void SceneShare_SetSlots(u8 *object, u32 value, u32 owner, u32 holder);
int SceneShare_IsOurs(u8 *object);

#endif
