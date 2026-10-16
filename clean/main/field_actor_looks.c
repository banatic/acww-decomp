/* The field actor's looks (field_actor.h): what its player's record says of them, the colour
 * palettes, the clothes, the head (part B) and part C, and the sun level faded by the days
 * since it was last stored.
 *
 * The head and part C change in three steps, each a separate call: a request stores the item
 * and the values while the part is LOOKS_READY and marks it LOOKS_PENDING; the update applies a
 * pending change (LOOKS_LOADING); polls then mark it LOOKS_READY once its models are loaded
 * (field_actor_parts.h). */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/calendar.h"
#include "main/session.h"

static_assert(offsetof(FieldActor, unk_234) == FIELD_ACTOR_BODY, "body");
static_assert(offsetof(FieldActor, flags) == 0x6ec, "flags");
static_assert(offsetof(FieldActor, player) == 0x800, "player");

/* The session (main/session.h). */
extern NetSession *data_020ccf94;

/* The names the textures and palettes are copied under: "cloth", "skin_pl", "e.0", "m.0",
 * "hair_pl", and the body's material "w" the clothes are bound to. */
extern const char data_020d83f0[]; /* "skin_pl" */
extern const char data_020d83f8[]; /* "e.0" */
extern const char data_020d83fc[]; /* "m.0" */
extern const char data_020d8400[]; /* "hair_pl" */
extern const char data_020d8408[]; /* "w" */

/* Part C's kinds by item: 0x1431 and up (data_020cc7cc of them, 64), and 0x1471 and up through
 * func_0204bfa0 (data_020cc7d0 of them, 11). */
extern u32 data_020cc7cc;
extern u32 data_020cc7d0;

/* Part C's kind for no part. */
#define PART_C_NONE 0x4b
/* A part of the head that is not there (func_0205e138 and func_0205e708's result). */
#define HEAD_MODEL_NONE 0x9e
#define ITEM_NONE 0xfff1

/* The scenes where the sun level is not faded. */
#define SCENE_2E 0x2e
#define SCENE_0D 0x0d
#define SCENE_0E 0x0e
#define SCENE_0C 0x0c
#define SCENE_2F 0x2f

/* The byte func_0209626c points at: bits the sun level's update clears. */
#define SUN_BYTE_BIT0 0x01
#define SUN_BYTE_BIT1 0x02
#define SUN_BYTE_BIT4 0x10

/* A texture's named palette copied into another's (func_0206435c) and the same for a named
 * texture's image (func_0206439c). */
extern void func_0206435c(int from, int to, const void *from_name, const void *to_name);
extern void func_0206439c(int from, int to, const void *from_name, const void *to_name);

/* The player's record of the actor (NULL for none) and its fields. */
extern u8 *func_02011368(FieldActor *actor);
extern u16 *func_02099728(u8 *record);      /* the held item (slot 5, 0x2406) */
extern u16 *func_02099710(u8 *record);      /* the clothes (slot 2, 0x2408) */
extern u16 *func_020996f8(u8 *record);      /* the head's item (slot 4, 0x240a) */
extern u16 *func_020996e0(u8 *record);      /* part C's item (slot 3, 0x240c) */
extern u32 func_0209984c(u8 *record);       /* bits 0-3 of byte 0x243c */
extern u32 func_02099824(const u8 *record); /* bits 4-7 of byte 0x243c */
extern u32 func_020997f8(u8 *record);       /* bits 0-2 of byte 0x243d */
extern u32 func_020997d0(u8 *record);       /* bits 3-5 of byte 0x243d: the sun level */
extern void func_020997b4(u8 *record, int level);
extern int func_0209975c(u8 *record);     /* bit 0 of its flags at 0x23f8 */
extern u8 *func_02099870(u8 *record);     /* the player's name and town at 0x247e */
extern int func_020950c0(const s8 *name); /* its signed byte 28 */

/* The textures of the parts and their files. */
extern int func_021077e8(int file);
extern int func_0205dc80(const u8 *face);
extern int func_0205f8b4(const u8 *palettes); /* "skin_pl"'s file */
extern int func_0205f8a0(const u8 *palettes); /* "hair_pl"'s file */
extern int func_0205f874(const u8 *palettes, int index);
extern int func_0205f848(const u8 *palettes, int index);

/* The clothes. */
extern void func_0205d3d4(u8 *cloth, u16 *item, int record, int a, int b);
extern int func_0205d25c(const u8 *cloth);
extern int func_0203cfa8(int texture);
extern int func_020b9d3c(void *binding, int model, const char *material, int texture, int tex_index, int plt_index);

/* The head (part B) and its models. */
extern int func_0205e708(int flag, int kind, u16 *item, int *model_kind, int *second);
extern int func_0205e348(u8 *head, int model_kind, int second, u16 *item, int record);
extern int func_0205e194(u8 *head, int index);
extern int func_0205e138(const u8 *head, int index);
extern int func_0205e1bc(u8 *head);
extern void func_0205e274(u8 *head);
extern void func_0205e444(u8 *head);
extern int func_02055454(void *model);
extern void func_020554b0(void *model, int resource);
extern void func_0205682c(void *anim);
extern Heap *func_0205db38(const u8 *part);
extern int func_0205d8a0(const u8 *set);
extern int func_0205d894(const u8 *set);
extern void func_0205678c(void *anim, int resource, int frame, int a, u8 flags, fx32 speed);

/* Part C and its model. */
extern u8 func_0205e0a4(u32 index);
extern u8 func_0205e098(u32 index);
extern int func_0204bd84(u16 *item);
extern int func_0204bfa0(u16 *item);
extern void func_0205de94(u8 *part, int kind);
extern int func_0205ddd4(u8 *part);
extern void func_0205de70(u8 *part);
extern void func_0205dec8(u8 *part);
extern int func_0205de10(u8 *part);
extern int func_0205de24(u8 *part);

/* The sun level's update. */
extern int func_020b65c4(void); /* the scene */
extern int func_020b67ac(void);
extern int func_02096180(u32 made_with);                            /* the state the actor started in */
extern int func_0209e380(const DateTime *from, const DateTime *to); /* days between dates */
extern u8 *func_0209626c(void);
extern u16 *func_02096274(void);

/* The byte `offset` into the actor. */
static u8 *field_actor_looks_at(FieldActor *actor, u32 offset)
{
    return (u8 *) actor + offset;
}

/* ---- Textures and palettes */

/* func_020100b8: the palette `from_name` of the texture `from` into the palette `to_name` of
 * the texture `to` (func_0206435c); the actor is not used. */
void FieldActor_CopyPalette(FieldActor *actor, int from, int to, const void *from_name, const void *to_name)
{
    (void) actor;
    func_0206435c(from, to, from_name, to_name);
}
CLEAN_AS(func_020100b8, FieldActor_CopyPalette)

/* func_020100d0: the same for the image of the texture named `from_name` (func_0206439c). */
void FieldActor_CopyTexture(FieldActor *actor, int from, int to, const void *from_name, const void *to_name)
{
    (void) actor;
    func_0206439c(from, to, from_name, to_name);
}
CLEAN_AS(func_020100d0, FieldActor_CopyTexture)

/* ---- The head (part B at 0x428, with its models at 0x38c and 0x464) */

/* func_020100e8: asks for the head to change to `item` (the head's item, ITEM_NONE for none),
 * its kind when the item does not set one, the hair colour, and whether the face's textures
 * are copied onto it; 1 when it was taken, 0 while another change is under way. */
int FieldActor_RequestHead(FieldActor *actor, const u16 *item, u8 kind, u8 hair_color, u8 with_face)
{
    if (FIELD_ACTOR_HEAD_STATUS(actor) != LOOKS_READY) {
        return 0;
    }
    FIELD_ACTOR_HEAD_STATUS(actor) = LOOKS_PENDING;
    FIELD_ACTOR_HEAD_ITEM(actor) = *item;
    FIELD_ACTOR_HEAD_KIND(actor) = kind;
    FIELD_ACTOR_HEAD_HAIR_COLOR(actor) = hair_color;
    FIELD_ACTOR_HEAD_WITH_FACE(actor) = with_face;
    return 1;
}
CLEAN_AS(func_020100e8, FieldActor_RequestHead)

/* func_02010134: a head being loaded is ready once func_0205e1bc says so. */
void FieldActor_PollHead(FieldActor *actor)
{
    if (FIELD_ACTOR_HEAD_STATUS(actor) == LOOKS_LOADING && func_0205e1bc(field_actor_looks_at(actor, FIELD_ACTOR_PART_B))) {
        FIELD_ACTOR_HEAD_STATUS(actor) = LOOKS_READY;
    }
}
CLEAN_AS(func_02010134, FieldActor_PollHead)

/* func_02010160: applies a pending change of the head. The item (none with flag 0xc) and the
 * kind choose the head's models (func_0205e708, also given func_02011340's flag), which are
 * loaded with the item (func_0205e348); the palettes are set for the hair colour and the sun
 * level (FieldActor_SunLevel without storing). The face's "e.0" and "m.0" go onto the first
 * model's texture when asked for; "skin_pl" and "hair_pl" onto it, and "skin_pl" onto the
 * second model's when there is one. The head and its two models are then rebuilt. Without the
 * face, the face's animations are rebuilt: freed (with all of their heap), bound again
 * (FieldActor_BindFaceAnims) and started at the whole frames they were at, with the flags the
 * body's animation was started with. The head is then LOOKS_LOADING. */
void FieldActor_ApplyHead(FieldActor *actor)
{
    u8 *head = field_actor_looks_at(actor, FIELD_ACTOR_PART_B);
    if (FIELD_ACTOR_HEAD_STATUS(actor) != LOOKS_PENDING) {
        return;
    }

    u16 item = FieldActor_TestFlag(actor, 0xc) ? ITEM_NONE : FIELD_ACTOR_HEAD_ITEM(actor);
    int model_kind;
    int second;
    func_0205e708(FieldActor_RecordFlag249A(actor), FIELD_ACTOR_HEAD_KIND(actor), &item, &model_kind, &second);
    u16 loaded = FIELD_ACTOR_HEAD_ITEM(actor);
    func_0205e348(head, model_kind, second, &loaded, (int) (uintptr_t) func_02011368(actor));
    FieldActor_SetPalettes(actor, FIELD_ACTOR_HEAD_HAIR_COLOR(actor), FieldActor_SunLevel(actor, 0));

    int first_texture = func_021077e8(func_0205e194(head, 0));
    int second_texture = 0;
    if (second < HEAD_MODEL_NONE) {
        second_texture = func_021077e8(func_0205e194(head, 1));
    }
    if (FIELD_ACTOR_HEAD_WITH_FACE(actor)) {
        int face = func_021077e8(func_0205dc80(field_actor_looks_at(actor, FIELD_ACTOR_FACE)));
        FieldActor_CopyTexture(actor, face, first_texture, data_020d83f8, data_020d83f8);
        FieldActor_CopyTexture(actor, face, first_texture, data_020d83fc, data_020d83fc);
    }
    int skin = func_021077e8(func_0205f8b4(field_actor_looks_at(actor, FIELD_ACTOR_PALETTES)));
    int hair = func_021077e8(func_0205f8a0(field_actor_looks_at(actor, FIELD_ACTOR_PALETTES)));
    FieldActor_CopyPalette(actor, skin, first_texture, data_020d83f0, data_020d83f0);
    FieldActor_CopyPalette(actor, hair, first_texture, data_020d8400, data_020d8400);
    if (second_texture != 0) {
        FieldActor_CopyPalette(actor, skin, second_texture, data_020d83f0, data_020d83f0);
    }

    func_0205e274(head);
    func_0205e444(head);
    func_0205e1bc(head);
    func_02055454(field_actor_looks_at(actor, FIELD_ACTOR_MODEL_A));
    func_02055454(field_actor_looks_at(actor, FIELD_ACTOR_MODEL_B));
    func_020554b0(field_actor_looks_at(actor, FIELD_ACTOR_MODEL_A), func_0205e194(head, 0));
    if (func_0205e138(head, 1) < HEAD_MODEL_NONE) {
        func_020554b0(field_actor_looks_at(actor, FIELD_ACTOR_MODEL_B), func_0205e194(head, 1));
    }

    if (!FIELD_ACTOR_HEAD_WITH_FACE(actor)) {
        /* The whole frames (16 bits) the two animations were at. */
        int frame_a = (int) (((u32) FIELD_ACTOR_FACE_ANIM_A_FRAME(actor) << 4) >> 16);
        int frame_b = (int) (((u32) FIELD_ACTOR_FACE_ANIM_B_FRAME(actor) << 4) >> 16);
        u8 *anim_a = field_actor_looks_at(actor, FIELD_ACTOR_FACE_ANIM_A);
        u8 *anim_b = field_actor_looks_at(actor, FIELD_ACTOR_FACE_ANIM_B);
        const u8 *set = field_actor_looks_at(actor, FIELD_ACTOR_FACE_ANIM_SET);
        func_0205682c(anim_a);
        func_0205682c(anim_b);
        Heap_FreeAll(func_0205db38(field_actor_looks_at(actor, FIELD_ACTOR_FACE_ANIM_HEAP)));
        FieldActor_BindFaceAnims(actor);
        func_0205678c(anim_a, func_0205d8a0(set), frame_a, 0, FIELD_ACTOR_ANIM_FLAGS(actor), FX32_ONE);
        func_0205678c(anim_b, func_0205d894(set), frame_b, 0, FIELD_ACTOR_ANIM_FLAGS(actor), FX32_ONE);
    }
    FIELD_ACTOR_HEAD_STATUS(actor) = LOOKS_LOADING;
}
CLEAN_AS(func_02010160, FieldActor_ApplyHead)

/* ---- Part C (0x59c, with its model at 0x500) */

/* func_020103c0: asks for part C to change to `item`; 1 when it was taken, 0 while another
 * change is under way. */
int FieldActor_RequestPartC(FieldActor *actor, const u16 *item)
{
    if (FIELD_ACTOR_PART_C_STATUS(actor) != LOOKS_READY) {
        return 0;
    }
    FIELD_ACTOR_PART_C_STATUS(actor) = LOOKS_PENDING;
    FIELD_ACTOR_PART_C_ITEM(actor) = *item;
    return 1;
}
CLEAN_AS(func_020103c0, FieldActor_RequestPartC)

/* func_020103e4: part C being loaded is ready when it is PART_C_NONE or once func_0205de24 says
 * so. */
void FieldActor_PollPartC(FieldActor *actor)
{
    if (FIELD_ACTOR_PART_C_STATUS(actor) != LOOKS_LOADING) {
        return;
    }
    u8 *part = field_actor_looks_at(actor, FIELD_ACTOR_PART_C);
    int ready = 1;
    if (func_0205ddd4(part) != PART_C_NONE) {
        ready = func_0205de24(part);
    }
    if (ready) {
        FIELD_ACTOR_PART_C_STATUS(actor) = LOOKS_READY;
    }
}
CLEAN_AS(func_020103e4, FieldActor_PollPartC)

/* func_02010424: applies a pending change of part C. Its kind comes from the item: items
 * 0x1431 to 0x1470 by their index (func_0205e0a4, below data_020cc7cc), items 0x1471 to 0x1491
 * that func_0204bd84 accepts by func_0204bfa0's index (func_0205e098, below data_020cc7d0), and
 * PART_C_NONE for any other. With a part its model is rebuilt; it is LOOKS_LOADING either way,
 * and polled at once when there is none. */
void FieldActor_ApplyPartC(FieldActor *actor)
{
    if (FIELD_ACTOR_PART_C_STATUS(actor) != LOOKS_PENDING) {
        return;
    }
    u8 *part = field_actor_looks_at(actor, FIELD_ACTOR_PART_C);
    int kind = PART_C_NONE;
    u16 item = FIELD_ACTOR_PART_C_ITEM(actor);
    if (item >= 0x1431 && item <= 0x1470) {
        u32 index = (u32) item - 0x1431;
        if (index < data_020cc7cc) {
            kind = func_0205e0a4(index);
        }
    } else if (item >= 0x1471 && item <= 0x1491 && func_0204bd84(&item)) {
        int index = func_0204bfa0(&item);
        if (index >= 0 && (u32) index < data_020cc7d0) {
            kind = func_0205e098((u32) index);
        }
    }

    func_0205de94(part, kind);
    if (func_0205ddd4(part) != PART_C_NONE) {
        func_0205de70(part);
        func_0205dec8(part);
        func_02055454(field_actor_looks_at(actor, FIELD_ACTOR_MODEL_C));
        func_020554b0(field_actor_looks_at(actor, FIELD_ACTOR_MODEL_C), func_0205de10(part));
        func_0205de24(part);
        FIELD_ACTOR_PART_C_STATUS(actor) = LOOKS_LOADING;
    } else {
        FIELD_ACTOR_PART_C_STATUS(actor) = LOOKS_LOADING;
        FieldActor_PollPartC(actor);
    }
}
CLEAN_AS(func_02010424, FieldActor_ApplyPartC)

/* ---- The clothes (0x774) and the palettes (0x7a0) */

/* func_0201063c: binds the clothes' texture to the body model's material "w" (func_020b9d3c
 * through the binding at 0x778); func_020b9d3c's answer. */
int FieldActor_BindCloth(FieldActor *actor)
{
    int model = FIELD_ACTOR_FIELD(actor, int, 0x290);
    int texture = func_0203cfa8(func_0205d25c(field_actor_looks_at(actor, FIELD_ACTOR_CLOTH)));
    return func_020b9d3c(field_actor_looks_at(actor, FIELD_ACTOR_CLOTH_BINDING), model, data_020d8408, texture, 0, 0);
}
CLEAN_AS(func_0201063c, FieldActor_BindCloth)

/* func_02010680: the clothes become `item` (func_0205d3d4, with the player's record). */
void FieldActor_SetCloth(FieldActor *actor, u16 *item)
{
    func_0205d3d4(field_actor_looks_at(actor, FIELD_ACTOR_CLOTH), item, (int) (uintptr_t) func_02011368(actor), 0, 0);
}
CLEAN_AS(func_02010680, FieldActor_SetCloth)

/* func_020106a8: the palettes' two entries. The skin's is the sun level plus 8 times a base
 * that grows with the face (FieldActor_RecordFace: 1 below 8, 9 below 0x10, 0x11 below 0x18,
 * else 0x19; 0x10 less with the record's flag 0); it is set (func_0205f874) below 0x80. The
 * hair's is the sun level plus 8 times the hair colour plus 0x80; it is set (func_0205f848)
 * from 0x80 to 0xbf. */
void FieldActor_SetPalettes(FieldActor *actor, int hair_color, int sun_level)
{
    int face = FieldActor_RecordFace(actor);
    int base;
    if (face >= 0x18) {
        base = 0x19;
    } else if (face >= 0x10) {
        base = 0x11;
    } else if (face >= 8) {
        base = 9;
    } else {
        base = 1;
    }
    if (FieldActor_RecordFlag0(actor) != 0) {
        base -= 0x10;
    }
    int skin = sun_level + base * 8;
    int hair = sun_level + hair_color * 8 + 0x80;
    const u8 *palettes = field_actor_looks_at(actor, FIELD_ACTOR_PALETTES);
    if (skin < 0x80) {
        func_0205f874(palettes, skin);
    }
    if (hair >= 0x80 && hair < 0xc0) {
        func_0205f848(palettes, hair);
    }
}
CLEAN_AS(func_020106a8, FieldActor_SetPalettes)

/* ---- The player's record (func_02011368, NULL for none) */

/* func_020110c4: the held item (slot 5); ITEM_NONE without a record. */
void FieldActor_RecordHeldItem(u16 *item, FieldActor *actor)
{
    *item = ITEM_NONE;
    u8 *record = func_02011368(actor);
    if (record != NULL) {
        *item = *func_02099728(record);
    }
}
CLEAN_AS(func_020110c4, FieldActor_RecordHeldItem)

/* func_020110e8: the face: bits 0-3 of the record's byte 0x243c, 0x10 more with its flag 0;
 * 0 without a record. */
int FieldActor_RecordFace(FieldActor *actor)
{
    u8 *record = func_02011368(actor);
    int face = 0x20;
    if (record != NULL) {
        face = (int) func_0209984c(record);
        if (func_0209975c(record) != 0) {
            face += 0x10;
        }
    }
    return face < 0x20 ? face : 0;
}
CLEAN_AS(func_020110e8, FieldActor_RecordFace)

/* func_0201111c: the record's flag 0 (bit 0 of its words at 0x23f8); 0 without a record. */
int FieldActor_RecordFlag0(FieldActor *actor)
{
    u8 *record = func_02011368(actor);
    if (record == NULL) {
        return 0;
    }
    return func_0209975c(record);
}
CLEAN_AS(func_0201111c, FieldActor_RecordFlag0)

/* func_02011138: part C's item (slot 3).
 * REQUIRES: the actor's player has a record (without one, the halfword at 0x240c is read). */
void FieldActor_RecordPartCItem(u16 *item, FieldActor *actor)
{
    *item = *func_020996e0(func_02011368(actor));
}
CLEAN_AS(func_02011138, FieldActor_RecordPartCItem)

/* func_02011150: the sun level of the record, faded by half a level a day since the date stored
 * with it. It is left as it is in the scenes 0x2e, 0xd, 0xe, 0xc and 0x2f, and unless either
 * func_020b67ac is set and the actor started in state 8 (then `store` 1 counts as 0), or the
 * actor is this console's player's and `store` is set. FieldActor_CompareSunDate compares the
 * clock's date with the stored one:
 *  - before it: with `store`, today is stored (FieldActor_StoreSunDate);
 *  - the same: nothing;
 *  - after it: two days or more on, the level drops by half the days (to 0 at least) and, with
 *    `store`, goes into the record with today's date, bit 1 of func_0209626c's byte is cleared
 *    (and bit 4 unless FieldActor_LinkedNotPlayer0), and FieldActor_SendSunLevel; bit 0 of
 *    that byte is cleared on any day after.
 * The halfword func_02096274 points at becomes 0x4650 when it is 0.
 * REQUIRES: the actor's player has a record (FieldActor_RecordSunLevel). */
u8 FieldActor_SunLevel(FieldActor *actor, int store)
{
    u8 level = (u8) FieldActor_RecordSunLevel(actor);
    int linked = 0;

    int scene = func_020b65c4();
    if (scene == SCENE_2E || scene == SCENE_0D || scene == SCENE_0E || scene == SCENE_0C || scene == SCENE_2F) {
        return level;
    }
    if (func_020b67ac() != 0 && func_02096180(FIELD_ACTOR_FIELD(actor, u32, 8)) == 8) {
        if (store == 1) {
            store = 0;
        }
    } else if (!Session_IsLocalPlayer(data_020ccf94, actor->player) || store == 0) {
        return level;
    }

    if (FieldActor_LinkedNotPlayer0(actor) != 0) {
        linked = 1;
    }
    u8 *record = func_02011368(actor);
    DateTime now = {0};
    DateTime stored = {0};
    int order = FieldActor_CompareSunDate(actor, &now, &stored);
    u16 today = (u16) ((now.year & 0x7f) | ((now.month & 0xf) << 7) | ((now.day & 0x1f) << 11));

    if (order == -1) {
        if (store != 0) {
            FieldActor_StoreSunDate(actor, (int) (uintptr_t) record, &today);
        }
    } else if (order != 0) {
        int days = func_0209e380(&stored, &now);
        u8 *bits = func_0209626c();
        if (days >= 2) {
            int fade = days >> 1;
            level = level > fade ? (u8) (level - fade) : 0;
            if (store != 0) {
                func_020997b4(record, level);
                FieldActor_StoreSunDate(actor, (int) (uintptr_t) record, &today);
                *bits &= (u8) ~SUN_BYTE_BIT1;
                if (!linked) {
                    *bits &= (u8) ~SUN_BYTE_BIT4;
                }
                FieldActor_SendSunLevel(actor);
            }
        }
        *bits &= (u8) ~SUN_BYTE_BIT0;
    }

    u16 *value = func_02096274();
    if (*value == 0) {
        *value = 0x4650;
    }
    return level;
}
CLEAN_AS(func_02011150, FieldActor_SunLevel)

/* func_020112bc: the sun level (bits 3-5 of the record's byte 0x243d).
 * REQUIRES: the actor's player has a record (without one, the byte at 0x243d is read). */
unsigned int FieldActor_RecordSunLevel(FieldActor *actor)
{
    return func_020997d0(func_02011368(actor));
}
CLEAN_AS(func_020112bc, FieldActor_RecordSunLevel)

/* func_020112d0: the hair colour (bits 0-2 of the record's byte 0x243d), the index of the
 * "hair_pl" palette.
 * REQUIRES: the actor's player has a record (without one, the byte at 0x243d is read). */
unsigned int FieldActor_RecordHairColor(FieldActor *actor)
{
    return func_020997f8(func_02011368(actor));
}
CLEAN_AS(func_020112d0, FieldActor_RecordHairColor)

/* func_020112e4: the head's kind when its item does not set one (bits 4-7 of the record's byte
 * 0x243c).
 * REQUIRES: the actor's player has a record (without one, the byte at 0x243c is read). */
unsigned int FieldActor_RecordHeadKind(FieldActor *actor)
{
    return func_02099824(func_02011368(actor));
}
CLEAN_AS(func_020112e4, FieldActor_RecordHeadKind)

/* func_020112f8: the head's item (slot 4); ITEM_NONE without a record. */
void FieldActor_RecordHeadItem(u16 *item, FieldActor *actor)
{
    u8 *record = func_02011368(actor);
    *item = ITEM_NONE;
    if (record != NULL) {
        *item = *func_020996f8(record);
    }
}
CLEAN_AS(func_020112f8, FieldActor_RecordHeadItem)

/* func_0201131c: the clothes (slot 2); ITEM_NONE without a record. */
void FieldActor_RecordCloth(u16 *item, FieldActor *actor)
{
    u8 *record = func_02011368(actor);
    *item = ITEM_NONE;
    if (record != NULL) {
        *item = *func_02099710(record);
    }
}
CLEAN_AS(func_0201131c, FieldActor_RecordCloth)

/* func_02011340: whether the signed byte 28 of the record's name and town (0x247e) is not 0;
 * 0 without a record. */
int FieldActor_RecordFlag249A(FieldActor *actor)
{
    u8 *record = func_02011368(actor);
    if (record == NULL) {
        return 0;
    }
    return func_020950c0((const s8 *) func_02099870(record)) != 0;
}
CLEAN_AS(func_02011340, FieldActor_RecordFlag249A)
