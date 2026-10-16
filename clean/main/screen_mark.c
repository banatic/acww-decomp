/* The screen indicators' last sprite (screen_mark.h). */
#include "screen_mark.h"

#include "cell_anim.h"
#include "clean.h"
#include "event_queue.h" /* EventQueue_HasCurrent */
#include "scene_query.h" /* SceneQuery_Current */

static_assert(offsetof(ScreenMark, anim) == 0x0c && offsetof(ScreenMark, state) == 0x20, "ScreenMark");
static_assert(sizeof(ScreenMark) == 0x24, "ScreenMark");

/* The object, its draw (vtable slot 2) and its update (vtable slot 3). */
extern ScreenMark data_021d35f8;
extern void func_0208eea0(ScreenMark *mark);
extern void func_0208ee20(ScreenMark *mark);

/* The animations of main's sprites: the mark appears with entry 2 and hides with 3. */
extern const CellAnimData data_020d5b3c[];
#define SCREEN_MARK_ANIM_APPEARING 2
#define SCREEN_MARK_ANIM_HIDING 3

/* POWCNT1's swap bit: 1 for the main engine on the top screen. */
extern int data_021c8c9c;

/* The scene number (func_020960d8(4)); the mark is not shown in scenes 8 to 15 and 0x24 to
 * 0x2c, nor while the scene query's current scene is 6. */
extern int func_020960d8(int which);
#define SCREEN_MARK_SCENE_WHICH 4
#define SCREEN_MARK_NO_SCENE_FIRST_1 8
#define SCREEN_MARK_NO_SCENE_COUNT_1 8
#define SCREEN_MARK_NO_SCENE_FIRST_2 0x24
#define SCREEN_MARK_NO_SCENE_COUNT_2 9
#define SCREEN_MARK_NO_QUERY_SCENE 6

static void screen_mark_set_anim(ScreenMark *mark, int entry)
{
    CellAnim_SetData(&mark->anim, &data_020d5b3c[entry]);
    CellAnim_SetHold(&mark->anim, 1);
    CellAnim_Restart(&mark->anim);
}

/* func_0208ecd0: whether the mark should show (each condition is asked every time). */
int ScreenMark_ShouldShow(void)
{
    int main_on_bottom = data_021c8c9c == 0;
    int no_event = EventQueue_HasCurrent() == 0;
    int query_scene = SceneQuery_Current() == SCREEN_MARK_NO_QUERY_SCENE;
    u32 scene = (u32) func_020960d8(SCREEN_MARK_SCENE_WHICH);
    int no_scene_1 = scene - SCREEN_MARK_NO_SCENE_FIRST_1 < SCREEN_MARK_NO_SCENE_COUNT_1;
    int no_scene_2 = scene - SCREEN_MARK_NO_SCENE_FIRST_2 < SCREEN_MARK_NO_SCENE_COUNT_2;

    return main_on_bottom && no_event && !query_scene && !no_scene_1 && !no_scene_2;
}
CLEAN_AS(func_0208ecd0, ScreenMark_ShouldShow)

/* func_0208ed40 (state 3): the animation advanced; hidden once it is done. */
void ScreenMark_StepHiding(ScreenMark *mark)
{
    CellAnim_Advance(&mark->anim);
    if (CellAnim_IsDone(&mark->anim) != 0) {
        mark->state = SCREEN_MARK_HIDDEN;
    }
}
CLEAN_AS(func_0208ed40, ScreenMark_StepHiding)

/* func_0208ed60 (state 2): hiding once the mark should no longer show. */
void ScreenMark_StepShown(ScreenMark *mark)
{
    if (ScreenMark_ShouldShow()) {
        return;
    }
    mark->state = SCREEN_MARK_HIDING;
    screen_mark_set_anim(mark, SCREEN_MARK_ANIM_HIDING);
}
CLEAN_AS(func_0208ed60, ScreenMark_StepShown)

/* func_0208ed98 (state 1): the animation advanced; shown once it is done. */
void ScreenMark_StepAppearing(ScreenMark *mark)
{
    CellAnim_Advance(&mark->anim);
    if (CellAnim_IsDone(&mark->anim) != 0) {
        mark->state = SCREEN_MARK_SHOWN;
    }
}
CLEAN_AS(func_0208ed98, ScreenMark_StepAppearing)

/* func_0208edb8 (state 0): appearing once the mark should show. */
void ScreenMark_StepHidden(ScreenMark *mark)
{
    if (ScreenMark_ShouldShow()) {
        mark->state = SCREEN_MARK_APPEARING;
        screen_mark_set_anim(mark, SCREEN_MARK_ANIM_APPEARING);
    }
}
CLEAN_AS(func_0208edb8, ScreenMark_StepHidden)

/* func_0208edf0: the mark drawn (the screen indicators' draw). */
void ScreenMark_DrawInstance(void)
{
    func_0208eea0(&data_021d35f8);
}
CLEAN_AS(func_0208edf0, ScreenMark_DrawInstance)

/* func_0208ee00: the mark updated (the screen indicators' execute). */
void ScreenMark_UpdateInstance(void)
{
    func_0208ee20(&data_021d35f8);
}
CLEAN_AS(func_0208ee00, ScreenMark_UpdateInstance)

/* func_0208ee10: nothing to rewind (the screen indicators' delete). */
void ScreenMark_RewindInstance(void) {}
CLEAN_AS(func_0208ee10, ScreenMark_RewindInstance)
