/* A room object of the RMO family (rmo_object.h; vtable 0x022558f8, receiver part 0x02255974
 * at 0x290, 0x644 bytes) built from /roomObj/obj_telephone, that talks with the message file
 * "sp_etc_sequence1". Not the room objects' telephone of telephone.h. Only one exists at a
 * time: data_ov004_022588c8 points to it from its start to its release.
 *
 * Its state (RmoTelephone.state, 0 to 14) has an entry and an update, as pairs of member
 * pointers in the table data_ov004_022588d8 (filled by __sinit_ov004_0224ebd8); one of them may
 * be none. func_ov004_0223121c enters a state (running its entry, then setting it whatever the
 * entry did) and func_ov004_022316a4 runs the state's update each frame. The states these
 * functions belong to:
 *
 * - 10: its talk started over its receiver (message 0xe); on once the talk has opened (11);
 * - 11 and 12: once the talk has closed, its receiver let go and on to state 7;
 * - 13: once the talk is gone, the screen of group 0x30 opened and on to 14;
 * - 14: once that screen has closed, the talk shows message 0x10 or 0x18, then state 12 (in
 *   scene 6) or 4.
 *
 * Other overlay 4 code restarts the body's first joint animation from its end, forwards or
 * backwards, or from its start, and asks for state 10. */
#ifndef CLEAN_OV004_RMO_TELEPHONE_H
#define CLEAN_OV004_RMO_TELEPHONE_H

#include "main/collision_box.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "rmo_object.h"
#include "types.h"

typedef struct RmoTelephone {
    RmoObject base;                                 /* 0x000 */
    TalkReceiver receiver;                          /* 0x290: vtable data_ov004_02255974 */
    CollisionBox box;                               /* 0x2d8 */
    TouchPickFace pick_faces[TOUCH_PICK_BOX_FACES]; /* 0x374 */
    u8 unk_61c[0x1c];                               /* 0x61c: built by func_020b7f70 */
    s32 state;                                      /* 0x638: 0 to 14 */
    u8 talking;                                     /* 0x63c: set while it holds the talk */
    u8 unk_63d[3];                                  /* 0x63d */
    s32 unk_640;                                    /* 0x640 */
} RmoTelephone;

void RmoTelephone_PlayFromEnd(void);
void RmoTelephone_PlayBackFromEnd(void);
void RmoTelephone_PlayFromStart(void);
int RmoTelephone_EnterState10Current(void);
int RmoTelephone_IsTalking(void);
void RmoTelephone_StartTalk(RmoTelephone *self, const char *name, u8 message);
void RmoTelephone_UpdateState14(RmoTelephone *self);
void RmoTelephone_EnterState14(void);
void RmoTelephone_UpdateState13(RmoTelephone *self);
void RmoTelephone_EnterState13(void);
void RmoTelephone_UpdateState12(RmoTelephone *self);
void RmoTelephone_EnterState12(void);
void RmoTelephone_UpdateState11(RmoTelephone *self);
void RmoTelephone_EnterState11(void);
void RmoTelephone_UpdateState10(RmoTelephone *self);

#endif
