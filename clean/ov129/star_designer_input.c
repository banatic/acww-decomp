/* The pointer, the key cursor and the sub states of overlay 129's screen (star_designer.h):
 * the pen over the sky and the arrows, the free pointer and the cursor of the keys, the panel's
 * buttons and the question they ask. */
#include "star_designer.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/constellations.h"
#include "main/group_params.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"

/* The buttons and the pen: down, down or up since the frame before, and where (now, and where
 * it last went down). */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern u8 data_021f6c60;
extern u8 data_021f6c5c;

#define STAR_DESIGNER_KEY_A 0x0001
#define STAR_DESIGNER_KEY_B 0x0002
#define STAR_DESIGNER_KEY_START 0x0008
#define STAR_DESIGNER_KEY_RIGHT 0x0010
#define STAR_DESIGNER_KEY_LEFT 0x0020
#define STAR_DESIGNER_KEY_UP 0x0040
#define STAR_DESIGNER_KEY_DOWN 0x0080
#define STAR_DESIGNER_KEY_Y 0x0800

/* The sounds (SoundSys_PlaySe). */
#define STAR_DESIGNER_SE_DONE 0x87f   /* "done": the view glides to the constellation */
#define STAR_DESIGNER_SE_SAVED 0x27   /* "yes" to "done" */
#define STAR_DESIGNER_SE_LEFT 0x28    /* "yes" to "quit" */
#define STAR_DESIGNER_SE_NO_QUIT 0x29 /* "no" to "quit" */
#define STAR_DESIGNER_SE_CANCEL 0x2a  /* "no" to "done", and "quit" */

/* The free pointer's bounds; past them the view scrolls by its steps. */
#define STAR_DESIGNER_STEP 4
#define STAR_DESIGNER_LEFT 0x30
#define STAR_DESIGNER_RIGHT 0xd0
#define STAR_DESIGNER_TOP 0x1c
#define STAR_DESIGNER_BOTTOM 0xac

/* The key cursor's next place by the key latched, from each place: left, down, right, up. */
extern const u8 data_ov129_0229dae4[STAR_DESIGNER_CURSORS];
extern const u8 data_ov129_0229daec[STAR_DESIGNER_CURSORS];
extern const u8 data_ov129_0229daf4[STAR_DESIGNER_CURSORS];
extern const u8 data_ov129_0229dafc[STAR_DESIGNER_CURSORS];
/* The arrows' places, x and y. */
extern const u8 data_ov129_0229db40[];
extern const u8 data_ov129_0229db48[];

/* The constellation saved by "yes" to "done": a static object made once (guard bit 0 of
 * data_ov129_0229dcc0) and registered with its destructor (the game's function) in the record
 * at data_ov129_0229dccc. */
extern u32 data_ov129_0229dcc0;
extern u8 data_ov129_0229dccc[];
extern Constellation data_ov129_0229dcd8;
extern void __register_global_object(void *object, void *destruct, void *record);
extern Constellation *func_020b1a54(Constellation *constellation);

static MenuScene *star_designer_scene(StarDesigner *self)
{
    return &self->base;
}

static CellLayerSprite *star_designer_pointer_cells(StarDesigner *self)
{
    return (CellLayerSprite *) (void *) &self->pointer;
}

/* The pointer's update through its class (vtable slot 3). */
static void star_designer_update_pointer(StarDesigner *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->pointer.vtable;
    vtable[3](&self->pointer);
}

/* The pen touched the screen this frame. */
static int star_designer_touch_began(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

static int star_designer_done_enabled(StarDesigner *self)
{
    return ButtonPanel_HasSpriteFlag4(&self->panel, STAR_DESIGNER_BUTTON_DONE) == 0;
}

/* func_ov129_0229c2fc: the pointer's release played (STAR_DESIGNER_SUB_RELEASE, back to this
 * sub state after). */
void StarDesigner_ReleasePointer(StarDesigner *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_RELEASE);
}
CLEAN_AS(func_ov129_0229c2fc, StarDesigner_ReleasePointer)

/* func_ov129_0229c328: the pointer's press played (STAR_DESIGNER_SUB_PRESS). */
void StarDesigner_PressPointer(StarDesigner *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_PRESS);
}
CLEAN_AS(func_ov129_0229c328, StarDesigner_PressPointer)

/* func_ov129_0229c348: the pointer shows the first of its set of animations (at rest). */
void StarDesigner_ShowPointer(StarDesigner *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    star_designer_update_pointer(self);
}
CLEAN_AS(func_ov129_0229c348, StarDesigner_ShowPointer)

/* func_ov129_0229c368: the pointer eased to (x, y) in 3 steps while the sub state waits
 * (STAR_DESIGNER_SUB_GLIDE, back to this one after). */
void StarDesigner_GlidePointer(StarDesigner *self, int x, int y)
{
    Glider_EaseTo(&self->pointer, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_GLIDE);
}
CLEAN_AS(func_ov129_0229c368, StarDesigner_GlidePointer)

/* func_ov129_0229c39c: the pointer turned to its set for the cursor's place and glided there. */
void StarDesigner_GlideToCursor(StarDesigner *self)
{
    int x;
    int y;

    if (StarDesigner_IsPointerSetA(self) != 0) {
        Glider_TurnToSetA(&self->pointer);
    } else if (StarDesigner_IsPointerSetB(self) != 0) {
        Glider_TurnToSetB(&self->pointer);
    } else {
        Glider_TurnToSetC(&self->pointer);
    }
    x = StarDesigner_CursorX(self);
    y = StarDesigner_CursorY(self);
    StarDesigner_GlidePointer(self, x, y);
}
CLEAN_AS(func_ov129_0229c39c, StarDesigner_GlideToCursor)

/* func_ov129_0229c3f4: the pointer hidden (animation 0). */
void StarDesigner_HidePointer(StarDesigner *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    star_designer_update_pointer(self);
}
CLEAN_AS(func_ov129_0229c3f4, StarDesigner_HidePointer)

/* func_ov129_0229c418: the cursor's y: the free pointer's, a button's, or an arrow's from its
 * table.
 * REQUIRES: the cursor is below STAR_DESIGNER_CURSORS (the table is read at it). */
int StarDesigner_CursorY(StarDesigner *self)
{
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_FREE) != 0) {
        return self->y;
    }
    switch (self->cursor) {
        case STAR_DESIGNER_CURSOR_DONE:
            return ButtonPanel_ButtonY(&self->panel, STAR_DESIGNER_BUTTON_DONE);
        case STAR_DESIGNER_CURSOR_QUIT:
            return ButtonPanel_ButtonY(&self->panel, STAR_DESIGNER_BUTTON_QUIT);
        default:
            return data_ov129_0229db48[self->cursor];
    }
}
CLEAN_AS(func_ov129_0229c418, StarDesigner_CursorY)

/* func_ov129_0229c468: the cursor's x, as StarDesigner_CursorY. */
int StarDesigner_CursorX(StarDesigner *self)
{
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_FREE) != 0) {
        return self->x;
    }
    switch (self->cursor) {
        case STAR_DESIGNER_CURSOR_DONE:
            return ButtonPanel_ButtonX(&self->panel, STAR_DESIGNER_BUTTON_DONE);
        case STAR_DESIGNER_CURSOR_QUIT:
            return ButtonPanel_ButtonX(&self->panel, STAR_DESIGNER_BUTTON_QUIT);
        default:
            return data_ov129_0229db40[self->cursor];
    }
}
CLEAN_AS(func_ov129_0229c468, StarDesigner_CursorX)

/* func_ov129_0229c4b8: the pointer put at the cursor in its set for the cursor's place, at
 * rest. */
void StarDesigner_PlacePointer(StarDesigner *self)
{
    int x = StarDesigner_CursorX(self);
    int y = StarDesigner_CursorY(self);

    Glider_PlaceAt(&self->pointer, x, y);
    if (StarDesigner_IsPointerSetA(self) != 0) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    } else if (StarDesigner_IsPointerSetB(self) != 0) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_C);
    }
    StarDesigner_ShowPointer(self);
}
CLEAN_AS(func_ov129_0229c4b8, StarDesigner_PlacePointer)

/* func_ov129_0229c520: the pointer's set is B: the key cursor on "done". */
int StarDesigner_IsPointerSetB(StarDesigner *self)
{
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_FREE) != 0) {
        return 0;
    }
    return self->cursor == STAR_DESIGNER_CURSOR_DONE;
}
CLEAN_AS(func_ov129_0229c520, StarDesigner_IsPointerSetB)

/* func_ov129_0229c548: the pointer's set is A: the free pointer, or the key cursor anywhere
 * but on the top arrow (STAR_SCOPE_ARROW_DOWN) and "done". */
int StarDesigner_IsPointerSetA(StarDesigner *self)
{
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_FREE) != 0) {
        return 1;
    }
    if (self->cursor == STAR_SCOPE_ARROW_DOWN || self->cursor == STAR_DESIGNER_CURSOR_DONE) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov129_0229c548, StarDesigner_IsPointerSetA)

/* func_ov129_0229c574: the key cursor moved by the first of left, right, up and down latched,
 * through its tables. Returns whether it moved. (The source passes the keys as a pointer.)
 * REQUIRES: the cursor is below STAR_DESIGNER_CURSORS. */
int StarDesigner_MoveCursor(StarDesigner *self, u32 keys)
{
    u8 was = self->cursor;

    if (KeyRepeat_HasLeft((int) keys) != 0) {
        self->cursor = data_ov129_0229dae4[self->cursor];
    } else if (KeyRepeat_HasRight((int) keys) != 0) {
        self->cursor = data_ov129_0229daf4[self->cursor];
    } else if (KeyRepeat_HasUp((int) keys) != 0) {
        self->cursor = data_ov129_0229dafc[self->cursor];
    } else if (KeyRepeat_HasDown((int) keys) != 0) {
        self->cursor = data_ov129_0229daec[self->cursor];
    }
    return was != self->cursor;
}
CLEAN_AS(func_ov129_0229c574, StarDesigner_MoveCursor)

/* func_ov129_0229c610: the error message `message` shown (STAR_DESIGNER_SUB_ERROR), the pointer
 * out of the window. */
void StarDesigner_ShowError(StarDesigner *self, char message)
{
    u8 messages[1];

    messages[0] = (u8) message;
    ErrorMessage_Open(&self->error, messages, 1, 0);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_ERROR);
    CellLayerSprite_ClearWindow(star_designer_pointer_cells(self));
}
CLEAN_AS(func_ov129_0229c610, StarDesigner_ShowError)

/* func_ov129_0229c644: "no" (heard by the question): pressed, then back to the drawing
 * (STAR_DESIGNER_STATE_BACK_START). */
void StarDesigner_AnswerNo(StarDesigner *self)
{
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_QUITTING) != 0) {
        SoundSys_PlaySe(STAR_DESIGNER_SE_NO_QUIT);
    } else {
        SoundSys_PlaySe(STAR_DESIGNER_SE_CANCEL);
    }
    ButtonPanel_Select(&self->panel, STAR_DESIGNER_BUTTON_NO);
    MenuScene_SetState(star_designer_scene(self), STAR_DESIGNER_STATE_BACK_START);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_BUTTON);
}
CLEAN_AS(func_ov129_0229c644, StarDesigner_AnswerNo)

/* func_ov129_0229c684: "yes": pressed, then the screen closes (STAR_DESIGNER_STATE_CLOSE). To
 * "quit", GroupParams' byte 0xc4c is 0 and the leaving heard. To "done", it is 1 and the
 * constellation saved in the slot of GroupParams' argument (not new): the static
 * constellation, made the first time, cleared and given the player as its creator, then the
 * pieces and the name copied in. */
void StarDesigner_AnswerYes(StarDesigner *self)
{
    Constellation *saved = &data_ov129_0229dcd8;
    int number;

    ButtonPanel_Select(&self->panel, STAR_DESIGNER_BUTTON_YES);
    MenuScene_SetState(star_designer_scene(self), STAR_DESIGNER_STATE_CLOSE);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_BUTTON);
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_QUITTING) != 0) {
        GroupParams_SetC4C(0);
        SoundSys_PlaySe(STAR_DESIGNER_SE_LEFT);
        return;
    }
    GroupParams_SetC4C(1);
    number = GroupParams_Arg();
    if ((data_ov129_0229dcc0 & 1) == 0) {
        Constellations_ConstructOne((int) (uintptr_t) saved);
        __register_global_object(saved, (void *) (uintptr_t) func_020b1a54, data_ov129_0229dccc);
        data_ov129_0229dcc0 |= 1;
    }
    Constellations_Clear(saved);
    Constellations_SetCreator(&saved->creator);
    for (int i = 0; i < CONSTELLATIONS_PIECES; i++) {
        saved->pieces[i] = self->pieces[i];
    }
    for (int i = 0; i < CONSTELLATIONS_NAME_LENGTH; i++) {
        saved->name[i] = self->name[i];
    }
    Constellations_Put(saved, number, 0);
    SoundSys_PlaySe(STAR_DESIGNER_SE_SAVED);
}
CLEAN_AS(func_ov129_0229c684, StarDesigner_AnswerYes)

/* func_ov129_0229c758: "quit" pressed: the quit question asked next
 * (STAR_DESIGNER_STATE_ASK_START), the centre and the end mark no more drawn; heard. */
void StarDesigner_PressQuit(StarDesigner *self)
{
    StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_QUITTING);
    ButtonPanel_Select(&self->panel, STAR_DESIGNER_BUTTON_QUIT);
    MenuScene_SetState(star_designer_scene(self), STAR_DESIGNER_STATE_ASK_START);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_BUTTON);
    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_CENTRE);
    SoundSys_PlaySe(STAR_DESIGNER_SE_CANCEL);
    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_END_MARK);
}
CLEAN_AS(func_ov129_0229c758, StarDesigner_PressQuit)

/* func_ov129_0229c79c: "done" pressed: the done question asked next, the centre no more drawn,
 * the pieces painted without the open ones and the view glided to the constellation's centre
 * (in whole 4 pixels); heard, and the end mark no more drawn. */
void StarDesigner_PressDone(StarDesigner *self)
{
    int x;
    int y;

    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_QUITTING);
    ButtonPanel_Select(&self->panel, STAR_DESIGNER_BUTTON_DONE);
    MenuScene_SetState(star_designer_scene(self), STAR_DESIGNER_STATE_ASK_START);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_BUTTON);
    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_CENTRE);
    StarDesigner_Refresh(self, 0);
    Constellations_Center(self->pieces, &x, &y);
    x &= 0xfffc;
    y &= 0xfffc;
    StarScope_GlideTo(&self->scope, x, y);
    SoundSys_PlaySe(STAR_DESIGNER_SE_DONE);
    StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_END_MARK);
}
CLEAN_AS(func_ov129_0229c79c, StarDesigner_PressDone)

/* func_ov129_0229c820: back to the drawing with the end mark drawn, by the pen or the keys as
 * last used (state flag 2). */
void StarDesigner_EnterDrawing(StarDesigner *self)
{
    StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_END_MARK);
    if (StateFlags_IsClear2() != 0) {
        StarDesigner_EnterPen(self);
    } else {
        StarDesigner_EnterKeys(self);
    }
}
CLEAN_AS(func_ov129_0229c820, StarDesigner_EnterDrawing)

/* func_ov129_0229c848: on to the keys with the free pointer (STAR_DESIGNER_SUB_FREE), put at
 * its place, the usual key repeat. */
void StarDesigner_EnterKeys(StarDesigner *self)
{
    StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_FREE);
    StarDesigner_PlacePointer(self);
    MenuScene_ResetKeyRepeat(star_designer_scene(self));
    StarDesigner_Hover(self);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_FREE);
}
CLEAN_AS(func_ov129_0229c848, StarDesigner_EnterKeys)

/* func_ov129_0229c874: on to the pen: the pointer hidden, nothing pointed at
 * (STAR_DESIGNER_SUB_TOUCH). */
void StarDesigner_EnterPen(StarDesigner *self)
{
    StarDesigner_HidePointer(self);
    StarDesigner_Unhover(self);
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_TOUCH);
}
CLEAN_AS(func_ov129_0229c874, StarDesigner_EnterPen)

/* func_ov129_0229c890 (sub state 14): once the error message is closed, back to the drawing
 * with the pointer in the window again. */
void StarDesigner_SubError(StarDesigner *self)
{
    if (ErrorMessage_Update(&self->error, 0) != 0) {
        StarDesigner_EnterDrawing(self);
        CellLayerSprite_SetWindow(star_designer_pointer_cells(self));
    }
}
CLEAN_AS(func_ov129_0229c890, StarDesigner_SubError)

/* func_ov129_0229c8b8 (sub state 13): once the pointer's press has played, the answer chosen. */
void StarDesigner_SubAnswerPress(StarDesigner *self)
{
    if (CellLayerSprite_IsDone(star_designer_pointer_cells(self)) != 0) {
        if (self->answer != STAR_DESIGNER_ANSWER_YES) {
            StarDesigner_AnswerNo(self);
        } else {
            StarDesigner_AnswerYes(self);
        }
    }
}
CLEAN_AS(func_ov129_0229c8b8, StarDesigner_SubAnswerPress)

/* func_ov129_0229c8ec (sub state 12): the question by the keys. A touch goes on to the pen; A
 * presses the answer chosen (STAR_DESIGNER_SUB_ANSWER_PRESS); B answers "no" and START "yes";
 * left and right choose "yes" and "no", the pointer gliding to the button. */
void StarDesigner_SubAnswerKeys(StarDesigner *self)
{
    u16 pressed;
    u8 was;
    u32 keys;

    if (MenuScene_TakeTouch(star_designer_scene(self)) != 0) {
        StarDesigner_EnterAnswerPen(self);
        return;
    }
    pressed = data_021fbe40.pressed;
    if ((pressed & STAR_DESIGNER_KEY_A) != 0) {
        Glider_ShowSecondOfSet(&self->pointer);
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_ANSWER_PRESS);
        return;
    }
    if ((pressed & STAR_DESIGNER_KEY_B) != 0) {
        StarDesigner_HidePointer(self);
        StarDesigner_AnswerNo(self);
        return;
    }
    if ((pressed & STAR_DESIGNER_KEY_START) != 0) {
        StarDesigner_HidePointer(self);
        StarDesigner_AnswerYes(self);
        return;
    }
    was = self->answer;
    keys = MenuScene_LatchRepeatedKeys(star_designer_scene(self));
    if (KeyRepeat_HasLeft((int) keys) != 0) {
        if (self->answer != STAR_DESIGNER_ANSWER_YES) {
            self->answer--;
        }
    } else if (KeyRepeat_HasRight((int) keys) != 0) {
        if (self->answer < STAR_DESIGNER_ANSWER_NO) {
            self->answer++;
        }
    }
    if (was != self->answer) {
        int button = self->answer != STAR_DESIGNER_ANSWER_YES ? STAR_DESIGNER_BUTTON_NO : STAR_DESIGNER_BUTTON_YES;
        int x = ButtonPanel_ButtonX(&self->panel, button);
        int y = ButtonPanel_ButtonY(&self->panel, button);
        StarDesigner_GlidePointer(self, x, y);
    }
}
CLEAN_AS(func_ov129_0229c8ec, StarDesigner_SubAnswerKeys)

/* func_ov129_0229ca04 (sub state 11): the question by the pen. A button goes on to the keys; a
 * touch of "yes" or "no" answers. */
void StarDesigner_SubAnswerPen(StarDesigner *self)
{
    if (MenuScene_TakeButtons(star_designer_scene(self), 1) != 0) {
        StarDesigner_EnterAnswerKeys(self);
        return;
    }
    if (star_designer_touch_began()) {
        if (ButtonPanel_IsTouched(&self->panel, STAR_DESIGNER_BUTTON_YES) != 0) {
            StarDesigner_AnswerYes(self);
            return;
        }
        if (ButtonPanel_IsTouched(&self->panel, STAR_DESIGNER_BUTTON_NO) != 0) {
            StarDesigner_AnswerNo(self);
            return;
        }
    }
}
CLEAN_AS(func_ov129_0229ca04, StarDesigner_SubAnswerPen)

/* func_ov129_0229ca70 (sub state 10): a button of the panel pressed. While its press plays, a
 * shown pointer follows the button down; at its end the pointer is hidden and the states run
 * again (phase 1). */
void StarDesigner_SubButton(StarDesigner *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(star_designer_pointer_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->pointer, frame + x, frame + y);
        }
    } else {
        StarDesigner_HidePointer(self);
        MenuScene_SetPhase(star_designer_scene(self), STAR_DESIGNER_PHASE_STATES);
    }
}
CLEAN_AS(func_ov129_0229ca70, StarDesigner_SubButton)

/* func_ov129_0229cadc (sub state 9): once the pointer's release has played, the pointer at rest
 * and back to the sub state it left. */
void StarDesigner_SubRelease(StarDesigner *self)
{
    if (CellLayerSprite_IsDone(star_designer_pointer_cells(self)) != 0) {
        StarDesigner_ShowPointer(self);
        MenuScene_SetSubState(star_designer_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov129_0229cadc, StarDesigner_SubRelease)

/* func_ov129_0229cb08 (sub state 8): once the pointer's press has played, what it pressed. The
 * free pointer touches the star under it (staying when the error message came up) and is
 * released back to the free pointer. The key cursor presses "done" when enabled (else is
 * released), "quit", or holds its arrow (STAR_DESIGNER_SUB_ARROW_KEY). */
void StarDesigner_SubPress(StarDesigner *self)
{
    if (CellLayerSprite_IsDone(star_designer_pointer_cells(self)) == 0) {
        return;
    }
    if (StarDesigner_TestFlags(self, STAR_DESIGNER_FLAG_FREE) != 0) {
        if (StarDesigner_FindUnderPointer(self, self->x, self->y) != 0) {
            if (StarDesigner_TouchStar(self) == STAR_DESIGNER_TOUCH_ERROR) {
                return;
            }
        }
        StarDesigner_Hover(self);
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_FREE);
        StarDesigner_ReleasePointer(self);
        return;
    }
    switch (self->cursor) {
        case STAR_DESIGNER_CURSOR_DONE:
            if (star_designer_done_enabled(self)) {
                StarDesigner_PressDone(self);
            } else {
                MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_CURSOR);
                StarDesigner_ReleasePointer(self);
            }
            break;
        case STAR_DESIGNER_CURSOR_QUIT:
            StarDesigner_PressQuit(self);
            break;
        case STAR_SCOPE_ARROW_LEFT:
        case STAR_SCOPE_ARROW_RIGHT:
        case STAR_SCOPE_ARROW_UP:
        case STAR_SCOPE_ARROW_DOWN:
            self->arrow = self->cursor;
            StarScope_HoldArrow(&self->scope, self->arrow, 0);
            MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_ARROW_KEY);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov129_0229cb08, StarDesigner_SubPress)

/* func_ov129_0229cbdc (sub state 7): once the pointer has stopped, back to the sub state it
 * left, which runs at once. */
void StarDesigner_SubGlide(StarDesigner *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(star_designer_scene(self), self->return_sub_state);
        StarDesigner_RunSubState(self);
    }
}
CLEAN_AS(func_ov129_0229cbdc, StarDesigner_SubGlide)

/* func_ov129_0229cc08 (sub state 6): the nudge after an arrow let go; at its end the pointer at
 * rest and back to the sub state saved (the key cursor's). The pointer is also put at rest once
 * its release has played. */
void StarDesigner_SubNudgeKey(StarDesigner *self)
{
    if (StarScope_StepNudge(&self->scope) != 0) {
        StarDesigner_ShowPointer(self);
        MenuScene_SetSubState(star_designer_scene(self), self->return_sub_state);
    }
    if (CellLayerSprite_IsDone(star_designer_pointer_cells(self)) != 0) {
        StarDesigner_ShowPointer(self);
    }
}
CLEAN_AS(func_ov129_0229cc08, StarDesigner_SubNudgeKey)

/* func_ov129_0229cc4c (sub state 5): the arrow held by A scrolls the view; when A is let go the
 * pointer is released and the view nudged on (STAR_DESIGNER_SUB_NUDGE_KEY, back to the key
 * cursor after). */
void StarDesigner_SubArrowKey(StarDesigner *self)
{
    if ((data_021fbe40.held & STAR_DESIGNER_KEY_A) == 0) {
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_CURSOR);
        StarDesigner_ReleasePointer(self);
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_NUDGE_KEY);
        StarScope_Nudge(&self->scope, self->arrow);
    } else {
        StarScope_HoldArrow(&self->scope, self->arrow, 0);
    }
}
CLEAN_AS(func_ov129_0229cc4c, StarDesigner_SubArrowKey)

/* func_ov129_0229cc9c (sub state 4): the key cursor over the arrows and the buttons. A touch
 * goes on to the pen; A presses; Y goes on to the free pointer; START presses "done" when
 * enabled; B presses "quit"; the d-pad moves the cursor and the pointer glides to it. */
void StarDesigner_SubCursor(StarDesigner *self)
{
    u16 pressed;

    if (MenuScene_TakeTouch(star_designer_scene(self)) != 0) {
        StarDesigner_EnterPen(self);
        return;
    }
    pressed = data_021fbe40.pressed;
    if ((pressed & STAR_DESIGNER_KEY_A) != 0) {
        StarDesigner_PressPointer(self);
    } else if ((pressed & STAR_DESIGNER_KEY_Y) != 0) {
        StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_FREE);
        StarDesigner_Hover(self);
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_FREE);
        StarDesigner_GlideToCursor(self);
    } else if ((pressed & STAR_DESIGNER_KEY_START) != 0) {
        if (star_designer_done_enabled(self)) {
            StarDesigner_HidePointer(self);
            StarDesigner_PressDone(self);
        }
    } else if ((pressed & STAR_DESIGNER_KEY_B) != 0) {
        StarDesigner_HidePointer(self);
        StarDesigner_PressQuit(self);
    } else if (StarDesigner_MoveCursor(self, MenuScene_LatchRepeatedKeys(star_designer_scene(self))) != 0) {
        StarDesigner_GlideToCursor(self);
    }
}
CLEAN_AS(func_ov129_0229cc9c, StarDesigner_SubCursor)

/* func_ov129_0229cd54 (sub state 3): the free pointer. A touch goes on to the pen; A presses;
 * Y goes back to the key cursor; START presses "done" when enabled and B "quit" (the cursor put
 * on the button). The d-pad held moves the pointer 4 pixels a frame; past its bounds it stays
 * and the view scrolls instead (STAR_DESIGNER_FLAG_SCROLLED when it did); then the piece
 * pointed at is painted and the pointer put at its place. */
void StarDesigner_SubFree(StarDesigner *self)
{
    u16 pressed;
    u16 held;
    s32 was_x;
    s32 was_y;

    if (MenuScene_TakeTouch(star_designer_scene(self)) != 0) {
        StarDesigner_EnterPen(self);
        return;
    }
    pressed = data_021fbe40.pressed;
    if ((pressed & STAR_DESIGNER_KEY_A) != 0) {
        StarDesigner_PressPointer(self);
        return;
    }
    if ((pressed & STAR_DESIGNER_KEY_Y) != 0) {
        StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_FREE);
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_CURSOR);
        StarDesigner_GlideToCursor(self);
        StarDesigner_Unhover(self);
        return;
    }
    if ((pressed & STAR_DESIGNER_KEY_START) != 0) {
        if (!star_designer_done_enabled(self)) {
            return;
        }
        StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_FREE);
        self->cursor = STAR_DESIGNER_CURSOR_DONE;
        StarDesigner_Unhover(self);
        StarDesigner_HidePointer(self);
        StarDesigner_PressDone(self);
        return;
    }
    if ((pressed & STAR_DESIGNER_KEY_B) != 0) {
        StarDesigner_ClearFlags(self, STAR_DESIGNER_FLAG_FREE);
        self->cursor = STAR_DESIGNER_CURSOR_QUIT;
        StarDesigner_Unhover(self);
        StarDesigner_HidePointer(self);
        StarDesigner_PressQuit(self);
        return;
    }

    was_x = self->x;
    was_y = self->y;
    held = data_021fbe40.held;
    if ((held & STAR_DESIGNER_KEY_LEFT) != 0) {
        self->x -= STAR_DESIGNER_STEP;
    } else if ((held & STAR_DESIGNER_KEY_RIGHT) != 0) {
        self->x += STAR_DESIGNER_STEP;
    }
    held = data_021fbe40.held;
    if ((held & STAR_DESIGNER_KEY_UP) != 0) {
        self->y -= STAR_DESIGNER_STEP;
    } else if ((held & STAR_DESIGNER_KEY_DOWN) != 0) {
        self->y += STAR_DESIGNER_STEP;
    }
    if (was_x == self->x && was_y == self->y) {
        return;
    }
    if (self->x < STAR_DESIGNER_LEFT) {
        self->x = STAR_DESIGNER_LEFT;
        StarScope_ScrollHorizontally(&self->scope, -STAR_DESIGNER_STEP);
        StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_SCROLLED);
    } else if (self->x > STAR_DESIGNER_RIGHT) {
        self->x = STAR_DESIGNER_RIGHT;
        StarScope_ScrollHorizontally(&self->scope, STAR_DESIGNER_STEP);
        StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_SCROLLED);
    }
    if (self->y < STAR_DESIGNER_TOP) {
        self->y = STAR_DESIGNER_TOP;
        if (StarScope_ScrollVertically(&self->scope, -STAR_DESIGNER_STEP, 0) != 0) {
            StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_SCROLLED);
        }
    } else if (self->y > STAR_DESIGNER_BOTTOM) {
        self->y = STAR_DESIGNER_BOTTOM;
        if (StarScope_ScrollVertically(&self->scope, STAR_DESIGNER_STEP, 0) != 0) {
            StarDesigner_SetFlags(self, STAR_DESIGNER_FLAG_SCROLLED);
        }
    }
    StarDesigner_Hover(self);
    Glider_PlaceAt(&self->pointer, self->x, self->y);
}
CLEAN_AS(func_ov129_0229cd54, StarDesigner_SubFree)

/* func_ov129_0229cf5c (sub state 2): the nudge after an arrow let go by the pen; at its end an
 * arrow under the pen (where it last went down) is held again, else back to the pen. */
void StarDesigner_SubNudgePen(StarDesigner *self)
{
    if (StarScope_StepNudge(&self->scope) == 0) {
        return;
    }
    if (data_021fbdd8 != 0) {
        self->arrow = (u8) StarScope_ArrowAt(&self->scope, data_021f6c60, data_021f6c5c);
        if (self->arrow != STAR_SCOPE_ARROWS) {
            StarScope_HoldArrow(&self->scope, self->arrow, 0);
            MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_ARROW_PEN);
            return;
        }
    }
    MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_TOUCH);
}
CLEAN_AS(func_ov129_0229cf5c, StarDesigner_SubNudgePen)

/* func_ov129_0229cfc8 (sub state 1): the arrow held by the pen scrolls the view; when the pen
 * is up the view is nudged on (STAR_DESIGNER_SUB_NUDGE_PEN). */
void StarDesigner_SubArrowPen(StarDesigner *self)
{
    if (data_021fbdd8 == 0) {
        StarScope_Nudge(&self->scope, self->arrow);
        MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_NUDGE_PEN);
    } else {
        StarScope_HoldArrow(&self->scope, self->arrow, 0);
    }
}
CLEAN_AS(func_ov129_0229cfc8, StarDesigner_SubArrowPen)

/* func_ov129_0229d008 (sub state 0): the pen. A button goes on to the keys. A touch holds an
 * arrow (STAR_DESIGNER_SUB_ARROW_PEN), presses "done" (when enabled) or "quit", or touches the
 * star under the pen, flashing the piece when one was drawn or taken off. The flashed piece is
 * painted back on leaving and counted down otherwise. */
void StarDesigner_SubTouch(StarDesigner *self)
{
    if (MenuScene_TakeButtons(star_designer_scene(self), 1) != 0) {
        StarDesigner_EnterKeys(self);
        StarDesigner_Unflash(self);
        return;
    }
    if (star_designer_touch_began()) {
        int x = data_021f6c58;
        int y = data_021f6c54;
        self->arrow = (u8) StarScope_ArrowAt(&self->scope, x, y);
        if (self->arrow != STAR_SCOPE_ARROWS) {
            StarScope_HoldArrow(&self->scope, self->arrow, 0);
            MenuScene_SetSubState(star_designer_scene(self), STAR_DESIGNER_SUB_ARROW_PEN);
            StarDesigner_Unflash(self);
            return;
        }
        if (star_designer_done_enabled(self) && ButtonPanel_IsTouched(&self->panel, STAR_DESIGNER_BUTTON_DONE) != 0) {
            StarDesigner_PressDone(self);
            StarDesigner_Unflash(self);
            return;
        }
        if (ButtonPanel_IsTouched(&self->panel, STAR_DESIGNER_BUTTON_QUIT) != 0) {
            StarDesigner_PressQuit(self);
            StarDesigner_Unflash(self);
            return;
        }
        if (StarDesigner_FindUnderPointer(self, x, y) != 0) {
            switch (StarDesigner_TouchStar(self)) {
                case STAR_DESIGNER_TOUCH_STAR:
                    return;
                case STAR_DESIGNER_TOUCH_PIECES:
                    StarDesigner_Flash(self);
                    return;
                case STAR_DESIGNER_TOUCH_ERROR:
                    return;
                default:
                    break;
            }
        }
    }
    StarDesigner_StepFlash(self);
}
CLEAN_AS(func_ov129_0229d008, StarDesigner_SubTouch)
