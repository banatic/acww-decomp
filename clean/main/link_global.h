/* The one link state the game has (data_021f4320, link_state.h and link_scene.h) as the rest of
 * the game reaches it: its fields read and set, slots' places looked up, the scene holder a
 * session message goes to, and the moves asked of the host. */
#ifndef CLEAN_MAIN_LINK_GLOBAL_H
#define CLEAN_MAIN_LINK_GLOBAL_H

#include "link_state.h"
#include "types.h"

void LinkGlobal_SetServedSlot(int slot);
u32 LinkGlobal_ServedSlot(void);
u32 LinkGlobal_DoneKind(void);
void LinkGlobal_SetDoneKind(u32 kind);
int LinkGlobal_Kind(void);
void LinkGlobal_SetKind(u32 kind);
void LinkGlobal_SetAnswer(int slot, int answer);
void LinkGlobal_SetChosen(int slot);
u16 LinkGlobal_MemberMask(void);
void LinkGlobal_SetMemberMask(u32 members);
int LinkGlobal_Status(int slot);
void LinkGlobal_SetStatus(int slot, int status);

void LinkGlobal_AskMove(void);
int LinkGlobal_SceneHolder(int scene);
int LinkGlobal_MessageTarget(int slot, int to, int scene, u8 *hold);
int LinkGlobal_SceneOwner(int scene);
int LinkGlobal_IsMoving(void);
int LinkGlobal_HoldsScene(void);
int LinkGlobal_PlaceMoving(int slot);
u8 LinkGlobal_PlaceHolder(int slot);
int LinkGlobal_PlaceScene(int slot);
void LinkGlobal_AddPlaceChange(int slot, int scene, int holder, int moving, int mask);
void LinkGlobal_SetArrived(int slot, int value);
void LinkGlobal_SetPlace(int slot, int scene, int holder, int moving, int mask);
void LinkGlobal_QueueMove(int slot, int scene);
void LinkGlobal_Empty7448(void);
int LinkGlobal_Zero744C(void);
int LinkGlobal_Zero7450(void);

#endif
