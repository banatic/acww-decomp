/* The music players (music_player.h). */
#include "music_player.h"

#include <stdint.h>

#include "clean.h"
#include "main/group_params.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_parts.h"

static_assert(offsetof(MusicPlayer, playing) == 0x844, "playing");
static_assert(offsetof(MusicPlayer, song) == 0x845, "song");
static_assert(offsetof(MusicPlayer, glows) == 0x848, "glows");
static_assert(offsetof(MusicPlayer, state) == 0x8a0, "state");
static_assert(offsetof(MusicPlayer, talk_step) == 0x8a4, "talk step");
static_assert(offsetof(RoomSound, position) == 0x20, "the sound's position");

#define MUSIC_PLAYER_RECEIVER_OFFSET 0xec
#define ONE 0x1000           /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0     /* start again at the end */
#define ANIM_MODE_ONCE 1     /* stop at the end */
#define KIND_ANIMATED 0x29   /* RoomObject.unk_780 of the players that animate */
#define MENU_MODE_SONGS 0x40 /* the mode group 9 opens the song menu in */

/* The music items: song n is item MUSIC_ITEM_FIRST + n. */
#define MUSIC_ITEM_FIRST 0x1323
#define MUSIC_ITEM_LAST 0x1368
#define SONG_COUNT 0x46
#define NO_SONG (-1)

/* What the receiver's state byte tells the talk: the song handed to the link, or none. */
#define SAYS_SONG 5
#define SAYS_NO_SONG 6

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_022570b0;
extern MemberPointer data_ov004_02257154[MUSIC_PLAYER_STATE_COUNT];
extern const MemberPointer data_ov004_02250450, data_ov004_02250448;
extern u32 data_ov004_02257034;
extern MemberPointer data_ov004_02257144[MUSIC_PLAYER_STATE_COUNT];
extern const MemberPointer data_ov004_02250470, data_ov004_02250130;
/* The talk steps' updates. */
extern u32 data_ov004_02257044;
extern MemberPointer data_ov004_022575dc[MUSIC_PLAYER_TALK_STEP_COUNT];
extern const MemberPointer data_ov004_022500a0, data_ov004_022504b0, data_ov004_022504a8, data_ov004_022504a0,
    data_ov004_02250498, data_ov004_02250490;

/* Whether each state shows the object on (for vtable slot 0x74): PLAYING does. */
extern const u8 data_ov004_02247660[MUSIC_PLAYER_STATE_COUNT];

/* "obj_etc_player", the name the receiver takes for the talk. */
extern const char data_ov004_022531f0[];
/* The villagers (0x7ec bytes each). */
extern u8 data_021e5a2c[];

/* Plays song `song` (as music 0xb0 + song) and makes it the house's music item, when none is
 * playing; and stops it (also clearing the item with `clear_item`) when one is. */
extern void func_ov004_022165dc(MusicPlayer *player, unsigned int song);
extern void func_ov004_02216598(MusicPlayer *player, unsigned int song, int clear_item);
/* Enters talk step `step` if its entry agrees (through a table); whether it did. */
extern int func_ov004_022164a0(MusicPlayer *player, int step);
/* Switches every room object to `value` whose switch shows otherwise, of those `filter`
 * accepts. */
extern void func_ov004_0223c2b4(int value, int (*filter)(void *object), void *pending);
/* Whether unk_00C is 0x3a and the switch on (RoomObject_Unk00CIs3AAndOn), handed to
 * func_ov004_0223c2b4 by its symbol. */
extern int func_ov004_02211308(void *object);
/* Moves a sound that is playing to `at`. */
extern void func_ov004_0223cf2c(RoomSound *sound, const Vec3 *at);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);
/* The scene object's hooks: asking the scene for an event, letting it go on, and taking and
 * handing back the receiver. */
extern int func_0203e0a8(MusicPlayer *player, int a1);
extern int func_0203e020(MusicPlayer *player);
extern void func_0203ee14(MusicPlayer *player, void *receiver);
extern void func_0203ee08(MusicPlayer *player, void *receiver);
extern void func_020a8164(void *receiver, const char *name);
/* Sets flag 0x17 of the actor func_02096718(4) gives; whether there is one. */
extern int func_02095ec4(void);
/* The item chosen in group 9's menu (data_021cfc70). */
extern u16 func_0206f668(void);
/* Whether the scene (func_020b65c4) is a villager's house (17 to 24), and the villager whose. */
extern int func_020b6680(void);
extern int func_020b66b0(void);
/* A villager (NULL when there is none) and its song (its byte at 0x4d). */
extern void *func_0207cec0(void *villagers, int villager);
extern int func_0207f2c4(void *villager);
/* The music item of the scene's house (0xfff1 when it has none). */
extern u16 *func_02060b70(void);
/* A text made from an item's name, handed to the link as its message 0, and taken down. */
extern void *func_02062f90(void *text, u16 *item);
extern void func_020683b4(RoomLink *link, int index, void *text, int kind);
extern void *func_02062f4c(void *text);

static unsigned int MusicPlayer_address(MusicPlayer *player)
{
    return (unsigned int) (uintptr_t) player;
}

/* The receiver part as C++ converts a pointer to the player to it: NULL stays NULL. */
static void *MusicPlayer_receiver(MusicPlayer *player)
{
    return player != NULL ? (u8 *) player + MUSIC_PLAYER_RECEIVER_OFFSET : NULL;
}

/* Touching it: the switch put back to `shown`, and the scene asked for an event. */
static int MusicPlayer_touched(MusicPlayer *player, u8 shown)
{
    Switch_Set(&player->base.light_switch, shown, 0);
    func_0203e0a8(player, 0);
    return func_02095ec4();
}

/* func_ov004_02215f8c (update of MUSIC_PLAYER_PLAYING): the animations, the sound at 0, the
 * glows towards on, the sound kept at the object; when touched, gives the answer of
 * func_02095ec4, else 0. */
int MusicPlayer_UpdatePlaying(MusicPlayer *player)
{
    RoomObject_AdvanceAnims(&player->base);
    RoomObject_PlaySound0(&player->base);
    GlowSet_Switch(&player->glows, 1, 1, 0);
    func_ov004_0223cf2c(&player->base.sound, &player->base.sound.position);
    if (Switch_IsPending(&player->base.light_switch)) {
        return MusicPlayer_touched(player, 1);
    }
    return 0;
}
CLEAN_AS(func_ov004_02215f8c, MusicPlayer_UpdatePlaying)

/* func_ov004_02215ff0 (entry of MUSIC_PLAYER_PLAYING): the sound at 2; every room object with
 * unk_00C 0x3a that is on (this one included) switched off; the switch on (shown at once); the
 * song given with the state (RoomObject.unk_77C) kept and played; kind 0x29 loops the
 * animations of variant 1 from the start. */
int MusicPlayer_EnterPlaying(MusicPlayer *player)
{
    RoomObject_PlaySound1(&player->base);
    func_ov004_0223c2b4(0, func_ov004_02211308, NULL);
    Switch_Set(&player->base.light_switch, 1, 0);
    player->song = player->base.unk_77C;
    func_ov004_022165dc(player, player->base.unk_77C);
    if (player->base.unk_780 == KIND_ANIMATED) {
        RoomObject_PlayAnimsFrom(&player->base, 1, ANIM_MODE_LOOP, ONE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_02215ff0, MusicPlayer_EnterPlaying)

/* func_ov004_0221605c (update of MUSIC_PLAYER_STOPPED): kind 0x29's animations, the glows
 * towards off; when touched, the scene is asked for an event. */
void MusicPlayer_UpdateStopped(MusicPlayer *player)
{
    if (player->base.unk_780 == KIND_ANIMATED) {
        RoomObject_AdvanceAnims(&player->base);
    }
    GlowSet_Switch(&player->glows, 0, 1, 0);
    if (Switch_IsPending(&player->base.light_switch)) {
        MusicPlayer_touched(player, 0);
    }
}
CLEAN_AS(func_ov004_0221605c, MusicPlayer_UpdateStopped)

/* func_ov004_022160b0 (entry of MUSIC_PLAYER_STOPPED): the sound at 4, the switch off (shown at
 * once); the song stopped, its item cleared, unless the model is being bound
 * (RoomObject.unk_77E); kind 0x29 plays the animations of variant 0 once from the start. */
int MusicPlayer_EnterStopped(MusicPlayer *player)
{
    RoomObject_PlaySound2(&player->base);
    Switch_Set(&player->base.light_switch, 0, 0);
    if (player->base.unk_77E == 0) {
        func_ov004_02216598(player, player->song, 1);
    }
    if (player->base.unk_780 == KIND_ANIMATED) {
        RoomObject_PlayAnimsFrom(&player->base, 0, ANIM_MODE_ONCE, ONE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_022160b0, MusicPlayer_EnterStopped)

/* _ZN18Obj_ov004_022517bc19func_ov004_02216110Ev: the state's update, through its table. */
void MusicPlayer_UpdateState(MusicPlayer *player)
{
    static const MemberPointer *const updates[MUSIC_PLAYER_STATE_COUNT] = {
        &data_ov004_02250450, /* MusicPlayer_UpdateStopped */
        &data_ov004_02250448, /* MusicPlayer_UpdatePlaying */
    };
    MemberTable_InitOnce(&data_ov004_022570b0, data_ov004_02257154, updates, MUSIC_PLAYER_STATE_COUNT);
    if (player->state < MUSIC_PLAYER_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257154[player->state], player);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022517bc19func_ov004_02216110Ev, MusicPlayer_UpdateState)

/* func_ov004_0221617c (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`, the song), then enters `state` if its entry (through a table) agrees; whether
 * it did. States 2 and above do not exist. */
int MusicPlayer_EnterState(MusicPlayer *player, unsigned int state, int value)
{
    static const MemberPointer *const entries[MUSIC_PLAYER_STATE_COUNT] = {
        &data_ov004_02250470, /* MusicPlayer_EnterStopped */
        &data_ov004_02250130, /* MusicPlayer_EnterPlaying */
    };
    RoomObject_SetUnk77C(&player->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257034, data_ov004_02257144, entries, MUSIC_PLAYER_STATE_COUNT);
    if (state < MUSIC_PLAYER_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257144[state], player) != 0) {
        player->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221617c, MusicPlayer_EnterState)

/* func_ov004_02216200 (vtable slot 0x74): whether `state` shows the object on (PLAYING does); 0
 * for a state that does not exist. */
u8 MusicPlayer_StateIsOn(MusicPlayer *player, unsigned int state)
{
    (void) player;
    if (state < MUSIC_PLAYER_STATE_COUNT) {
        return data_ov004_02247660[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02216200, MusicPlayer_StateIsOn)

/* func_ov004_02216214 (update of MUSIC_PLAYER_TALK_END): once the link has closed, hands the
 * receiver back (func_0203ee08) and lets the scene go on (func_0203e020). The step stays until
 * the scene sets another. */
void MusicPlayer_UpdateTalkEnd(MusicPlayer *player)
{
    if (player->base.link != NULL && player->base.link->open == 0) {
        func_0203ee08(player, MusicPlayer_receiver(player));
        func_0203e020(player);
    }
}
CLEAN_AS(func_ov004_02216214, MusicPlayer_UpdateTalkEnd)

/* func_ov004_02216244 (entry of MUSIC_PLAYER_TALK_END) */
int MusicPlayer_EnterTalkEnd(MusicPlayer *player)
{
    (void) player;
    return 1;
}
CLEAN_AS(func_ov004_02216244, MusicPlayer_EnterTalkEnd)

/* func_ov004_02216248 (update of MUSIC_PLAYER_TALK): on once the link has opened. */
void MusicPlayer_UpdateTalk(MusicPlayer *player)
{
    if (player->base.link != NULL && player->base.link->open != 0) {
        func_ov004_022164a0(player, MUSIC_PLAYER_TALK_END);
    }
}
CLEAN_AS(func_ov004_02216248, MusicPlayer_UpdateTalk)

/* The song's item handed to the link as text, the receiver told so. */
static void MusicPlayer_tell_song(MusicPlayer *player, u16 *item)
{
    u8 text[0x28];
    func_02062f90(text, item);
    player->base.receiver_state = SAYS_SONG;
    func_020683b4(player->base.link, 0, text, 7);
    func_02062f4c(text);
}

/* func_ov004_0221626c (entry of MUSIC_PLAYER_TALK): takes the receiver (func_0203ee14), raises
 * the link's request and names the receiver "obj_etc_player". In a villager's house it tells
 * the villager's song (song 0 for no villager or a song past the last); elsewhere the house's
 * music item, or that there is none.
 * REQUIRES: the receiver has a link once func_0203ee14 has taken it. */
int MusicPlayer_EnterTalk(MusicPlayer *player)
{
    func_0203ee14(player, MusicPlayer_receiver(player));
    player->base.link->requested = 1;
    func_020a8164(&player->base.receiver_vtable, data_ov004_022531f0);
    if (func_020b6680() != 0) {
        u32 song = 0;
        void *villager = func_0207cec0(data_021e5a2c, func_020b66b0());
        if (villager != NULL) {
            song = (u32) func_0207f2c4(villager);
        }
        u16 item = song < SONG_COUNT ? (u16) (MUSIC_ITEM_FIRST + song) : MUSIC_ITEM_FIRST;
        MusicPlayer_tell_song(player, &item);
    } else {
        u16 *item = func_02060b70();
        if (*item >= MUSIC_ITEM_FIRST && *item <= MUSIC_ITEM_LAST) {
            MusicPlayer_tell_song(player, item);
        } else {
            player->base.receiver_state = SAYS_NO_SONG;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0221626c, MusicPlayer_EnterTalk)

/* func_ov004_02216350 (update of MUSIC_PLAYER_TALK_NEXT): talks. */
void MusicPlayer_UpdateTalkNext(MusicPlayer *player)
{
    func_ov004_022164a0(player, MUSIC_PLAYER_TALK);
}
CLEAN_AS(func_ov004_02216350, MusicPlayer_UpdateTalkNext)

/* func_ov004_0221635c (entry of MUSIC_PLAYER_TALK_NEXT) */
int MusicPlayer_EnterTalkNext(MusicPlayer *player)
{
    (void) player;
    return 1;
}
CLEAN_AS(func_ov004_0221635c, MusicPlayer_EnterTalkNext)

/* func_ov004_02216360 (update of MUSIC_PLAYER_TALK_MENU): once group 9 can be opened again (the
 * menu has closed): when a music item was chosen there (GroupParams_C4CIs1), requests
 * MUSIC_PLAYER_PLAYING with its song (0xff for an item that is no music); then lets the scene
 * go on. The step stays until the scene sets another. */
void MusicPlayer_UpdateTalkMenu(MusicPlayer *player)
{
    if (!GroupParams_CanOpen()) {
        return;
    }
    if (GroupParams_C4CIs1()) {
        u16 item = func_0206f668();
        int song = NO_SONG;
        if (item >= MUSIC_ITEM_FIRST && item <= MUSIC_ITEM_LAST) {
            song = item - MUSIC_ITEM_FIRST;
        }
        func_0205265c(MusicPlayer_address(player), MUSIC_PLAYER_PLAYING, (u8) song, 1);
    }
    func_0203e020(player);
}
CLEAN_AS(func_ov004_02216360, MusicPlayer_UpdateTalkMenu)

/* func_ov004_022163c4 (entry of MUSIC_PLAYER_TALK_MENU): opens the song menu (group 9 in mode
 * 0x40); refused when it cannot be opened. */
int MusicPlayer_EnterTalkMenu(MusicPlayer *player)
{
    (void) player;
    return GroupParams_Open(MENU_MODE_SONGS) ? 1 : 0;
}
CLEAN_AS(func_ov004_022163c4, MusicPlayer_EnterTalkMenu)

/* func_ov004_022163e0 (update of MUSIC_PLAYER_TALK_MENU_NEXT): opens the menu. */
void MusicPlayer_UpdateTalkMenuNext(MusicPlayer *player)
{
    func_ov004_022164a0(player, MUSIC_PLAYER_TALK_MENU);
}
CLEAN_AS(func_ov004_022163e0, MusicPlayer_UpdateTalkMenuNext)

/* func_ov004_022163ec (entry of MUSIC_PLAYER_TALK_MENU_NEXT) */
int MusicPlayer_EnterTalkMenuNext(MusicPlayer *player)
{
    (void) player;
    return 1;
}
CLEAN_AS(func_ov004_022163ec, MusicPlayer_EnterTalkMenuNext)

/* func_ov004_022163f0 (update of MUSIC_PLAYER_TALK_NONE) */
void MusicPlayer_UpdateTalkNone(MusicPlayer *player)
{
    (void) player;
}
CLEAN_AS(func_ov004_022163f0, MusicPlayer_UpdateTalkNone)

/* func_ov004_022163f4 (entry of MUSIC_PLAYER_TALK_NONE) */
int MusicPlayer_EnterTalkNone(MusicPlayer *player)
{
    (void) player;
    return 1;
}
CLEAN_AS(func_ov004_022163f4, MusicPlayer_EnterTalkNone)

/* _ZN18Obj_ov004_022517bc19func_ov004_022163f8Ev: the talk step's update, through its table.
 * REQUIRES: the step is not negative (func_ov004_022164a0 is only given 0 to 5). */
void MusicPlayer_UpdateTalkStep(MusicPlayer *player)
{
    static const MemberPointer *const updates[MUSIC_PLAYER_TALK_STEP_COUNT] = {
        &data_ov004_022500a0, /* MusicPlayer_UpdateTalkNone */
        &data_ov004_022504b0, /* MusicPlayer_UpdateTalkMenuNext */
        &data_ov004_022504a8, /* MusicPlayer_UpdateTalkMenu */
        &data_ov004_022504a0, /* MusicPlayer_UpdateTalkNext */
        &data_ov004_02250498, /* MusicPlayer_UpdateTalk */
        &data_ov004_02250490, /* MusicPlayer_UpdateTalkEnd */
    };
    MemberTable_InitOnce(&data_ov004_02257044, data_ov004_022575dc, updates, MUSIC_PLAYER_TALK_STEP_COUNT);
    if (player->talk_step < MUSIC_PLAYER_TALK_STEP_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022575dc[player->talk_step], player);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022517bc19func_ov004_022163f8Ev, MusicPlayer_UpdateTalkStep)
