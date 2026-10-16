/* The one link state the game has, as the rest of the game reaches it (link_global.h).
 *
 * REQUIRES: every slot passed here is not negative (the game passes 0-3, or 4 for none). */
#include "link_global.h"

#include "clean.h"
#include "link_parts.h"
#include "link_scene.h"
#include "scene_exit.h"
#include "session.h"

extern NetSession *data_020ccf94;
extern LinkState data_021f4320;

/* The one-byte request of session message 8 (the scene asked for): made, given its scene and
 * ended. */
extern void func_020a7948(void *request);
extern void func_020a7940(u8 *request, int scene);
extern void func_020a7944(void *request);
/* A slot's pending change added to (link_scene.h): the fields of `mask` set, `mask` or'ed in. */
extern void func_020a7794(LinkStatePlaceChange *change, u8 scene, u8 holder, u8 moving, u32 mask);

#define HOST_SLOT 0

#define MASK_SCENE 1
#define MASK_HOLDER 2
#define MASK_MOVING 4

/* Session messages and where they are sent (session_message.h, link_scene.h). */
#define MESSAGE_ASK_MOVE 8
#define TO_HOST 0

/* The addresses of a session message (Session_EndMessage's `kind`), past the slots 0-3. */
enum {
    TO_OTHERS = 4,         /* every system but the sender */
    TO_GUESTS = 5,         /* every system but the host */
    TO_SCENE_HOLDER = 6,   /* the system holding the message's scene */
    TO_SCENE_VISITORS = 7, /* the other systems in the message's scene that do not hold it */
};

/* The phase from which a moving system's new scene is being created (link_scene.h). */
#define PHASE_CREATING 7

/* func_020a6ec0 */
void LinkGlobal_SetServedSlot(int slot)
{
    LinkState_SetServedSlot(&data_021f4320, (u32) slot);
}
CLEAN_AS(func_020a6ec0, LinkGlobal_SetServedSlot)

/* func_020a6ed0 */
u32 LinkGlobal_ServedSlot(void)
{
    return LinkState_ServedSlot(&data_021f4320);
}
CLEAN_AS(func_020a6ed0, LinkGlobal_ServedSlot)

/* func_020a6ee0 */
u32 LinkGlobal_DoneKind(void)
{
    return LinkState_DoneKind(&data_021f4320);
}
CLEAN_AS(func_020a6ee0, LinkGlobal_DoneKind)

/* func_020a6ef0 */
void LinkGlobal_SetDoneKind(u32 kind)
{
    LinkState_SetDoneKind(&data_021f4320, kind);
}
CLEAN_AS(func_020a6ef0, LinkGlobal_SetDoneKind)

/* func_020a6f00 */
int LinkGlobal_Kind(void)
{
    return (int) LinkState_Kind(&data_021f4320);
}
CLEAN_AS(func_020a6f00, LinkGlobal_Kind)

/* func_020a6f10 */
void LinkGlobal_SetKind(u32 kind)
{
    LinkState_SetKind(&data_021f4320, kind);
}
CLEAN_AS(func_020a6f10, LinkGlobal_SetKind)

/* func_020a6f20 */
void LinkGlobal_SetAnswer(int slot, int answer)
{
    LinkState_SetAnswer(&data_021f4320, slot, answer);
}
CLEAN_AS(func_020a6f20, LinkGlobal_SetAnswer)

/* func_020a6f34 */
void LinkGlobal_SetChosen(int slot)
{
    LinkState_SetChosen(&data_021f4320, slot);
}
CLEAN_AS(func_020a6f34, LinkGlobal_SetChosen)

/* func_020a6f44: the session's member mask (the link state's halfword 0x98). */
u16 LinkGlobal_MemberMask(void)
{
    return LinkState_Half98(&data_021f4320);
}
CLEAN_AS(func_020a6f44, LinkGlobal_MemberMask)

/* func_020a6f54: the member mask set (its low halfword kept). */
void LinkGlobal_SetMemberMask(u32 members)
{
    LinkState_SetHalf98(&data_021f4320, (u16) members);
}
CLEAN_AS(func_020a6f54, LinkGlobal_SetMemberMask)

/* func_020a6f64 */
int LinkGlobal_Status(int slot)
{
    return LinkState_Status(&data_021f4320, slot);
}
CLEAN_AS(func_020a6f64, LinkGlobal_Status)

/* func_020a6f74 */
void LinkGlobal_SetStatus(int slot, int status)
{
    LinkState_SetStatus(&data_021f4320, slot, status);
}
CLEAN_AS(func_020a6f74, LinkGlobal_SetStatus)

/* func_020a6f88: the move to the entry record's next scene asked of the host: the host queues
 * it itself, a guest sends message 8 with the scene. */
void LinkGlobal_AskMove(void)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLocalSlot(session, HOST_SLOT)) {
        int own = session->local_slot;
        LinkGlobal_QueueMove(own, SceneExit_NextScene());
        return;
    }
    u8 request[1];
    func_020a7948(request);
    func_020a7940(request, SceneExit_NextScene());
    session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, request, sizeof(request));
    Session_EndMessage(session, MESSAGE_ASK_MOVE, TO_HOST);
    func_020a7944(request);
}
CLEAN_AS(func_020a6f88, LinkGlobal_AskMove)

/* func_020a6ff0: the slot that holds `scene` (the highest), preferring one that is not moving;
 * LINK_STATE_SLOTS when none does. Slots are not checked to be in the session. */
int LinkGlobal_SceneHolder(int scene)
{
    int still = LINK_STATE_SLOTS;
    int moving = LINK_STATE_SLOTS;

    for (int slot = 0; slot < LINK_STATE_SLOTS; slot++) {
        u8 place_scene;
        u8 holder;
        u8 place_moving;
        LinkPart_GetPlace(&data_021f4320.places[slot], &place_scene, &holder, &place_moving);
        if (place_scene == scene && holder != 0) {
            if (place_moving != 0) {
                moving = slot;
            } else {
                still = slot;
            }
        }
    }
    return still != LINK_STATE_SLOTS ? still : moving;
}
CLEAN_AS(func_020a6ff0, LinkGlobal_SceneHolder)

/* func_020a70ec: whether a session message of address `to` and scene `scene` reaches `slot`:
 * `slot` when it does, LINK_STATE_SLOTS when not. `hold` is set when the message is for the
 * holder of its scene, no system holds it still, and `slot` holds it while moving: the message
 * then waits until the scene's owner is known (Session_RouteHeldMessages). A message for the
 * visitors of its scene also reaches the slot this system sent its scene's state to, while it
 * is on its way. */
int LinkGlobal_MessageTarget(int slot, int to, int scene, u8 *hold)
{
    int own = data_020ccf94->local_slot;
    u8 place_scene;
    u8 holder;
    u8 moving;

    *hold = 0;
    switch (to) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (slot == to) {
                return slot;
            }
            break;
        case TO_OTHERS:
            if (slot != own) {
                return slot;
            }
            break;
        case TO_GUESTS:
            if (slot != HOST_SLOT) {
                return slot;
            }
            break;
        case TO_SCENE_HOLDER: {
            int owner = LinkGlobal_SceneOwner(scene);
            if (owner < LINK_STATE_SLOTS) {
                if (owner == slot) {
                    return slot;
                }
            } else {
                LinkPart_GetPlace(&data_021f4320.places[slot], &place_scene, &holder, &moving);
                if (place_scene == scene && holder != 0 && moving != 0) {
                    *hold = 1;
                }
            }
            break;
        }
        case TO_SCENE_VISITORS:
            LinkPart_GetPlace(&data_021f4320.places[slot], &place_scene, &holder, &moving);
            if (place_scene == scene) {
                if (holder == 0 && moving == 0 && slot != own) {
                    return slot;
                }
            } else {
                int sent_to = LinkScene_StateSentTo(&data_021f4320);
                if (sent_to < LINK_STATE_SLOTS && sent_to == slot && slot != own) {
                    return slot;
                }
            }
            break;
        default:
            break;
    }
    return LINK_STATE_SLOTS;
}
CLEAN_AS(func_020a70ec, LinkGlobal_MessageTarget)

/* func_020a71ec: the slot of the session that holds `scene` and is not moving (the highest);
 * LINK_STATE_SLOTS when none does. */
int LinkGlobal_SceneOwner(int scene)
{
    NetSession *session = data_020ccf94;

    for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
        u8 place_scene;
        u8 holder;
        u8 moving;
        if (!Session_IsSlotTaken(session, slot)) {
            continue;
        }
        LinkPart_GetPlace(&data_021f4320.places[slot], &place_scene, &holder, &moving);
        if (place_scene == scene && holder != 0 && moving == 0) {
            return slot;
        }
    }
    return LINK_STATE_SLOTS;
}
CLEAN_AS(func_020a71ec, LinkGlobal_SceneOwner)

/* func_020a7258: whether this system's place moves; 1 without a slot. */
int LinkGlobal_IsMoving(void)
{
    if (data_020ccf94->local_slot < LINK_STATE_SLOTS) {
        return LinkGlobal_PlaceMoving(data_020ccf94->local_slot);
    }
    return 1;
}
CLEAN_AS(func_020a7258, LinkGlobal_IsMoving)

/* func_020a7278: whether this system decides for its scene: whether it holds it, and while it
 * moves, once its new scene is being created, whether it enters that scene first. 1 without a
 * slot. */
int LinkGlobal_HoldsScene(void)
{
    int own = data_020ccf94->local_slot;
    u8 scene;
    u8 holder;
    u8 moving;

    if (own >= LINK_STATE_SLOTS) {
        return 1;
    }
    LinkPart_GetPlace(&data_021f4320.places[own], &scene, &holder, &moving);
    if (moving == 0) {
        return holder;
    }
    if (LinkScene_Phase(&data_021f4320) < PHASE_CREATING) {
        return holder;
    }
    return LinkScene_EntersFirst(&data_021f4320);
}
CLEAN_AS(func_020a7278, LinkGlobal_HoldsScene)

/* func_020a72d0: whether `slot`'s place moves; 0 for no slot. */
int LinkGlobal_PlaceMoving(int slot)
{
    u8 scene;
    u8 holder;
    u8 moving;

    if (slot >= LINK_STATE_SLOTS) {
        return 0;
    }
    LinkPart_GetPlace(&data_021f4320.places[slot], &scene, &holder, &moving);
    return moving;
}
CLEAN_AS(func_020a72d0, LinkGlobal_PlaceMoving)

/* func_020a7300: whether `slot` holds its scene; 1 for no slot. */
u8 LinkGlobal_PlaceHolder(int slot)
{
    u8 scene;
    u8 holder;
    u8 moving;

    if (slot >= LINK_STATE_SLOTS) {
        return 1;
    }
    LinkPart_GetPlace(&data_021f4320.places[slot], &scene, &holder, &moving);
    return holder;
}
CLEAN_AS(func_020a7300, LinkGlobal_PlaceHolder)

/* func_020a7330: `slot`'s scene; LINK_SCENE_NONE for no slot. */
int LinkGlobal_PlaceScene(int slot)
{
    u8 scene;
    u8 holder;
    u8 moving;

    if (slot >= LINK_STATE_SLOTS) {
        return LINK_SCENE_NONE;
    }
    LinkPart_GetPlace(&data_021f4320.places[slot], &scene, &holder, &moving);
    return scene;
}
CLEAN_AS(func_020a7330, LinkGlobal_PlaceScene)

/* func_020a7360: `slot`'s pending change added to: the fields of `mask` (bit 0 the scene, 1
 * holder, 2 moving). */
void LinkGlobal_AddPlaceChange(int slot, int scene, int holder, int moving, int mask)
{
    func_020a7794(&data_021f4320.changes[slot], (u8) scene, (u8) holder, (u8) moving, (u32) mask);
}
CLEAN_AS(func_020a7360, LinkGlobal_AddPlaceChange)

/* func_020a7380: `slot`'s arrived word set. */
void LinkGlobal_SetArrived(int slot, int value)
{
    LinkPart_SetArrived(&data_021f4320.arrived[slot], value);
}
CLEAN_AS(func_020a7380, LinkGlobal_SetArrived)

/* func_020a7394: `slot`'s place given the fields of `mask` (bit 0 the scene, 1 holder, 2
 * moving); a scene may now have an owner, so the held session messages are routed. */
void LinkGlobal_SetPlace(int slot, int scene, int holder, int moving, int mask)
{
    LinkStatePlace *place = &data_021f4320.places[slot];
    u8 new_scene;
    u8 new_holder;
    u8 new_moving;

    LinkPart_GetPlace(place, &new_scene, &new_holder, &new_moving);
    if (mask & MASK_SCENE) {
        new_scene = (u8) scene;
    }
    if (mask & MASK_HOLDER) {
        new_holder = (u8) holder;
    }
    if (mask & MASK_MOVING) {
        new_moving = (u8) moving;
    }
    LinkPart_SetPlace(place, new_scene, new_holder, new_moving);
    Session_RouteHeldMessages(data_020ccf94);
}
CLEAN_AS(func_020a7394, LinkGlobal_SetPlace)

/* func_020a7408 (host): a move of `slot` to `scene` put in the first empty entry of the queue.
 * QUIRK: with the queue full the move is dropped. */
void LinkGlobal_QueueMove(int slot, int scene)
{
    LinkStateMove *move = data_021f4320.moves;

    for (int left = LINK_STATE_SLOTS; left > 0; left--) {
        s32 move_slot;
        u8 move_scene;
        LinkPart_GetMove(move, &move_slot, &move_scene);
        if (move_slot >= LINK_STATE_SLOTS) {
            LinkPart_SetMove(move, slot, scene);
            return;
        }
        move++;
    }
}
CLEAN_AS(func_020a7408, LinkGlobal_QueueMove)

/* func_020a7448: called when a scene's process is first created; does nothing. */
void LinkGlobal_Empty7448(void) {}
CLEAN_AS(func_020a7448, LinkGlobal_Empty7448)

/* func_020a744c: always 0 (asked before a moving holder chooses a successor and before it
 * sends its scene's state). */
int LinkGlobal_Zero744C(void)
{
    return 0;
}
CLEAN_AS(func_020a744c, LinkGlobal_Zero744C)

/* func_020a7450: always 0 (asked before a moving holder chooses a successor). */
int LinkGlobal_Zero7450(void)
{
    return 0;
}
CLEAN_AS(func_020a7450, LinkGlobal_Zero7450)
