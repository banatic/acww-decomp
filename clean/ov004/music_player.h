/* The music players: a class of overlay 4's room objects (vtable 0x022517bc, receiver part
 * 0x02251868) that plays one of the 70 songs of the music items 0x1323-0x1368 (song n is item
 * 0x1323 + n, played as music 0xb0 + n by MusicPlayer_PlaySong and stopped by
 * MusicPlayer_StopSong). It has three glowing materials (a GlowSet, room_object_parts.h) that
 * fade in while it plays. Kind 0x29 (RoomObject.unk_780) also animates while playing.
 *
 * Its state (MusicPlayer.state) runs through tables of member pointers (member_pointer.h),
 * entered through vtable slot 0x70 with the song as the value it keeps (RoomObject.unk_77C):
 * - MUSIC_PLAYER_STOPPED (0): entered with the sound at 4 and the switch off, the song stopped
 *   unless the model is being bound; kind 0x29 plays the animations of variant 0 once;
 * - MUSIC_PLAYER_PLAYING (1): entered with the sound at 2, every room object with unk_00C 0x3a
 *   that is on switched off (this one included), then the switch on and the song played; kind
 *   0x29 loops the animations of variant 1. Each frame the sound at 0 follows the object.
 * Touching it does not switch it: the switch is put back and the scene is asked for an event
 * (func_0203e0a8), whose answer (vtable slot 0x4c) starts a talk: event 1 the song menu when
 * func_020b67d4 and Room_Check0220fed0 allow it, else the talk that tells the song; event 8
 * ends the talk.
 *
 * Once its model is bound (vtable slot 0x7c) it plays when its switch is on, outside the areas
 * func_ov004_0223c10c names: in a villager's house the villager's song, unless a player already
 * started it there (data_ov004_02256fec), elsewhere the house's music item; else it is
 * stopped. Vtable slot 0x0c stops the song and forgets the villager's song started.
 *
 * The talk has its own steps (MusicPlayer.talk_step), entered by MusicPlayer_EnterTalkStep,
 * with another two tables:
 * - MUSIC_PLAYER_TALK_NONE (0);
 * - MUSIC_PLAYER_TALK_MENU_NEXT (1): the next frame opens the menu;
 * - MUSIC_PLAYER_TALK_MENU (2): the song menu (group 9 in mode 0x40) is opened on entry, a step
 *   refused when it cannot be; once it has closed, a song chosen there is requested
 *   (MUSIC_PLAYER_PLAYING with the song) and the scene goes on (func_0203e020);
 * - MUSIC_PLAYER_TALK_NEXT (3): the next frame talks;
 * - MUSIC_PLAYER_TALK (4): it takes the receiver as "obj_etc_player" and tells the song of the
 *   place (in a villager's house the villager's, else the house's music item); it waits for
 *   the link to open;
 * - MUSIC_PLAYER_TALK_END (5): once the link has closed, the receiver is handed back and the
 *   scene goes on. */
#ifndef CLEAN_OV004_MUSIC_PLAYER_H
#define CLEAN_OV004_MUSIC_PLAYER_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct MusicPlayer {
    RoomObject base;
    u8 playing; /* its song is playing (set by MusicPlayer_PlaySong, cleared by MusicPlayer_StopSong) */
    u8 song;    /* the song it plays, 0 to 69 (0xff when asked for an item that is no music) */
    u8 unk_846[2];
    GlowSet glows;
    u8 state; /* MusicPlayerState */
    u8 unk_8a1[3];
    s32 talk_step; /* MusicPlayerTalkStep */
} MusicPlayer;

enum MusicPlayerState { MUSIC_PLAYER_STOPPED = 0, MUSIC_PLAYER_PLAYING = 1, MUSIC_PLAYER_STATE_COUNT = 2 };

enum MusicPlayerTalkStep {
    MUSIC_PLAYER_TALK_NONE = 0,
    MUSIC_PLAYER_TALK_MENU_NEXT = 1,
    MUSIC_PLAYER_TALK_MENU = 2,
    MUSIC_PLAYER_TALK_NEXT = 3,
    MUSIC_PLAYER_TALK = 4,
    MUSIC_PLAYER_TALK_END = 5,
    MUSIC_PLAYER_TALK_STEP_COUNT = 6
};

int MusicPlayer_UpdatePlaying(MusicPlayer *player);
int MusicPlayer_EnterPlaying(MusicPlayer *player);
void MusicPlayer_UpdateStopped(MusicPlayer *player);
int MusicPlayer_EnterStopped(MusicPlayer *player);
void MusicPlayer_UpdateState(MusicPlayer *player);
int MusicPlayer_EnterState(MusicPlayer *player, unsigned int state, int value);
u8 MusicPlayer_StateIsOn(MusicPlayer *player, unsigned int state);
void MusicPlayer_UpdateTalkEnd(MusicPlayer *player);
int MusicPlayer_EnterTalkEnd(MusicPlayer *player);
void MusicPlayer_UpdateTalk(MusicPlayer *player);
int MusicPlayer_EnterTalk(MusicPlayer *player);
void MusicPlayer_UpdateTalkNext(MusicPlayer *player);
int MusicPlayer_EnterTalkNext(MusicPlayer *player);
void MusicPlayer_UpdateTalkMenu(MusicPlayer *player);
int MusicPlayer_EnterTalkMenu(MusicPlayer *player);
void MusicPlayer_UpdateTalkMenuNext(MusicPlayer *player);
int MusicPlayer_EnterTalkMenuNext(MusicPlayer *player);
void MusicPlayer_UpdateTalkNone(MusicPlayer *player);
int MusicPlayer_EnterTalkNone(MusicPlayer *player);
void MusicPlayer_UpdateTalkStep(MusicPlayer *player);
int MusicPlayer_EnterTalkStep(MusicPlayer *player, int step);
void MusicPlayer_OnSceneEvent(MusicPlayer *player, int event);
void MusicPlayer_StopSong(MusicPlayer *player, unsigned int song, int clear_item);
void MusicPlayer_PlaySong(MusicPlayer *player, unsigned int song);
int MusicPlayer_Stop(MusicPlayer *player);
void MusicPlayer_UpdateUnsettled(MusicPlayer *player);
int MusicPlayer_Update(MusicPlayer *player);
int MusicPlayer_Start(MusicPlayer *player);
MusicPlayer *MusicPlayer_Delete(MusicPlayer *player);
MusicPlayer *MusicPlayer_Destroy(MusicPlayer *player);
MusicPlayer *MusicPlayer_Construct(MusicPlayer *player);
void MusicPlayer_Create(void);
MusicPlayer *MusicPlayerReceiver_Delete(void *receiver);
MusicPlayer *MusicPlayerReceiver_Destroy(void *receiver);

#endif
