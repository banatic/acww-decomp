/* The talk scene of a town villager (class with vtable 0x020d9df8, villager_talk.h): its
 * constructors and destructors, its vtable slots of its own and the setters of its member
 * function pointers.
 *
 * Its own vtable slots:
 * - 0x20 to 0x30: the focus speaker (scene_base.h) asked for mood 0 to 4 (the speaker's slot
 *   0xa4, villager_mood.h) for a length (0 for mood 0);
 * - 0x60: the talk asked for (SceneTalk_Request) without the camera;
 * - 0x68: the town record of the villager whose turn it is (VillagerTalkScene_SpeakerOf);
 * - 0x70: the step at 0xf8 run once; 0x7c: the member at 0xe8 run once;
 * - 0x78: the line member at 0xb0 run with the caller's VillagerTalkLine;
 * - 0x80: each step, the walk at 0xf0 run;
 * - 0x84: when a command ends, the member at 0xd8 run once, the one at 0xe0 then taking its
 *   place.
 *
 * Also here: the helpers the talk's states share: the villager's motion asked to stand, two
 * questions about the player's pockets, the player's memory noted by the villager, and a line
 * drawn for a personality. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_SCENE_H
#define CLEAN_MAIN_VILLAGER_TALK_SCENE_H

#include "mail.h"
#include "ov004/member_pointer.h"
#include "player_pockets.h"
#include "types.h"
#include "villager_talk.h"

int VillagerTalkScene_Stand(VillagerTalk *talk);
MailLetter *VillagerTalkScene_LetterToSend(PlayerPockets *pockets);
int VillagerTalkScene_PocketOfItem(PlayerPockets *pockets, u16 *item);
void VillagerTalkScene_RunMusic(VillagerTalk *talk);
void VillagerTalkScene_AskMood4(VillagerTalk *talk, int length);
void VillagerTalkScene_AskMood3(VillagerTalk *talk, int length);
void VillagerTalkScene_AskMood2(VillagerTalk *talk, int length);
void VillagerTalkScene_AskMood1(VillagerTalk *talk, int length);
void VillagerTalkScene_AskMood0(VillagerTalk *talk);
int VillagerTalkScene_RequestTalk(VillagerTalk *talk);
void VillagerTalkScene_NoteMemory(VillagerTalk *talk, u8 **memory, s32 *index, u8 *villager, int player);
void VillagerTalkScene_RunLine(VillagerTalk *talk, VillagerTalkLine *line);
u32 VillagerTalkScene_Object(VillagerTalk *talk);
void VillagerTalkScene_SetObject(VillagerTalk *talk, u32 object);
void *VillagerTalkScene_SpeakerRecord(VillagerTalk *talk);
int VillagerTalkScene_SpeakerOf(VillagerTalk *talk, int speaker);
int VillagerTalkScene_DrawLine(VillagerTalk *talk, char *text, u8 *message, int size, int personality, int texts,
                               int per_group, int group, int range);
void VillagerTalkScene_SetReply(VillagerTalk *talk, MemberPointer reply);
void VillagerTalkScene_SetLines(VillagerTalk *talk, const MemberPointer *table);
void VillagerTalkScene_ClearLines(VillagerTalk *talk);
void VillagerTalkScene_RunOnceE8(VillagerTalk *talk);
void VillagerTalkScene_SetE8(VillagerTalk *talk, MemberPointer member);
void VillagerTalkScene_OnCommandEnd(VillagerTalk *talk);
void VillagerTalkScene_SetNextCommandEnd(VillagerTalk *talk, MemberPointer member);
void VillagerTalkScene_SetCommandEnd(VillagerTalk *talk, MemberPointer member);
void VillagerTalkScene_Step(VillagerTalk *talk);
void VillagerTalkScene_Start(VillagerTalk *talk, u8 *villager, unsigned int lines);
VillagerTalk *VillagerTalkScene_DestructBody(VillagerTalk *talk);
VillagerTalk *VillagerTalkScene_DestructDelete(VillagerTalk *talk);
VillagerTalk *VillagerTalkScene_Destruct(VillagerTalk *talk);
VillagerTalk *VillagerTalkScene_Construct(VillagerTalk *talk);
VillagerTalk *VillagerTalkScene_ConstructAlt(VillagerTalk *talk);

#endif
