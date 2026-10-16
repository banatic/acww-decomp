/* The catch panel, the second screen panel (catch_panel.h). */
#include "catch_panel.h"

#include "autoload_2/approach.h" /* Approach_EaseS32MinMax */
#include "cell_anim.h"
#include "clean.h"
#include "clock.h"          /* Clock_ReadRtcDateTime */
#include "date_time.h"      /* DateTime_Compare, DateTime_Subtract */
#include "event_queue.h"    /* EventQueue_HasCurrent */
#include "field_label.h"    /* FieldLabel_ShowNotice */
#include "number_text.h"    /* NumberText_Format */
#include "overlay_groups.h" /* OverlayGroups_HasOwner */
#include "quick_message.h"  /* QuickMessage_OwnBalloonBusy */
#include "scene_query.h"    /* SceneQuery_Current */
#include "sound.h"          /* SoundSys_PlaySe */
#include "state_flags.h"    /* StateFlags_Test4, StateFlags_ValueOrOne */
#include "text_draw.h"      /* TextDraw_AlignRight, TextDraw_Center, TextDraw_RequestDraw */

static_assert(sizeof(CatchPanelText) == 0x1c, "CatchPanelText");
static_assert(offsetof(CatchPanel, anim) == 0x0c && offsetof(CatchPanel, state) == 0x20, "CatchPanel");
static_assert(offsetof(CatchPanel, minutes_box) == 0x24 && offsetof(CatchPanel, insects_box) == 0x30, "CatchPanel");
static_assert(offsetof(CatchPanel, minutes_text) == 0x34 && offsetof(CatchPanel, insects_text) == 0x88, "CatchPanel");
static_assert(offsetof(CatchPanel, minutes_changed) == 0xa4 && offsetof(CatchPanel, in_room) == 0xa9, "CatchPanel");
static_assert(offsetof(CatchPanel, fish) == 0xac && offsetof(CatchPanel, end) == 0xb8, "CatchPanel");
static_assert(offsetof(CatchPanel, left) == 0xc0 && offsetof(CatchPanel, linger) == 0xc8, "CatchPanel");
static_assert(offsetof(CatchPanel, shift_wait) == 0xd8 && offsetof(CatchPanel, beep_tick) == 0xdc, "CatchPanel");
static_assert(sizeof(CatchPanel) == 0xe4, "CatchPanel");

/* The animations of main's sprites: the panel appears with entry 0x26 and hides with 0x27, in a
 * room with 0x2b and 0x2c. */
extern const CellAnimData data_020d5b3c[];
#define CATCH_PANEL_ANIM_APPEARING 0x26
#define CATCH_PANEL_ANIM_HIDING 0x27
#define CATCH_PANEL_ANIM_APPEARING_ROOM 0x2b
#define CATCH_PANEL_ANIM_HIDING_ROOM 0x2c

/* The fonts of the numbers: fontC for the time, fontD for the counts. */
extern TextFont data_021c82e8;
extern TextFont data_021c81d4;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u64 OS_GetTick(void);
/* Whether the countdown is stopped (its time limit is 0). */
extern unsigned int func_0208d12c(void *panel);

/* The ease of `shift`: 20 pixels higher while this system's balloon is out, eased by 0x600 of
 * the distance a frame, the step from 0x2300 up to `shift_speed`, which grows by 0xa00 a frame
 * from 0x2300 to 0x5000. A new target waits 10 frames, except the first after a reset and
 * one back to 0 while the panel should not show. */
#define CATCH_PANEL_SHIFT_BALLOON (-0x14000)
#define CATCH_PANEL_SHIFT_RATE 0x600
#define CATCH_PANEL_SHIFT_SPEED_ADD 0xa00
#define CATCH_PANEL_SHIFT_SPEED_MIN 0x2300
#define CATCH_PANEL_SHIFT_SPEED_MAX 0x5000
#define CATCH_PANEL_SHIFT_WAIT 10

#define CATCH_PANEL_FX_ONE 0x1000

/* The frames the panel stays once the countdown ended. */
#define CATCH_PANEL_LINGER 600
/* The seconds that beep, and the most milliseconds since the second before for a beep. */
#define CATCH_PANEL_BEEP_SECONDS 10
#define CATCH_PANEL_BEEP_GAP_MS 1100
/* The OS ticks (33.514 MHz / 64) in milliseconds: ticks * 64 / 33514. */
#define CATCH_PANEL_TICK_SHIFT 6
#define CATCH_PANEL_TICK_KHZ 0x82ea
/* The sounds of a beep and of the end, not played in scene 0x2e. */
#define CATCH_PANEL_SE_BEEP 0x64
#define CATCH_PANEL_SE_END 0x65
#define CATCH_PANEL_QUIET_SCENE 0x2e
/* The field label's notice of the end. */
#define CATCH_PANEL_NOTICE_END 3

/* The numbers: 2 digits padded with zeros, no unit, half-width characters. */
#define CATCH_PANEL_DIGITS 2
#define CATCH_PANEL_UNIT 0
#define CATCH_PANEL_HALF_WIDTH 1

/* The text boxes: their first VRAM tile (outdoors, in a room), size and colour, on OBJs of the
 * main screen. */
#define CATCH_PANEL_BOX_LAYER_OBJECTS 4
#define CATCH_PANEL_BOX_BACKGROUND 0
#define CATCH_PANEL_TIME_COLOR 0xc
#define CATCH_PANEL_COUNT_COLOR 5
#define CATCH_PANEL_TIME_CELLS 3
#define CATCH_PANEL_TIME_ROWS 2
#define CATCH_PANEL_COUNT_CELLS 2
#define CATCH_PANEL_COUNT_ROWS 1

/* The fields of DateTime_Compare. */
#define CATCH_PANEL_ALL_FIELDS 0x3f

/* A box from VRAM tile `tile`, set up for the text `text` in `font` and `color`; NULL when the
 * boxes' heap is full. */
static LabelBox *catch_panel_open_box(LabelBox **slot, CatchPanelText *text, int tile, int cells, int rows, u8 color,
                                      TextFont *font)
{
    *slot = LabelBox_NewInVram(tile, cells, rows);
    LabelBox *box = *slot;
    if (box == NULL) {
        return NULL;
    }
    box->base.layer = CATCH_PANEL_BOX_LAYER_OBJECTS;
    box->base.screens = TEXT_DRAW_TO_MAIN;
    box->base.rows_full_width = 1;
    box->base.background = CATCH_PANEL_BOX_BACKGROUND;
    box->base.color = color;
    box->base.font = font;
    int chars = ((int (*)(CatchPanelText *))(uintptr_t) text->vtable->buffer)(text);
    box->base.text = (const char *) (uintptr_t) chars;
    return box;
}

static void catch_panel_format(CatchPanelText *text, int value)
{
    NumberText_Format(text, value, CATCH_PANEL_DIGITS, NUMBER_TEXT_ZEROS, CATCH_PANEL_UNIT, CATCH_PANEL_HALF_WIDTH);
}

static void catch_panel_set_anim(CatchPanel *panel, int entry)
{
    CellAnim_SetData(&panel->anim, &data_020d5b3c[entry]);
    CellAnim_SetHold(&panel->anim, 1);
    CellAnim_Restart(&panel->anim);
}

/* func_0208c890 */
void CatchPanel_ResetShift(CatchPanel *panel)
{
    panel->shift = 0;
    panel->shift_target = 0;
    panel->shift_wait = -1;
    panel->shift_speed = 0;
}
CLEAN_AS(func_0208c890, CatchPanel_ResetShift)

/* func_0208c8ac: `shift` eased toward its target, 20 pixels higher while this system's quick
 * message balloon is out and the panel should show. Both are asked every frame. */
void CatchPanel_UpdateShift(CatchPanel *panel)
{
    int busy = QuickMessage_OwnBalloonBusy();
    u8 show = CatchPanel_ShouldShow(panel);
    int target = (busy != 0 && show != 0) ? CATCH_PANEL_SHIFT_BALLOON : 0;
    panel->shift_speed += CATCH_PANEL_SHIFT_SPEED_ADD;
    if (panel->shift_speed < CATCH_PANEL_SHIFT_SPEED_MIN) {
        panel->shift_speed = CATCH_PANEL_SHIFT_SPEED_MIN;
    } else if (panel->shift_speed > CATCH_PANEL_SHIFT_SPEED_MAX) {
        panel->shift_speed = CATCH_PANEL_SHIFT_SPEED_MAX;
    }
    if (target != panel->shift_target) {
        int waited;
        if (panel->shift_wait < 0 || show == 0) {
            waited = 1;
        } else {
            panel->shift_wait++;
            waited = panel->shift_wait > CATCH_PANEL_SHIFT_WAIT;
        }
        if (waited) {
            panel->shift_target = target;
            panel->shift_wait = 0;
        }
    } else {
        panel->shift_wait = 0;
    }
    Approach_EaseS32MinMax(&panel->shift, panel->shift_target, CATCH_PANEL_SHIFT_RATE, panel->shift_speed,
                           CATCH_PANEL_SHIFT_SPEED_MIN);
}
CLEAN_AS(func_0208c8ac, CatchPanel_UpdateShift)

/* func_0208c978: a frame of the countdown: `linger` counted down; while the countdown runs, the
 * time left read from the RTC (0 once the end is reached) and, when its seconds or minutes
 * changed, kept with their boxes marked for a redraw. In the last minute: at 0 the countdown
 * stops with the end sound and notice, and the panel lingers; at 1 to 10 seconds a beep, when
 * the second before was shown at most 1.1 seconds ago (by the OS tick, noted at every second of
 * the last minute but the end). */
void CatchPanel_UpdateTime(CatchPanel *panel)
{
    if (panel->linger > 0) {
        panel->linger--;
    }
    if (panel->time_limit == 0) {
        return;
    }
    DateTime left;
    MI_CpuCopy8(&panel->end, &left, sizeof(DateTime));
    DateTime now = {0};
    Clock_ReadRtcDateTime(&now);
    int seconds_changed;
    int minutes_changed;
    int compared = DateTime_Compare(&now, &left, CATCH_PANEL_ALL_FIELDS);
    if (compared == 0 || compared == 1) {
        left = (DateTime){0};
        seconds_changed = 1;
        minutes_changed = 1;
    } else {
        DateTime elapsed;
        MI_CpuCopy8(&now, &elapsed, sizeof(DateTime));
        DateTime_Subtract(&left, &elapsed);
        seconds_changed = DateTime_Compare(&panel->left, &left, DATE_TIME_SECOND) != 0;
        minutes_changed = DateTime_Compare(&panel->left, &left, DATE_TIME_MINUTE) != 0;
    }
    panel->seconds_changed = (panel->seconds_changed | seconds_changed) != 0;
    panel->minutes_changed = (panel->minutes_changed | minutes_changed) != 0;
    if (!seconds_changed && !minutes_changed) {
        return;
    }
    MI_CpuCopy8(&left, &panel->left, sizeof(DateTime));
    if (left.minute != 0) {
        return;
    }
    if (left.second == 0) {
        panel->linger = CATCH_PANEL_LINGER;
        panel->time_limit = 0;
        if (SceneQuery_Current() != CATCH_PANEL_QUIET_SCENE) {
            SoundSys_PlaySe(CATCH_PANEL_SE_END);
        }
        FieldLabel_ShowNotice(CATCH_PANEL_NOTICE_END);
        return;
    }
    u64 tick = OS_GetTick();
    if (left.second <= CATCH_PANEL_BEEP_SECONDS) {
        u64 last = (u64) panel->beep_tick[0] | (u64) panel->beep_tick[1] << 32;
        u64 ms = ((tick - last) << CATCH_PANEL_TICK_SHIFT) / CATCH_PANEL_TICK_KHZ;
        if (ms <= CATCH_PANEL_BEEP_GAP_MS && SceneQuery_Current() != CATCH_PANEL_QUIET_SCENE) {
            SoundSys_PlaySe(CATCH_PANEL_SE_BEEP);
        }
    }
    panel->beep_tick[0] = (u32) tick;
    panel->beep_tick[1] = (u32) (tick >> 32);
}
CLEAN_AS(func_0208c978, CatchPanel_UpdateTime)

/* func_0208cb28: the insects' number written and its box redrawn, centred, once it changed. */
void CatchPanel_RedrawInsects(CatchPanel *panel)
{
    if (panel->insects_changed == 0 || panel->insects_box == NULL) {
        return;
    }
    catch_panel_format(&panel->insects_text, panel->insects);
    TextDraw_Center(&panel->insects_box->base);
    TextDraw_RequestDraw(&panel->insects_box->base);
    panel->insects_changed = 0;
}
CLEAN_AS(func_0208cb28, CatchPanel_RedrawInsects)

/* func_0208cb70: the fish's number, the same way. */
void CatchPanel_RedrawFish(CatchPanel *panel)
{
    if (panel->fish_changed == 0 || panel->fish_box == NULL) {
        return;
    }
    catch_panel_format(&panel->fish_text, panel->fish);
    TextDraw_Center(&panel->fish_box->base);
    TextDraw_RequestDraw(&panel->fish_box->base);
    panel->fish_changed = 0;
}
CLEAN_AS(func_0208cb70, CatchPanel_RedrawFish)

/* func_0208cbb8: the seconds left written and their box redrawn (as laid out), once changed. */
void CatchPanel_RedrawSeconds(CatchPanel *panel)
{
    if (panel->seconds_changed == 0 || panel->seconds_box == NULL) {
        return;
    }
    catch_panel_format(&panel->seconds_text, panel->left.second);
    TextDraw_RequestDraw(&panel->seconds_box->base);
    panel->seconds_changed = 0;
}
CLEAN_AS(func_0208cbb8, CatchPanel_RedrawSeconds)

/* func_0208cbfc: the minutes left written and their box redrawn, right-aligned, once
 * changed. */
void CatchPanel_RedrawMinutes(CatchPanel *panel)
{
    if (panel->minutes_changed == 0 || panel->minutes_box == NULL) {
        return;
    }
    catch_panel_format(&panel->minutes_text, panel->left.minute);
    TextDraw_AlignRight(&panel->minutes_box->base);
    TextDraw_RequestDraw(&panel->minutes_box->base);
    panel->minutes_changed = 0;
}
CLEAN_AS(func_0208cbfc, CatchPanel_RedrawMinutes)

/* func_0208cc44 */
void CatchPanel_RedrawNumbers(CatchPanel *panel)
{
    CatchPanel_RedrawMinutes(panel);
    CatchPanel_RedrawSeconds(panel);
    CatchPanel_RedrawFish(panel);
    CatchPanel_RedrawInsects(panel);
}
CLEAN_AS(func_0208cc44, CatchPanel_RedrawNumbers)

static void catch_panel_free_box(LabelBox **box)
{
    if (*box != NULL) {
        LabelBox_Free(*box);
        *box = NULL;
    }
}

/* func_0208cc64 */
void CatchPanel_FreeTextBoxes(CatchPanel *panel)
{
    catch_panel_free_box(&panel->minutes_box);
    catch_panel_free_box(&panel->seconds_box);
    catch_panel_free_box(&panel->fish_box);
    catch_panel_free_box(&panel->insects_box);
}
CLEAN_AS(func_0208cc64, CatchPanel_FreeTextBoxes)

/* func_0208cca8: the insects' box made (from tile 0xaa, or 0x176 in a room), marked for a
 * draw.
 * QUIRK: the box is made even when there is one already; the old one is left in the boxes'
 * list. */
void CatchPanel_OpenInsectsBox(CatchPanel *panel)
{
    int tile = panel->in_room != 0 ? 0x176 : 0xaa;
    if (catch_panel_open_box(&panel->insects_box, &panel->insects_text, tile, CATCH_PANEL_COUNT_CELLS, CATCH_PANEL_COUNT_ROWS,
                             CATCH_PANEL_COUNT_COLOR, &data_021c81d4) != NULL) {
        panel->insects_changed = 1;
    }
}
CLEAN_AS(func_0208cca8, CatchPanel_OpenInsectsBox)

/* func_0208cd18: the fish's box (from tile 0xa8, or 0x174 in a room), the same way. */
void CatchPanel_OpenFishBox(CatchPanel *panel)
{
    int tile = panel->in_room != 0 ? 0x174 : 0xa8;
    if (catch_panel_open_box(&panel->fish_box, &panel->fish_text, tile, CATCH_PANEL_COUNT_CELLS, CATCH_PANEL_COUNT_ROWS,
                             CATCH_PANEL_COUNT_COLOR, &data_021c81d4) != NULL) {
        panel->fish_changed = 1;
    }
}
CLEAN_AS(func_0208cd18, CatchPanel_OpenFishBox)

/* func_0208cd88: the seconds' box (from tile 0x83, or 0x117 in a room), the same way. */
void CatchPanel_OpenSecondsBox(CatchPanel *panel)
{
    int tile = panel->in_room != 0 ? 0x117 : 0x83;
    if (catch_panel_open_box(&panel->seconds_box, &panel->seconds_text, tile, CATCH_PANEL_TIME_CELLS, CATCH_PANEL_TIME_ROWS,
                             CATCH_PANEL_TIME_COLOR, &data_021c82e8) != NULL) {
        panel->seconds_changed = 1;
    }
}
CLEAN_AS(func_0208cd88, CatchPanel_OpenSecondsBox)

/* func_0208cdf8: the minutes' box (from tile 0x80, or 0x114 in a room), the same way. */
void CatchPanel_OpenMinutesBox(CatchPanel *panel)
{
    int tile = panel->in_room != 0 ? 0x114 : 0x80;
    if (catch_panel_open_box(&panel->minutes_box, &panel->minutes_text, tile, CATCH_PANEL_TIME_CELLS, CATCH_PANEL_TIME_ROWS,
                             CATCH_PANEL_TIME_COLOR, &data_021c82e8) != NULL) {
        panel->minutes_changed = 1;
    }
}
CLEAN_AS(func_0208cdf8, CatchPanel_OpenMinutesBox)

/* func_0208ce68 */
void CatchPanel_OpenTextBoxes(CatchPanel *panel)
{
    CatchPanel_OpenMinutesBox(panel);
    CatchPanel_OpenSecondsBox(panel);
    CatchPanel_OpenFishBox(panel);
    CatchPanel_OpenInsectsBox(panel);
}
CLEAN_AS(func_0208ce68, CatchPanel_OpenTextBoxes)

/* func_0208ce88: whether the panel should show (the `shown` byte as it is, else 0): `shown`
 * set, and no event running, or one with an overlay group owner while state flag 4 is set and
 * its value at least 1.0. Without `shown`, or with an event and no owner, `linger` is
 * cleared. */
u8 CatchPanel_ShouldShow(CatchPanel *panel)
{
    u8 shown = panel->shown;
    if (shown == 0) {
        panel->linger = 0;
        return 0;
    }
    int event = EventQueue_HasCurrent();
    int owner = OverlayGroups_HasOwner();
    int no_owner = event != 0 && owner == 0;
    int covered = 0;
    if (event != 0 && owner != 0) {
        int flag = StateFlags_Test4();
        fx32 value = StateFlags_ValueOrOne();
        covered = flag == 0 || value < CATCH_PANEL_FX_ONE;
    }
    if (no_owner || covered) {
        if (no_owner) {
            panel->linger = 0;
        }
        return 0;
    }
    return shown;
}
CLEAN_AS(func_0208ce88, CatchPanel_ShouldShow)

/* func_0208cf00: once the hiding animation is done, the text boxes freed and hidden. */
void CatchPanel_StepHiding(CatchPanel *panel)
{
    CellAnim_Advance(&panel->anim);
    if (CellAnim_IsDone(&panel->anim) != 0) {
        CatchPanel_FreeTextBoxes(panel);
        CatchPanel_EnterHidden(panel);
    }
}
CLEAN_AS(func_0208cf00, CatchPanel_StepHiding)

/* func_0208cf28 */
void CatchPanel_EnterHiding(CatchPanel *panel)
{
    panel->state = CATCH_PANEL_HIDING;
    catch_panel_set_anim(panel, panel->in_room != 0 ? CATCH_PANEL_ANIM_HIDING_ROOM : CATCH_PANEL_ANIM_HIDING);
}
CLEAN_AS(func_0208cf28, CatchPanel_EnterHiding)

/* func_0208cf6c */
void CatchPanel_StepShown(CatchPanel *panel)
{
    if (CatchPanel_ShouldShow(panel) == 0) {
        CatchPanel_EnterHiding(panel);
    }
}
CLEAN_AS(func_0208cf6c, CatchPanel_StepShown)

/* func_0208cf84 */
void CatchPanel_EnterShown(CatchPanel *panel)
{
    panel->state = CATCH_PANEL_SHOWN;
}
CLEAN_AS(func_0208cf84, CatchPanel_EnterShown)

/* func_0208cf8c */
void CatchPanel_StepAppearing(CatchPanel *panel)
{
    CellAnim_Advance(&panel->anim);
    if (CellAnim_IsDone(&panel->anim) != 0) {
        CatchPanel_EnterShown(panel);
    }
}
CLEAN_AS(func_0208cf8c, CatchPanel_StepAppearing)

/* func_0208cfb0: the shift reset, the appearing animation started and the text boxes made. */
void CatchPanel_EnterAppearing(CatchPanel *panel)
{
    panel->state = CATCH_PANEL_APPEARING;
    CatchPanel_ResetShift(panel);
    catch_panel_set_anim(panel, panel->in_room != 0 ? CATCH_PANEL_ANIM_APPEARING_ROOM : CATCH_PANEL_ANIM_APPEARING);
    CatchPanel_OpenTextBoxes(panel);
}
CLEAN_AS(func_0208cfb0, CatchPanel_EnterAppearing)

/* func_0208cffc */
void CatchPanel_StepHidden(CatchPanel *panel)
{
    if (CatchPanel_ShouldShow(panel) != 0) {
        CatchPanel_EnterAppearing(panel);
    }
}
CLEAN_AS(func_0208cffc, CatchPanel_StepHidden)

/* func_0208d014 */
void CatchPanel_EnterHidden(CatchPanel *panel)
{
    panel->state = CATCH_PANEL_HIDDEN;
}
CLEAN_AS(func_0208d014, CatchPanel_EnterHidden)

/* func_0208d01c: nothing to show: the countdown stopped and the lingering over. */
int CatchPanel_IsIdle(CatchPanel *panel)
{
    return func_0208d12c(panel) != 0 && panel->linger <= 0;
}
CLEAN_AS(func_0208d01c, CatchPanel_IsIdle)

/* func_0208d03c */
int CatchPanel_IsHidden(CatchPanel *panel)
{
    return panel->state == CATCH_PANEL_HIDDEN;
}
CLEAN_AS(func_0208d03c, CatchPanel_IsHidden)
