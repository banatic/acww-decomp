/* The mark that blinks during a linked game's screen transitions (transition_mark.h). */
#include "transition_mark.h"

#include "autoload_2/heap.h" /* Heap_AllocAuxZeroed, Heap_FreeAux, Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "display_shadow.h" /* DisplayShadow_EnableMainWindows, ... */
#include "oam_buffer.h"     /* OamBuffer_DrawCell */
#include "session.h"        /* Session_IsLinked */

#include "ov004/member_pointer.h" /* MemberPointer */

static_assert(offsetof(TransitionMark, anim) == 0x0c && offsetof(TransitionMark, state) == 0x20, "TransitionMark");
static_assert(offsetof(TransitionMark, next_tick) == 0x30 && offsetof(TransitionMark, suppressed) == 0x39, "TransitionMark");
static_assert(sizeof(TransitionMark) == 0x3c, "TransitionMark");
static_assert(sizeof(TransitionMarkProcess) == 0x50, "TransitionMarkProcess");

/* The mark, and the game's symbol for it from its state (0x20) on, through which the scene's
 * display set-up reaches its `suppressed` byte. */
extern TransitionMark data_021d3654;
extern u8 data_021d3674[];
#define TRANSITION_MARK_TAIL offsetof(TransitionMark, state)

/* The vtables of the mark and of the process, and the process's base class's. */
extern const u32 data_020e2400[];
extern const u32 data_020e241c[];
extern const u32 data_020da13c[];

/* The mark's animation. */
extern const CellAnimData data_020d71f4;

/* By the transition's kind: the frames the blinking lasts once the screen opens, and the
 * frames before it starts once the screen closes. */
extern const u8 data_020d0ba8[];
extern const u8 data_020d0ba4[];

/* The running scene's process (its class tells the scene change, 5), and the session. */
extern Process *data_021f42f4;
extern NetSession *data_020ccf94;
#define TRANSITION_MARK_SCENE_CHANGE_CLASS 5

extern u64 OS_GetTick(void);

/* The parts of the blink, in system ticks (64 cycles of 33.514 MHz): 0.2 s and 0.6 s. */
#define TRANSITION_MARK_TICKS_SHORT 0x1991b
#define TRANSITION_MARK_TICKS_LONG 0x4cb51

/* The main screen's OBJ window, with the OBJs inside it; and BG2 outside the windows. */
#define TRANSITION_MARK_PLANE_BG2 0x04
#define TRANSITION_MARK_PLANE_OBJ 0x10
#define TRANSITION_MARK_WINDOW_OBJ 0x04

#define TRANSITION_MARK_FX_ONE 0x1000
#define TRANSITION_MARK_OBJ_MODE_WINDOW 2

/* The mark's vtable slots: draw and update. */
#define TRANSITION_MARK_SLOT_DRAW 2
#define TRANSITION_MARK_SLOT_UPDATE 3

static void transition_mark_set_next_tick(TransitionMark *mark, u64 tick)
{
    mark->next_tick[0] = (u32) tick;
    mark->next_tick[1] = (u32) (tick >> 32);
}

static u64 transition_mark_next_tick(const TransitionMark *mark)
{
    return ((u64) mark->next_tick[1] << 32) | mark->next_tick[0];
}

static void transition_mark_set_suppressed(u8 value)
{
    data_021d3674[offsetof(TransitionMark, suppressed) - TRANSITION_MARK_TAIL] = value;
}

/* func_0208f660 (vtable slot 9, the DRAW phase): the mark drawn. */
int TransitionMarkProcess_Draw(void)
{
    TransitionMark_DrawInstance();
    return 1;
}
CLEAN_AS(func_0208f660, TransitionMarkProcess_Draw)

/* func_0208f670 (vtable slot 6, the EXECUTE phase): the mark updated. */
int TransitionMarkProcess_Execute(void)
{
    TransitionMark_UpdateInstance();
    return 1;
}
CLEAN_AS(func_0208f670, TransitionMarkProcess_Execute)

/* func_0208f680 (vtable slot 3, the DELETE phase): the mark stopped. */
int TransitionMarkProcess_Delete(void)
{
    TransitionMark_RewindInstance();
    return 1;
}
CLEAN_AS(func_0208f680, TransitionMarkProcess_Delete)

/* func_0208f690 (vtable slot 0, the CREATE phase): the mark reset. */
int TransitionMarkProcess_Create(void)
{
    TransitionMark_ResetInstance();
    return 1;
}
CLEAN_AS(func_0208f690, TransitionMarkProcess_Create)

/* func_0208f6a0: the destructor, then the process freed. */
TransitionMarkProcess *TransitionMarkProcess_DestructFree(TransitionMarkProcess *process)
{
    process->process.vtable = data_020e241c;
    process->process.vtable = data_020da13c;
    Process_Destruct(&process->process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_0208f6a0, TransitionMarkProcess_DestructFree)

/* func_0208f6c8: the destructor. */
TransitionMarkProcess *TransitionMarkProcess_Destruct(TransitionMarkProcess *process)
{
    process->process.vtable = data_020e241c;
    process->process.vtable = data_020da13c;
    Process_Destruct(&process->process);
    return process;
}
CLEAN_AS(func_0208f6c8, TransitionMarkProcess_Destruct)

/* func_0208f6e8: the constructor. */
TransitionMarkProcess *TransitionMarkProcess_Construct(TransitionMarkProcess *process)
{
    Process_Construct(&process->process);
    process->process.vtable = data_020da13c;
    process->process.vtable = data_020e241c;
    return process;
}
CLEAN_AS(func_0208f6e8, TransitionMarkProcess_Construct)

/* func_0208f708: the profile's create: a new process (zeroed, from the auxiliary heap),
 * nothing when there is no room.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * process (or NULL) in r0, the register a profile's create returns it in. */
void TransitionMarkProcess_New(void)
{
    TransitionMarkProcess *process = Heap_AllocAuxZeroed(sizeof(TransitionMarkProcess));
    if (process != NULL) {
        TransitionMarkProcess_Construct(process);
    }
}
CLEAN_AS(func_0208f708, TransitionMarkProcess_New)

/* func_0208f720: the mark's animation set, held on its last frame, from its start. */
void TransitionMark_SetAnim(TransitionMark *mark)
{
    CellAnim_SetData(&mark->anim, &data_020d71f4);
    CellAnim_SetHold(&mark->anim, 1);
    CellAnim_Restart(&mark->anim);
}
CLEAN_AS(func_0208f720, TransitionMark_SetAnim)

/* func_0208f748 (state 1): once the tick of the next part is reached, the next part of the
 * blink: shown (0.2 s), hidden (0.2 s), shown (0.2 s), hidden (0.6 s). Then, while
 * `frames_left` runs, one frame less, and at its end the OBJ window disabled and the mark
 * stopped. */
void TransitionMark_StepBlinking(TransitionMark *mark)
{
    u64 now = OS_GetTick();
    if (now >= transition_mark_next_tick(mark)) {
        switch (mark->blink_step) {
            case 0:
                transition_mark_set_next_tick(mark, now + TRANSITION_MARK_TICKS_SHORT);
                mark->shown = 1;
                mark->blink_step = 1;
                break;
            case 1:
                transition_mark_set_next_tick(mark, now + TRANSITION_MARK_TICKS_SHORT);
                mark->shown = 0;
                mark->blink_step = 2;
                break;
            case 2:
                transition_mark_set_next_tick(mark, now + TRANSITION_MARK_TICKS_SHORT);
                mark->shown = 1;
                mark->blink_step = 3;
                break;
            case 3:
                transition_mark_set_next_tick(mark, now + TRANSITION_MARK_TICKS_LONG);
                mark->shown = 0;
                mark->blink_step = 0;
                break;
            default:
                break;
        }
    }
    if (mark->frames_left > 0) {
        mark->frames_left--;
        if (mark->frames_left <= 0) {
            DisplayShadow_DisableMainWindows(TRANSITION_MARK_WINDOW_OBJ);
            TransitionMark_Stop(mark);
        }
    }
}
CLEAN_AS(func_0208f748, TransitionMark_StepBlinking)

/* func_0208f7f8: blinking, from its first part (shown for 0.2 s), until told how many frames
 * more; the main screen's OBJ window enabled with the OBJs inside it. */
void TransitionMark_Start(TransitionMark *mark)
{
    mark->state = TRANSITION_MARK_BLINKING;
    mark->frames_left = 0;
    DisplayShadow_SetMainObjWindowPlanes(TRANSITION_MARK_PLANE_OBJ);
    DisplayShadow_EnableMainWindows(TRANSITION_MARK_WINDOW_OBJ);
    u64 now = OS_GetTick();
    mark->blink_step = 1;
    transition_mark_set_next_tick(mark, now + TRANSITION_MARK_TICKS_SHORT);
    mark->shown = 1;
}
CLEAN_AS(func_0208f7f8, TransitionMark_Start)

/* func_0208f838 (state 0): while `delay` runs, one frame less, and at its end blinking. */
void TransitionMark_StepWaiting(TransitionMark *mark)
{
    if (mark->delay <= 0) {
        return;
    }
    mark->delay--;
    if (mark->delay <= 0) {
        TransitionMark_Start(mark);
    }
}
CLEAN_AS(func_0208f838, TransitionMark_StepWaiting)

/* func_0208f858: waiting with no delay, not shown (the OBJ window is left as it is). */
void TransitionMark_Stop(TransitionMark *mark)
{
    mark->state = TRANSITION_MARK_WAITING;
    mark->delay = 0;
    mark->shown = 0;
}
CLEAN_AS(func_0208f858, TransitionMark_Stop)

/* func_0208f864: the mark's vtable slot 2 (its draw) called; its result passed on. */
void *TransitionMark_CallDraw(TransitionMark *mark)
{
    return ((void *(*) (TransitionMark *) )(uintptr_t) mark->base.vtable[TRANSITION_MARK_SLOT_DRAW])(mark);
}
CLEAN_AS(func_0208f864, TransitionMark_CallDraw)

/* func_0208f874: the mark's vtable slot 3 (its update) called; its result passed on. */
void *TransitionMark_CallUpdate(TransitionMark *mark)
{
    return ((void *(*) (TransitionMark *) )(uintptr_t) mark->base.vtable[TRANSITION_MARK_SLOT_UPDATE])(mark);
}
CLEAN_AS(func_0208f874, TransitionMark_CallUpdate)

/* func_0208f884 */
void TransitionMark_Rewind(TransitionMark *mark)
{
    TransitionMark_Stop(mark);
}
CLEAN_AS(func_0208f884, TransitionMark_Rewind)

/* func_0208f88c: the animation set, no delay nor frames left, the blink at its first part
 * with the tick reached, not shown and not suppressed. The state is left as it is. */
void TransitionMark_Reset(TransitionMark *mark)
{
    TransitionMark_SetAnim(mark);
    mark->delay = 0;
    mark->frames_left = 0;
    mark->blink_step = 0;
    mark->next_tick[0] = 0;
    mark->next_tick[1] = 0;
    mark->shown = 0;
    mark->suppressed = 0;
}
CLEAN_AS(func_0208f88c, TransitionMark_Reset)

/* func_0208f8b0 */
void TransitionMark_DrawInstance(void)
{
    TransitionMark_CallDraw(&data_021d3654);
}
CLEAN_AS(func_0208f8b0, TransitionMark_DrawInstance)

/* func_0208f8c0 */
void TransitionMark_UpdateInstance(void)
{
    TransitionMark_CallUpdate(&data_021d3654);
}
CLEAN_AS(func_0208f8c0, TransitionMark_UpdateInstance)

/* func_0208f8d0 */
void TransitionMark_RewindInstance(void)
{
    TransitionMark_Rewind(&data_021d3654);
}
CLEAN_AS(func_0208f8d0, TransitionMark_RewindInstance)

/* func_0208f8e0 */
void TransitionMark_ResetInstance(void)
{
    TransitionMark_Reset(&data_021d3654);
}
CLEAN_AS(func_0208f8e0, TransitionMark_ResetInstance)

/* func_0208f8f0: not drawn (a scene's display is about to be set up). */
void TransitionMark_Suppress(void)
{
    transition_mark_set_suppressed(1);
}
CLEAN_AS(func_0208f8f0, TransitionMark_Suppress)

/* func_0208f8fc: after a scene's display set-up, while blinking, the OBJ window set up again,
 * with the OBJs inside it and BG2 outside the windows; drawn again. */
void TransitionMark_RestoreWithOutside(void)
{
    if (data_021d3654.state != TRANSITION_MARK_WAITING) {
        DisplayShadow_SetMainObjWindowPlanes(TRANSITION_MARK_PLANE_OBJ);
        DisplayShadow_SetMainOutsidePlanes(TRANSITION_MARK_PLANE_BG2);
        DisplayShadow_EnableMainWindows(TRANSITION_MARK_WINDOW_OBJ);
    }
    transition_mark_set_suppressed(0);
}
CLEAN_AS(func_0208f8fc, TransitionMark_RestoreWithOutside)

/* func_0208f930: after the scene change's display set-up, while blinking, the OBJ window set
 * up again with the OBJs inside it; drawn again. */
void TransitionMark_Restore(void)
{
    if (data_021d3654.state != TRANSITION_MARK_WAITING) {
        DisplayShadow_SetMainObjWindowPlanes(TRANSITION_MARK_PLANE_OBJ);
        DisplayShadow_EnableMainWindows(TRANSITION_MARK_WINDOW_OBJ);
    }
    transition_mark_set_suppressed(0);
}
CLEAN_AS(func_0208f930, TransitionMark_Restore)

/* func_0208f95c: a screen opened by transition `kind`: unless the running scene is the scene
 * change, the blinking lasts the kind's frames more (5, or 1 for kind 3).
 * REQUIRES: a scene process runs (the ROM reads its class without a check) and `kind` is 0-3. */
void TransitionMark_SetBlinkFrames(int kind)
{
    if (data_021f42f4->class_id == TRANSITION_MARK_SCENE_CHANGE_CLASS) {
        return;
    }
    data_021d3654.frames_left = data_020d0ba8[kind];
}
CLEAN_AS(func_0208f95c, TransitionMark_SetBlinkFrames)

/* func_0208f97c: a screen closed by transition `kind`: unless the running scene is the scene
 * change, and when the session is linked (asked every time), the blinking starts after the
 * kind's frames (8, or 1 for kind 3).
 * REQUIRES: a scene process runs (the ROM reads its class without a check) and `kind` is 0-3. */
void TransitionMark_SetDelay(int kind)
{
    u16 class_id = data_021f42f4->class_id;
    int linked = Session_IsLinked(data_020ccf94);
    if (class_id != TRANSITION_MARK_SCENE_CHANGE_CLASS && linked != 0) {
        data_021d3654.delay = data_020d0ba4[kind];
    }
}
CLEAN_AS(func_0208f97c, TransitionMark_SetDelay)

/* The member function table of TransitionMark_Update (a function-local static of the game):
 * its guard, the table, and the constants it is filled from. */
extern u32 data_021d3620;
extern MemberPointer data_021d3644[2];
extern const MemberPointer data_020e23cc, data_020e23bc;

/* func_0208f9b8 (vtable slot 3): the state's step, through the game's table (filled on the
 * first call).
 * REQUIRES: the state is 0 or 1 (the ROM indexes its table unchecked). */
void TransitionMark_Update(TransitionMark *mark)
{
    static const MemberPointer *const constants[2] = {
        &data_020e23cc, /* TransitionMark_StepWaiting */
        &data_020e23bc, /* TransitionMark_StepBlinking */
    };
    MemberTable_InitOnce(&data_021d3620, data_021d3644, constants, 2);
    MemberPointer_CallVoid(&data_021d3644[mark->state], mark);
}
CLEAN_AS(func_0208f9b8, TransitionMark_Update)

/* func_0208fa1c (vtable slot 2): while shown and not suppressed, the cell drawn on the main
 * screen at the place, as OBJs and as OBJ window. */
void TransitionMark_Draw(TransitionMark *mark)
{
    if (mark->shown == 0 || mark->suppressed != 0) {
        return;
    }
    int x = ScreenSprite_X(&mark->base);
    int y = ScreenSprite_Y(&mark->base);
    const OamEntry *cell = CellAnim_Cell(&mark->anim);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, cell, x, y, -1, -1, TRANSITION_MARK_FX_ONE, TRANSITION_MARK_FX_ONE, 0, -1, 0,
                       0);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, cell, x, y, -1, -1, TRANSITION_MARK_FX_ONE, TRANSITION_MARK_FX_ONE, 0,
                       TRANSITION_MARK_OBJ_MODE_WINDOW, 0, 0);
}
CLEAN_AS(func_0208fa1c, TransitionMark_Draw)

static void transition_mark_destruct(TransitionMark *mark)
{
    mark->base.vtable = data_020e2400;
    CellAnim_Destruct(&mark->anim);
    ScreenSprite_DestructBase(&mark->base);
}

/* func_0208fa9c (vtable slot 1): destructed and freed. */
TransitionMark *TransitionMark_Delete(TransitionMark *mark)
{
    transition_mark_destruct(mark);
    Heap_OperatorDeleteB(mark);
    return mark;
}
CLEAN_AS(func_0208fa9c, TransitionMark_Delete)

/* func_0208fac4 (vtable slot 0): the destructor. */
TransitionMark *TransitionMark_Destruct(TransitionMark *mark)
{
    transition_mark_destruct(mark);
    return mark;
}
CLEAN_AS(func_0208fac4, TransitionMark_Destruct)
