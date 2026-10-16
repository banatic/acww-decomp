/* The control-mode object and its icon (control_mode_icon.h). */
#include "control_mode_icon.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "event_queue.h" /* EventQueue_TestFlag1 */
#include "oam_buffer.h"  /* OamBuffer_DrawCell */

static_assert(offsetof(ControlModeIcon, mode) == 0x0c && offsetof(ControlModeIcon, anim) == 0x14, "ControlModeIcon");
static_assert(offsetof(ControlModeIcon, shown) == 0x28 && sizeof(ControlModeIcon) == 0x2c, "ControlModeIcon");

/* The object, and its vtable. */
extern ControlModeIcon data_021d369c;
extern const u32 data_020e246c[];

/* The animations of main's sprites by number, and the icons' numbers. */
extern const CellAnimData data_020d6fcc[];
#define CONTROL_MODE_ICON_ANIM_BUTTONS 0x43
#define CONTROL_MODE_ICON_ANIM_TOUCH 0x44

/* The last frame, as CellAnim_FrameX and CellAnim_FrameY take it. */
#define CONTROL_MODE_ICON_LAST_FRAME (-1)

#define CONTROL_MODE_ICON_FX_ONE 0x1000

/* func_0208fdc8: the icon of the mode set, held on its last frame, from its start: buttons for
 * mode 1, touch for any other but 0; nothing shown for mode 0. */
void ControlModeIcon_SetAnim(ControlModeIcon *icon)
{
    int mode = icon->mode;
    if (mode == CONTROL_MODE_ICON_NONE) {
        icon->shown = 0;
        return;
    }
    int entry = mode == CONTROL_MODE_ICON_BUTTONS ? CONTROL_MODE_ICON_ANIM_BUTTONS : CONTROL_MODE_ICON_ANIM_TOUCH;
    CellAnim_SetData(&icon->anim, &data_020d6fcc[entry]);
    CellAnim_SetHold(&icon->anim, 1);
    CellAnim_Restart(&icon->anim);
    icon->shown = 1;
}
CLEAN_AS(func_0208fdc8, ControlModeIcon_SetAnim)

/* func_0208fe14: does nothing. */
void ControlModeIcon_Rewind(ControlModeIcon *icon)
{
    (void) icon;
}
CLEAN_AS(func_0208fe14, ControlModeIcon_Rewind)

/* func_0208fe18: does nothing. */
void ControlModeIcon_Reset(ControlModeIcon *icon)
{
    (void) icon;
}
CLEAN_AS(func_0208fe18, ControlModeIcon_Reset)

/* func_0208fe1c: whether the icon is not drawn: while flag 1 of the event queue is set. */
int ControlModeIcon_IsHidden(ControlModeIcon *icon)
{
    (void) icon;
    return EventQueue_TestFlag1() != 0;
}
CLEAN_AS(func_0208fe1c, ControlModeIcon_IsHidden)

static void control_mode_icon_destruct(ControlModeIcon *icon)
{
    icon->base.vtable = data_020e246c;
    CellAnim_Destruct(&icon->anim);
    ScreenSprite_DestructBase(&icon->base);
}

/* func_0208fe34 (vtable slot 1): destructed and freed. */
ControlModeIcon *ControlModeIcon_Delete(ControlModeIcon *icon)
{
    control_mode_icon_destruct(icon);
    Heap_OperatorDeleteB(icon);
    return icon;
}
CLEAN_AS(func_0208fe34, ControlModeIcon_Delete)

/* func_0208fe5c (vtable slot 0): the destructor. */
ControlModeIcon *ControlModeIcon_Destruct(ControlModeIcon *icon)
{
    control_mode_icon_destruct(icon);
    return icon;
}
CLEAN_AS(func_0208fe5c, ControlModeIcon_Destruct)

/* func_0208fe80: the constructor: mode 0, no icon. */
ControlModeIcon *ControlModeIcon_Construct(ControlModeIcon *icon)
{
    ScreenSprite_Construct(&icon->base);
    icon->base.vtable = data_020e246c;
    icon->mode = CONTROL_MODE_ICON_NONE;
    icon->shown_mode = CONTROL_MODE_ICON_NONE;
    CellAnim_Construct(&icon->anim);
    icon->shown = 0;
    return icon;
}
CLEAN_AS(func_0208fe80, ControlModeIcon_Construct)

/* func_0208feb0 (vtable slot 3): the icon animated, then set again when the mode changed. */
void ControlModeIcon_Update(ControlModeIcon *icon)
{
    if (icon->shown != 0) {
        CellAnim_Advance(&icon->anim);
    }
    if (icon->mode != icon->shown_mode) {
        ControlModeIcon_SetAnim(icon);
        icon->shown_mode = icon->mode;
    }
}
CLEAN_AS(func_0208feb0, ControlModeIcon_Update)

/* func_0208fedc (vtable slot 2): the icon's cell drawn on the other screen than the 3D one, at
 * the place plus its last frame's offset, unless it is hidden. */
void ControlModeIcon_Draw(ControlModeIcon *icon)
{
    if (icon->shown == 0 || ControlModeIcon_IsHidden(icon) != 0) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&icon->anim);
    int x = ScreenSprite_X(&icon->base);
    x += CellAnim_FrameX(&icon->anim, CONTROL_MODE_ICON_LAST_FRAME);
    int y = ScreenSprite_Y(&icon->base);
    y += CellAnim_FrameY(&icon->anim, CONTROL_MODE_ICON_LAST_FRAME);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_OTHER, cell, x, y, -1, -1, CONTROL_MODE_ICON_FX_ONE, CONTROL_MODE_ICON_FX_ONE, 0, -1,
                       0, 0);
}
CLEAN_AS(func_0208fedc, ControlModeIcon_Draw)

/* func_0208ff58 */
void ControlModeIcon_DrawInstance(void)
{
    ControlModeIcon_Draw(&data_021d369c);
}
CLEAN_AS(func_0208ff58, ControlModeIcon_DrawInstance)

/* func_0208ff68 */
void ControlModeIcon_UpdateInstance(void)
{
    ControlModeIcon_Update(&data_021d369c);
}
CLEAN_AS(func_0208ff68, ControlModeIcon_UpdateInstance)

/* func_0208ff78 */
void ControlModeIcon_RewindInstance(void)
{
    ControlModeIcon_Rewind(&data_021d369c);
}
CLEAN_AS(func_0208ff78, ControlModeIcon_RewindInstance)

/* func_0208ff88 */
void ControlModeIcon_ResetInstance(void)
{
    ControlModeIcon_Reset(&data_021d369c);
}
CLEAN_AS(func_0208ff88, ControlModeIcon_ResetInstance)

/* func_0208ff98: whether the mode is touch. */
int ControlModeIcon_IsTouch(void)
{
    return data_021d369c.mode == CONTROL_MODE_ICON_TOUCH;
}
CLEAN_AS(func_0208ff98, ControlModeIcon_IsTouch)

/* func_0208ffac: whether the mode is buttons. */
int ControlModeIcon_IsButtons(void)
{
    return data_021d369c.mode == CONTROL_MODE_ICON_BUTTONS;
}
CLEAN_AS(func_0208ffac, ControlModeIcon_IsButtons)

/* func_0208ffc0 */
void ControlModeIcon_SetTouch(void)
{
    data_021d369c.mode = CONTROL_MODE_ICON_TOUCH;
}
CLEAN_AS(func_0208ffc0, ControlModeIcon_SetTouch)

/* func_0208ffcc */
void ControlModeIcon_SetButtons(void)
{
    data_021d369c.mode = CONTROL_MODE_ICON_BUTTONS;
}
CLEAN_AS(func_0208ffcc, ControlModeIcon_SetButtons)

/* func_0208ffd8 */
void ControlModeIcon_SetNone(void)
{
    data_021d369c.mode = CONTROL_MODE_ICON_NONE;
}
CLEAN_AS(func_0208ffd8, ControlModeIcon_SetNone)
