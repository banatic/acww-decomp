/* The walrus's talk scene (class vtable 0x0227a074, at 0x658 of the walrus, walrus.h): a scene
 * of class 0x020d9ff8 (obj_020d9ff8.h) that shows the lines of the archive "sp_npc_walrus".
 *
 * He asks the player for an item. The player picks one of the pockets (any of a slot of state
 * 0, WalrusTalk_IsOfferable); he takes it, unless it is one of the six tools 0x136a, 0x1373,
 * 0x1375, 0x1377, 0x1379, 0x137b (line 0x0b), with line 3 for one of his special items (a fish,
 * 0x12e8-0x131f, or one of 0x1518-0x151c, 0x1531-0x153a, 0x153b-0x1541, 0x1542-0x1546 and
 * 0x1548), else line 2. After a special item he gives item 0x13ac (or, one time in two,
 * 0x3530) for one of 0x153b-0x1541; for the others he offers a design (line 4): the player
 * picks a slot of the player's designs (screen mode 10) and he copies one of the design samples
 * (design kind 7) into it, the sample chosen by the item he took (WalrusTalk_GiveDesign);
 * clothes, a hat or an umbrella the player has on made from that slot are put on again. Daily
 * bit 10 of the player marks that he took an item today.
 *
 * Its vtable slots:
 * - 0x08 (WalrusTalk_Reset): reset, no item, nothing to run;
 * - 0x10 (WalrusTalk_Slot10): while line 0x0f is shown, motion 19 of the scene's commands;
 * - 0x14 (WalrusTalk_OnLineShown): what follows the line shown;
 * - 0x18 (WalrusTalk_OnAnswer): the player's answer to the line shown;
 * - 0x78 (WalrusTalk_Line): the first line: 0, or one of 6-8 once he took an item today;
 * - 0x84 (WalrusTalk_RunAfterCommand): when a command of the scene ends, what was left to run
 *   after it (WalrusTalk_SetAfterCommand), and then what was left to run after that
 *   (WalrusTalk_SetNextAfterCommand). */
#ifndef CLEAN_OV079_WALRUS_TALK_H
#define CLEAN_OV079_WALRUS_TALK_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Walrus;

/* What runs after a command of the scene (WalrusTalk_SetAfterCommand). */
#define WALRUS_TALK_AFTER_OFFERING 0  /* the pockets' screen ended: WalrusTalk_TakeOffering */
#define WALRUS_TALK_AFTER_NEXT_LINE 1 /* WalrusTalk_NextLine */
#define WALRUS_TALK_AFTER_DESIGN 2    /* the designs' screen ended: WalrusTalk_GiveDesign */
#define WALRUS_TALK_AFTERS 3

/* The talk scene (0xcc bytes). */
typedef struct WalrusTalk {
    SceneBase scene;             /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    struct Walrus *owner;        /* 0xb0 */
    MemberPointer after_command; /* 0xb4: run once when a command of the scene ends */
    MemberPointer next_after;    /* 0xbc: becomes after_command once that ran */
    u16 item;                    /* 0xc4: the item the player gave, 0xfff1 for none */
    u8 unk_c6[2];                /* 0xc6 */
    s32 slot;                    /* 0xc8: its slot in the pockets, -1 for none */
} WalrusTalk;

/* What its slot 0x78 gives: the archive's name and the line to say. */
typedef struct WalrusTalkLine {
    const char *name;
    u8 message;
    u8 unk_05[3];
} WalrusTalkLine;

/* Its slots. */
void WalrusTalk_OnAnswer(WalrusTalk *talk);
void WalrusTalk_OnLineShown(WalrusTalk *talk);
void WalrusTalk_Slot10(WalrusTalk *talk);
void WalrusTalk_Line(WalrusTalk *talk, WalrusTalkLine *line);
void WalrusTalk_Begin(WalrusTalk *talk, struct Walrus *owner);
void WalrusTalk_Reset(WalrusTalk *talk);
void WalrusTalk_RunAfterCommand(WalrusTalk *talk);
int WalrusTalk_IsOfferable(u16 *item, int state);

/* Its life. */
WalrusTalk *WalrusTalk_DestructDelete(WalrusTalk *talk);
WalrusTalk *WalrusTalk_Destruct(WalrusTalk *talk);
WalrusTalk *WalrusTalk_Construct(WalrusTalk *talk);

/* What runs after a command. */
void WalrusTalk_GiveDesign(WalrusTalk *talk);
void WalrusTalk_NextLine(WalrusTalk *talk);
void WalrusTalk_TakeOffering(WalrusTalk *talk);
void WalrusTalk_SetNextAfterCommand(WalrusTalk *talk, int after);
void WalrusTalk_SetAfterCommand(WalrusTalk *talk, int after);
void WalrusTalk_FromTable(WalrusTalk *unused, MemberPointer *out, int after);

#endif
