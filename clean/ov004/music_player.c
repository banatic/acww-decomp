/* The music players (music_player.h). */
#include "music_player.h"

#include <stdint.h>

#include "clean.h"
#include "main/group_params.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_map.h"
#include "room_object_parts.h"

static_assert(offsetof(MusicPlayer, playing) == 0x844, "playing");
static_assert(offsetof(MusicPlayer, song) == 0x845, "song");
static_assert(offsetof(MusicPlayer, glows) == 0x848, "glows");
static_assert(offsetof(MusicPlayer, state) == 0x8a0, "state");
static_assert(offsetof(MusicPlayer, talk_step) == 0x8a4, "talk step");
static_assert(offsetof(RoomSound, position) == 0x20, "the sound's position");
static_assert(sizeof(MusicPlayer) == 0x8a8, "the size MusicPlayer_Create allocates");

#define MUSIC_PLAYER_RECEIVER_OFFSET 0xec
#define MUSIC_PLAYER_SIZE 0x8a8
#define ONE 0x1000           /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0     /* start again at the end */
#define ANIM_MODE_ONCE 1     /* stop at the end */
#define KIND_ANIMATED 0x29   /* RoomObject.unk_780 of the players that animate */
#define KIND_13 0x13         /* another kind whose animations are loaded with its model */
#define MENU_MODE_SONGS 0x40 /* the mode group 9 opens the song menu in */

/* The music items: song n is item MUSIC_ITEM_FIRST + n. */
#define MUSIC_ITEM_FIRST 0x1323
#define MUSIC_ITEM_LAST 0x1368
#define SONG_COUNT 0x46
#define NO_SONG (-1)
#define NO_VALUE 0xff    /* the song given with MUSIC_PLAYER_STOPPED */
#define MUSIC_FIRST 0xb0 /* the music of song 0 */
#define ITEM_NONE 0xfff1 /* no item */

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

/* The talk steps' entries. */
extern u32 data_ov004_02257058;
extern MemberPointer data_ov004_022575ac[MUSIC_PLAYER_TALK_STEP_COUNT];
extern const MemberPointer data_ov004_02250088, data_ov004_022504f0, data_ov004_022504e8, data_ov004_022504e0,
    data_ov004_022504d8, data_ov004_022504d0;

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022517bc[];
extern const u8 data_ov004_02251868[];

/* The music item a player started in a villager's house (the villager's song), 0xfff1 for
 * none: a player there starts on with the villager's song only while none was started. */
extern u16 data_ov004_02256fec;

/* Music: starting music `id` (with 0x11, 0x7f and 0) and stopping it. */
extern void func_020356c4(int a0, int id, int a2, int a3);
extern void func_02035638(int id);
/* Sets the music item of the scene's house (func_02060b70 reads it), and sets it to none. */
extern void *func_02060b34(u16 *item);
extern void func_02060afc(void);
/* func_020b67e8 of the scene (func_020b65c4). */
extern int func_020b67d4(void);
/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1), straight
 * to func_020526b8. */
extern int func_02052738(unsigned int object, int state, int a2, int a3);
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
    MusicPlayer_PlaySong(player, player->base.unk_77C);
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
        MusicPlayer_StopSong(player, player->song, 1);
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
        MusicPlayer_EnterTalkStep(player, MUSIC_PLAYER_TALK_END);
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
    MusicPlayer_EnterTalkStep(player, MUSIC_PLAYER_TALK);
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
    MusicPlayer_EnterTalkStep(player, MUSIC_PLAYER_TALK_MENU);
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
 * REQUIRES: the step is not negative (MusicPlayer_EnterTalkStep only sets 0 to 5). */
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

/* func_ov004_022164a0: enters talk step `step` if its entry (through a table) agrees; whether it
 * did.
 * REQUIRES: `step` is not negative (the game passes the constants 0 to 5); for a negative step
 * the original reads a member pointer from before its table. */
int MusicPlayer_EnterTalkStep(MusicPlayer *player, int step)
{
    static const MemberPointer *const entries[MUSIC_PLAYER_TALK_STEP_COUNT] = {
        &data_ov004_02250088, /* MusicPlayer_EnterTalkNone */
        &data_ov004_022504f0, /* MusicPlayer_EnterTalkMenuNext */
        &data_ov004_022504e8, /* MusicPlayer_EnterTalkMenu */
        &data_ov004_022504e0, /* MusicPlayer_EnterTalkNext */
        &data_ov004_022504d8, /* MusicPlayer_EnterTalk */
        &data_ov004_022504d0, /* MusicPlayer_EnterTalkEnd */
    };
    MemberTable_InitOnce(&data_ov004_02257058, data_ov004_022575ac, entries, MUSIC_PLAYER_TALK_STEP_COUNT);
    if (step >= 0 && step < MUSIC_PLAYER_TALK_STEP_COUNT && MemberPointer_CallInt(&data_ov004_022575ac[step], player) != 0) {
        player->talk_step = step;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022164a0, MusicPlayer_EnterTalkStep)

/* func_ov004_02216558 (vtable slot 0x4c): the scene's answer to func_0203e0a8. Event 1 starts
 * the song menu when func_020b67d4 and Room_Check0220fed0 allow it, else the talk that tells the
 * song; event 8 ends the talk; others do nothing. */
void MusicPlayer_OnSceneEvent(MusicPlayer *player, int event)
{
    switch (event) {
        case 1:
            if (func_020b67d4() != 0 && Room_Check0220fed0() != 0) {
                MusicPlayer_EnterTalkStep(player, MUSIC_PLAYER_TALK_MENU_NEXT);
            } else {
                MusicPlayer_EnterTalkStep(player, MUSIC_PLAYER_TALK_NEXT);
            }
            break;
        case 8:
            MusicPlayer_EnterTalkStep(player, MUSIC_PLAYER_TALK_NONE);
            break;
    }
}
CLEAN_AS(func_ov004_02216558, MusicPlayer_OnSceneEvent)

/* func_ov004_02216598: stops song `song` (music 0xb0 + song) when it is playing, and with
 * `clear_item` sets the house's music item to none. Nothing for a song past the last. */
void MusicPlayer_StopSong(MusicPlayer *player, unsigned int song, int clear_item)
{
    if (player->playing && song < SONG_COUNT) {
        func_02035638((u16) (song + MUSIC_FIRST));
        if (clear_item != 0) {
            u16 none = ITEM_NONE;
            func_02060b34(&none);
        }
        player->playing = 0;
    }
}
CLEAN_AS(func_ov004_02216598, MusicPlayer_StopSong)

/* func_ov004_022165dc: plays song `song` (music 0xb0 + song) and makes its item the house's
 * music item, when none is playing. Nothing for a song past the last. */
void MusicPlayer_PlaySong(MusicPlayer *player, unsigned int song)
{
    if (!player->playing && song < SONG_COUNT) {
        func_020356c4(0x11, (u16) (song + MUSIC_FIRST), 0x7f, 0);
        u16 item = (u16) (MUSIC_ITEM_FIRST + song);
        func_02060b34(&item);
        player->playing = 1;
    }
}
CLEAN_AS(func_ov004_022165dc, MusicPlayer_PlaySong)

/* func_ov004_02216630 (vtable slot 0x0c): stops the song, setting the house's music item to none
 * when the object is vanishing; forgets the villager's song started (data_ov004_02256fec). */
int MusicPlayer_Stop(MusicPlayer *player)
{
    int vanishing = RoomObject_IsVanishing(&player->base);
    MusicPlayer_StopSong(player, player->song, vanishing);
    if (data_ov004_02256fec >= MUSIC_ITEM_FIRST && data_ov004_02256fec <= MUSIC_ITEM_LAST) {
        data_ov004_02256fec = ITEM_NONE;
    }
    return 1;
}
CLEAN_AS(func_ov004_02216630, MusicPlayer_Stop)

/* func_ov004_02216680 (vtable slot 0x84, each frame while appearing or vanishing): the same as
 * each frame otherwise (vtable slot 0x80, MusicPlayer_Update). */
void MusicPlayer_UpdateUnsettled(MusicPlayer *player)
{
    player->base.vtable->update_settled(&player->base);
}
CLEAN_AS(func_ov004_02216680, MusicPlayer_UpdateUnsettled)

/* _ZN18Obj_ov004_022517bc19func_ov004_02216694Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state, the talk step and the glows. */
int MusicPlayer_Update(MusicPlayer *player)
{
    MusicPlayer_UpdateState(player);
    MusicPlayer_UpdateTalkStep(player);
    GlowSet_Update(&player->glows);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022517bc19func_ov004_02216694Ev, MusicPlayer_Update)

/* Vtable slot 0x70 (MusicPlayer_EnterState): requests state `state` with `song`. */
static int MusicPlayer_request(MusicPlayer *player, int state, int song)
{
    return player->base.vtable->vfunc_70(&player->base, state, song);
}

/* func_ov004_022166b8 (vtable slot 0x7c, once the model is bound): kinds 0x13 and 0x29 load the
 * animations of variant 0, looping; the glows are bound, on as the switch shows. In mode 1
 * (unk_76C) STOPPED is requested for the object's cell (func_02052738). Otherwise, with the
 * switch on outside the areas func_ov004_0223c10c names, it plays:
 * - in a villager's house the villager's song (song 0 for no villager), noted as started
 *   (data_ov004_02256fec, the first song's item for a song past the last); but once a song was
 *   started there it stops instead;
 * - elsewhere the song of the house's music item; with none the item is set to none and it
 *   stops.
 * Else it stops. Done at once. */
int MusicPlayer_Start(MusicPlayer *player)
{
    RoomObject *base = &player->base;
    if (base->unk_780 == KIND_ANIMATED || base->unk_780 == KIND_13) {
        RoomObject_LoadAnims(base, 0, ANIM_MODE_LOOP, ONE, 0);
    }
    GlowSet_Bind(&player->glows, base->model_resource, Switch_Value(&base->light_switch));
    if (base->unk_76C == 1) {
        func_02052738(MusicPlayer_address(player), MUSIC_PLAYER_STOPPED, NO_VALUE, 1);
    } else if (Switch_Value(&base->light_switch) != 0 && func_ov004_0223c10c() == 0) {
        if (func_020b6680() != 0) {
            u32 song = 0;
            void *villager = func_0207cec0(data_021e5a2c, func_020b66b0());
            if (villager != NULL) {
                song = (u32) func_0207f2c4(villager);
            }
            if (data_ov004_02256fec >= MUSIC_ITEM_FIRST && data_ov004_02256fec <= MUSIC_ITEM_LAST) {
                MusicPlayer_request(player, MUSIC_PLAYER_STOPPED, NO_VALUE);
            } else if (MusicPlayer_request(player, MUSIC_PLAYER_PLAYING, (u8) song) != 0) {
                data_ov004_02256fec = song < SONG_COUNT ? (u16) (MUSIC_ITEM_FIRST + song) : MUSIC_ITEM_FIRST;
            }
        } else {
            u16 item = *func_02060b70();
            if (item >= MUSIC_ITEM_FIRST && item <= MUSIC_ITEM_LAST) {
                MusicPlayer_request(player, MUSIC_PLAYER_PLAYING, (u8) (item - MUSIC_ITEM_FIRST));
            } else {
                func_02060afc();
                MusicPlayer_request(player, MUSIC_PLAYER_STOPPED, NO_VALUE);
            }
        }
    } else {
        MusicPlayer_request(player, MUSIC_PLAYER_STOPPED, NO_VALUE);
    }
    return 1;
}
CLEAN_AS(func_ov004_022166b8, MusicPlayer_Start)

static void MusicPlayer_set_vtables(MusicPlayer *player)
{
    player->base.vtable = (const RoomObjectVtable *) data_ov004_022517bc;
    player->base.receiver_vtable = data_ov004_02251868;
}

/* func_ov004_02216820 (the deleting destructor, vtable slot 0x44) */
MusicPlayer *MusicPlayer_Delete(MusicPlayer *player)
{
    MusicPlayer_set_vtables(player);
    GlowSet_Destruct(&player->glows);
    RoomObject_DestructBase(&player->base);
    RoomObject_Free(player);
    return player;
}
CLEAN_AS(func_ov004_02216820, MusicPlayer_Delete)

/* func_ov004_02216858 (the destructor, vtable slot 0x40) */
MusicPlayer *MusicPlayer_Destroy(MusicPlayer *player)
{
    MusicPlayer_set_vtables(player);
    GlowSet_Destruct(&player->glows);
    RoomObject_DestructBase(&player->base);
    return player;
}
CLEAN_AS(func_ov004_02216858, MusicPlayer_Destroy)

/* func_ov004_0221688c (the constructor): the base, the vtables and the glows. Its other fields
 * are left as the allocation zeroed them. */
MusicPlayer *MusicPlayer_Construct(MusicPlayer *player)
{
    RoomObject_ConstructBase(&player->base);
    MusicPlayer_set_vtables(player);
    GlowSet_Construct(&player->glows);
    return player;
}
CLEAN_AS(func_ov004_0221688c, MusicPlayer_Construct)

/* func_ov004_022168bc: a new music player from the room's heap; nothing when it has no room. */
void MusicPlayer_Create(void)
{
    MusicPlayer *player = RoomObject_Alloc(MUSIC_PLAYER_SIZE);
    if (player != NULL) {
        MusicPlayer_Construct(player);
    }
}
CLEAN_AS(func_ov004_022168bc, MusicPlayer_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters MusicPlayer's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static MusicPlayer *MusicPlayer_from_receiver(void *receiver)
{
    return (MusicPlayer *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a804: the deleting destructor, entered from the receiver part. */
MusicPlayer *MusicPlayerReceiver_Delete(void *receiver)
{
    return MusicPlayer_Delete(MusicPlayer_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022517bcD0Ev, MusicPlayerReceiver_Delete)

/* func_ov004_0221a820: the destructor, entered from the receiver part. */
MusicPlayer *MusicPlayerReceiver_Destroy(void *receiver)
{
    return MusicPlayer_Destroy(MusicPlayer_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022517bcD1Ev, MusicPlayerReceiver_Destroy)
