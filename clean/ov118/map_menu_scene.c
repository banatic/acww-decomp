/* The town map of the menu (map_menu.h): its constructor and destructors, the loading of its
 * files and of the map, its states, the frame's start and end, its draw and the vtable's
 * slots. */
#include "map_menu.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/message_reader.h"
#include "main/oam_buffer.h"
#include "main/player_actor_ops.h"
#include "main/rom_file.h"
#include "main/scene_place.h"
#include "main/scene_tables.h"
#include "main/screen_map.h"
#include "main/state_flags.h"
#include "main/town_name.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"

/* The menu's vtable. */
extern const u8 data_ov118_0229cc08[];

/* The files: the OBJs' palettes and characters, the layers' palettes, characters and screens. */
extern const char data_ov118_0229cc68[]; /* "menu/map/b_map_obj.bpl" */
extern const char data_ov118_0229cc80[]; /* "menu/map/b_map_obj_0.bch" */
extern const char data_ov118_0229cc9c[]; /* "menu/map/b_map_obj_1.bch" */
extern const char data_ov118_0229ccb8[]; /* "menu/map/b_map_bg.bpl" */
extern const char data_ov118_0229ccd0[]; /* "menu/map/b_map_bg_0.bch" */
extern const char data_ov118_0229cce8[]; /* "menu/map/b_map_bg_1.bch" */
extern const char data_ov118_0229cd00[]; /* "menu/map/b_map_a_bg.bsc" */
extern const char data_ov118_0229cd18[]; /* "menu/map/b_map_b_bg.bsc" */

/* The cells drawn at the screen's centre: the frame's OBJs, and the two list buttons. */
extern const OamEntry data_ov118_0229cbb0[];
extern const OamEntry data_ov118_0229cb70[]; /* the residents' button */
extern const OamEntry data_ov118_0229cb90[]; /* the places' button */

/* The heap the files are read with. */
extern Heap *data_021fbe94;
/* The pad (autoload_2/input.h). */
extern PadState data_021fbe40;
/* Set when the player is in a room. */
extern u8 data_020e54a8;
/* The town's name (main/town_name.h), in the state block. */
extern TownName data_021dc7aa;
/* The place the player came into the room by (main/scene_place.h). */
extern ScenePlace data_021f69b8;

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov118_0229cd40; /* the sub states' guard */
extern u32 data_ov118_0229cd44; /* the states' guard */
extern MemberPointer data_ov118_0229cd48[MAP_MENU_STATES];
extern MemberPointer data_ov118_0229cd90[MAP_MENU_SUB_STATES];
extern const MemberPointer data_ov118_0229cb10; /* MapMenu_SubTouch */
extern const MemberPointer data_ov118_0229cb18; /* MapMenu_SubDragKnob */
extern const MemberPointer data_ov118_0229caf8; /* MapMenu_SubTrack */
extern const MemberPointer data_ov118_0229cb68; /* MapMenu_SubKeys */
extern const MemberPointer data_ov118_0229cae8; /* MapMenu_SubGlide */
extern const MemberPointer data_ov118_0229cac8; /* MapMenu_SubPress */
extern const MemberPointer data_ov118_0229cad0; /* MapMenu_SubRelease */
extern const MemberPointer data_ov118_0229cb00; /* MapMenu_SubKnobPress */
extern const MemberPointer data_ov118_0229cb08; /* MapMenu_SubKnobHeld */
extern const MemberPointer data_ov118_0229cb20; /* MapMenu_SubKnobRelease */
extern const MemberPointer data_ov118_0229caf0; /* MapMenu_SubPointer */
extern const MemberPointer data_ov118_0229cb60; /* MapMenu_StateLoad */
extern const MemberPointer data_ov118_0229cb58; /* MapMenu_StateMapStart */
extern const MemberPointer data_ov118_0229cb50; /* MapMenu_StateMapMiddle */
extern const MemberPointer data_ov118_0229cb48; /* MapMenu_StateMapEnd */
extern const MemberPointer data_ov118_0229cae0; /* MapMenu_StateList */
extern const MemberPointer data_ov118_0229cb38; /* MapMenu_StateShow */
extern const MemberPointer data_ov118_0229cb30; /* MapMenu_StateWipeIn */
extern const MemberPointer data_ov118_0229cb28; /* MapMenu_StateLeave */
extern const MemberPointer data_ov118_0229cad8; /* MapMenu_StateWipeOut */

/* The arrays' element functions handed to the C++ runtime: the game's symbols. */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void func_02070c08(void *label); /* TextLabel_Construct */
extern void func_02070be8(void *label); /* TextLabel_Destruct */
extern void func_ov118_0229a43c(void *mark);
extern void func_ov118_0229a438(void *mark);

/* The player's actor whose place the map shows outdoors. */
#define MAP_MENU_PLAYER_ACTOR 4

/* The layers (main/display_layers.h): the map and the list, on the sub screen, and the sub
 * screen's OBJs. */
#define MAP_MENU_LAYER_MAP 4
#define MAP_MENU_LAYER_LIST 6
#define MAP_MENU_LAYER_OBJ 8

/* The list's layer is scrolled so that its first row is at y 0x50. */
#define MAP_MENU_LIST_TOP 0x50

/* The wipe: the layers it works on and its margin. */
#define MAP_MENU_WIPE_LAYERS 0x0a
#define MAP_MENU_WIPE_MARGIN 0x30

/* The town's name in a label of style 8 from tile 0x1ab: menu message 0xa9 with the name as
 * its part 0. */
#define MAP_MENU_TITLE_MESSAGE 0xa9

#define MAP_MENU_TAB_CLOSE 7
#define MAP_MENU_TAB_POCKETS 0
#define MAP_MENU_TAB_4 4
#define MAP_MENU_PAD_B 0x0002
#define MAP_MENU_PAD_SELECT 0x0004
#define MAP_MENU_PAD_X 0x0400
#define MAP_MENU_PAD_Y 0x0800

static MenuScene *map_menu_scene(MapMenu *self)
{
    return &self->base;
}

/* The knob, as main's sprite of two cell animations it is built on. */
static DualCellSprite *map_menu_knob_sprite(MapMenu *self)
{
    return (DualCellSprite *) (void *) &self->knob_button;
}

/* A member's virtual function `slot` (2: draw, 3: update). */
static void map_menu_call_slot(void *member, int slot)
{
    void (*const *vtable)(void *) = *(void (*const *const *)(void *)) member;
    vtable[slot](member);
}

static void map_menu_destroy_members(MapMenu *self)
{
    self->base.vtable = data_ov118_0229cc08;
    __cxa_vec_cleanup(self->marks, MAP_MENU_MARKS, sizeof(MapMenuMark), func_ov118_0229a438);
    __cxa_vec_cleanup(self->extra_marks, MAP_MENU_EXTRA_MARKS, sizeof(MapMenuMark), func_ov118_0229a438);
    TownMapMarkers_Destruct(self->spots);
    Glider0_Destroy(&self->cursor);
    PushButton_Destroy(&self->knob_button);
    __cxa_vec_cleanup(self->labels, MAP_MENU_ROWS, sizeof(TextLabel), func_02070be8);
    MenuScene_DestroyBase(map_menu_scene(self));
}

/* func_ov118_0229a340 (vtable slot 0x40): the members' destructors, last first (the layer tasks
 * have none), then the base's. */
MapMenu *MapMenu_Destroy(MapMenu *self)
{
    map_menu_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov118_0229a340, MapMenu_Destroy)

/* func_ov118_0229a3b8 (vtable slot 0x44) */
MapMenu *MapMenu_Delete(MapMenu *self)
{
    map_menu_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov118_0229a3b8, MapMenu_Delete)

/* func_ov118_0229bda4: the OBJs' palettes 6-14 and characters 0xc0-0xff and 0x180-0x1ff. */
void MapMenu_LoadObjFiles(void)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov118_0229cc68, heap, MAP_MENU_LAYER_OBJ, 6, 6, 0xe);
    DisplayLayer_LoadCharsFromFile(data_ov118_0229cc80, heap, MAP_MENU_LAYER_OBJ, 0xc0, 0xc0, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov118_0229cc9c, heap, MAP_MENU_LAYER_OBJ, 0x180, 0x180, 0x1ff);
}
CLEAN_AS(func_ov118_0229bda4, MapMenu_LoadObjFiles)

/* func_ov118_0229be04: the map finished: overlay 117's last step, its characters into
 * `map_chars` (then loaded as the map layer's characters 0x60-0x15f) and its spots into `spots`,
 * from which the marks are made. */
void MapMenu_FinishMap(MapMenu *self)
{
    TownMapImage_DrawRow(3);
    TownMapMarkers_Clear(self->spots);
    TownMapImage_Finish((int) (uintptr_t) self->map_chars, (int) (uintptr_t) self->spots);
    DisplayLayer_LoadChars((u32) (uintptr_t) self->map_chars, MAP_MENU_LAYER_MAP, 0x60, 0x60, 0x15f);
    MapMenu_FillMarks(self, self->spots);
}
CLEAN_AS(func_ov118_0229be04, MapMenu_FinishMap)

/* func_ov118_0229be54: overlay 117's map steps 1 and 2. */
void MapMenu_ContinueMap(void)
{
    TownMapImage_DrawRow(1);
    TownMapImage_DrawRow(2);
}
CLEAN_AS(func_ov118_0229be54, MapMenu_ContinueMap)

/* func_ov118_0229be6c: overlay 117's map started: its maker, step 0, and the two parts of the
 * other step. */
void MapMenu_StartMap(void)
{
    TownMapImage_Create();
    TownMapImage_DrawRow(0);
    TownMapImage_Mark(TOWN_MAP_MARK_VILLAGERS);
    TownMapImage_Mark(TOWN_MAP_MARK_OTHERS);
}
CLEAN_AS(func_ov118_0229be6c, MapMenu_StartMap)

/* func_ov118_0229be8c: the map layer's palettes 1-15 and characters 0x11-0x5f and 0x230-0x25f;
 * its screen read and loaded; the list's template read, its first row in palette 4. */
void MapMenu_LoadBgFiles(MapMenu *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov118_0229ccb8, heap, MAP_MENU_LAYER_MAP, 1, 1, 0xf);
    DisplayLayer_LoadCharsFromFile(data_ov118_0229ccd0, heap, MAP_MENU_LAYER_MAP, 0x11, 0x11, 0x5f);
    DisplayLayer_LoadCharsFromFile(data_ov118_0229cce8, heap, MAP_MENU_LAYER_MAP, 0x230, 0x230, 0x25f);
    RomFile_Read(data_ov118_0229cd00, self->map_screen, MAP_MENU_SCREEN_BYTES);
    DisplayLayer_LoadScreen(self->map_screen, MAP_MENU_LAYER_MAP, MAP_MENU_SCREEN_BYTES, 0);
    RomFile_Read(data_ov118_0229cd18, self->rows_template, MAP_MENU_SCREEN_BYTES);
    ScreenMap_SetPalette(self->rows_template, 0x13, 0, 0x1c, 1, 4);
}
CLEAN_AS(func_ov118_0229be8c, MapMenu_LoadBgFiles)

/* func_ov118_0229bf3c: both layers at priority 2, with the first size and 16 colours. */
void MapMenu_SetUpLayers(void)
{
    DisplayLayer_SetPriority(MAP_MENU_LAYER_MAP, 2);
    DisplayLayer_SetPriority(MAP_MENU_LAYER_LIST, 2);
    DisplayLayer_SetBgControl(MAP_MENU_LAYER_MAP, 0, 0, 0);
    DisplayLayer_SetBgControl(MAP_MENU_LAYER_LIST, 0, 0, 0);
}
CLEAN_AS(func_ov118_0229bf3c, MapMenu_SetUpLayers)

/* func_ov118_0229bf70 */
void MapMenu_EndInteractiveFrame(MapMenu *self)
{
    MapMenu_EndFrame(self);
}
CLEAN_AS(func_ov118_0229bf70, MapMenu_EndInteractiveFrame)

/* func_ov118_0229bf78: the frame's start, the knob and the cursor updated. */
void MapMenu_BeginInteractiveFrame(MapMenu *self)
{
    MapMenu_BeginFrame(self);
    map_menu_call_slot(&self->knob_button, 3);
    map_menu_call_slot(&self->cursor, 3);
}
CLEAN_AS(func_ov118_0229bf78, MapMenu_BeginInteractiveFrame)

/* func_ov118_0229bfa4: the frame's end: a scroll under way steps (the list's layer follows, the
 * shown rows are made again when its first row changed); the blink steps; the shown rows made
 * when asked; the map's screen and the shown rows loaded when asked, once their tasks are
 * queued. */
void MapMenu_EndFrame(MapMenu *self)
{
    if (MapMenu_IsScrolling(self)) {
        MapMenu_StepScroll(self);
        DisplayLayer_SetScroll(MAP_MENU_LAYER_LIST, 0, self->scroll - MAP_MENU_LIST_TOP);
        if (self->shown_top != self->scroll >> 4) {
            MapMenu_SetFlags(self, MAP_MENU_FLAG_ROWS_DIRTY);
        }
    }
    MapMenu_StepBlink(self);
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_ROWS_DIRTY) != 0) {
        MapMenu_BuildShownRows(self);
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_ROWS_DIRTY);
    }
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_MAP_UPLOAD) != 0) {
        if (LayerTask_QueueScreen(&self->map_task, (int) (uintptr_t) self->map_screen, MAP_MENU_LAYER_MAP,
                                  MAP_MENU_SCREEN_BYTES, 0) != 0) {
            MapMenu_ClearFlags(self, MAP_MENU_FLAG_MAP_UPLOAD);
        }
    }
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_ROWS_UPLOAD) != 0) {
        if (LayerTask_QueueScreen(&self->rows_task, (int) (uintptr_t) self->shown_rows, MAP_MENU_LAYER_LIST,
                                  MAP_MENU_SCREEN_BYTES, 0) != 0) {
            MapMenu_ClearFlags(self, MAP_MENU_FLAG_ROWS_UPLOAD);
        }
    }
}
CLEAN_AS(func_ov118_0229bfa4, MapMenu_EndFrame)

/* func_ov118_0229c070: the frame's start: every label's box closed. */
void MapMenu_BeginFrame(MapMenu *self)
{
    MapMenu_ResetLabels(self);
}
CLEAN_AS(func_ov118_0229c070, MapMenu_BeginFrame)

/* func_ov118_0229c078: the members' end: the labels' boxes closed, both layer tasks ended. */
void MapMenu_EndMembers(MapMenu *self)
{
    MapMenu_ResetLabels(self);
    LayerTask_End(&self->rows_task);
    LayerTask_End(&self->map_task);
}
CLEAN_AS(func_ov118_0229c078, MapMenu_EndMembers)

/* func_ov118_0229c098: the menu's setup: no label, flag, scroll or blink; the focus on the
 * residents' button, the free pointer at (0x58, 0x70) over no mark, nothing selected; the lists
 * made; the player's place on the map from where they stand (outdoors, actor 4's start; in a
 * room, the place they came in by): its tile, 8 left and 13 down; the knob at rest. While the
 * bar's menu is opening the setup takes a frame a state (MAP_MENU_FLAG_OPENING). */
void MapMenu_Setup(MapMenu *self)
{
    Vec3 position;

    self->labels_used = 0;
    self->flags = 0;
    self->scroll = 0;
    self->scroll_target = 0;
    self->knob = 0;
    self->wipe_y = 0;
    self->blink = 0;
    self->focus = MAP_MENU_FOCUS_RESIDENTS;
    self->pointer_x = 0x58;
    self->pointer_y = 0x70;
    self->pointed_mark = MAP_MENU_NO_MARK;
    MapMenu_Select(self, MAP_MENU_SELECT_NONE);
    MapMenu_BuildLists(self);
    if (data_020e54a8 == 0) {
        position = *PlayerActorOps_StartPosition(MAP_MENU_PLAYER_ACTOR);
    } else {
        SceneTables_EntryRecord();
        position = *(const Vec3 *) ScenePlace_Position(&data_021f69b8);
    }
    int tile_z = (position.z + 0x800) >> 12;
    int tile_x = (position.x + 0x800) >> 12;
    self->position_x = (u8) (tile_x - 8);
    self->position_y = (u8) (tile_z + 0xd);
    DualCellSprite_SetState(map_menu_knob_sprite(self), DUAL_CELL_SPRITE_STILL);
    if (MenuTabs_IsOpening((MenuTabs *) (void *) Process_GetParent((Process *) (void *) self)) != 0) {
        MapMenu_SetFlags(self, MAP_MENU_FLAG_OPENING);
    }
}
CLEAN_AS(func_ov118_0229c098, MapMenu_Setup)

/* Both layers placed by the wipe (the list's lowered to its scroll), and the wipe's y kept for
 * the OBJs. */
static void map_menu_follow_wipe(MapMenu *self)
{
    MenuScene_ScrollWipe(map_menu_scene(self), MAP_MENU_LAYER_MAP, 0, 0);
    MenuScene_ScrollWipe(map_menu_scene(self), MAP_MENU_LAYER_LIST, 0, MAP_MENU_LIST_TOP - self->scroll);
    self->wipe_y = MenuScene_WipeOffsetY(map_menu_scene(self));
}

/* func_ov118_0229c18c (state 8): the wipe out; when it is over both layers are hidden, nothing
 * is drawn and the menu asks to be deleted (phase 5). */
void MapMenu_StateWipeOut(MapMenu *self)
{
    if (MenuScene_StepWipe(map_menu_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(MAP_MENU_LAYER_MAP);
        DisplayLayer_HideAndResetScroll(MAP_MENU_LAYER_LIST);
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_DRAWN);
        MenuScene_SetPhase(map_menu_scene(self), MAP_MENU_PHASE_DELETE);
    } else {
        map_menu_follow_wipe(self);
    }
}
CLEAN_AS(func_ov118_0229c18c, MapMenu_StateWipeOut)

/* func_ov118_0229c1ec (state 7): the menu leaves: the cursor hidden, the wipe out started
 * (state 8). */
void MapMenu_StateLeave(MapMenu *self)
{
    MapMenu_HideCursor(self);
    MenuScene_StartWipeOnWindow2(map_menu_scene(self), MAP_MENU_WIPE_LAYERS, 0, 0, MAP_MENU_WIPE_MARGIN);
    MenuScene_ScrollWipe(map_menu_scene(self), MAP_MENU_LAYER_MAP, 0, 0);
    MenuScene_ScrollWipe(map_menu_scene(self), MAP_MENU_LAYER_LIST, 0, MAP_MENU_LIST_TOP - self->scroll);
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_WIPE_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(map_menu_scene(self));
}
CLEAN_AS(func_ov118_0229c1ec, MapMenu_StateLeave)

/* func_ov118_0229c240 (state 6): the wipe in; when it is over the menu is in use (phase 2), by
 * the pen or the keys as the last input was. */
void MapMenu_StateWipeIn(MapMenu *self)
{
    if (MenuScene_StepWipeBack(map_menu_scene(self), 0)) {
        MenuScene_SetPhase(map_menu_scene(self), MAP_MENU_PHASE_INTERACTIVE);
        if (StateFlags_IsClear2()) {
            MapMenu_EnterTouch(self);
        } else {
            MapMenu_EnterKeys(self);
        }
    }
    map_menu_follow_wipe(self);
}
CLEAN_AS(func_ov118_0229c240, MapMenu_StateWipeIn)

/* func_ov118_0229c2a0 (state 5): the OBJs' files loaded; the town's name shown in a label
 * (menu message 0xa9); the wipe in started with both layers shown; the OBJs drawn (state 6). */
void MapMenu_StateShow(MapMenu *self)
{
    TownNameText name;

    MapMenu_LoadObjFiles();
    TownNameText_Construct(&name);
    TownName_ToText(&data_021dc7aa, (TextBase *) (void *) &name);
    MessageReader_SetPart(0, (int) (uintptr_t) &name);
    TextLabel *label = MapMenu_NextLabel(self);
    TextLabel_OpenStyledBox2(label, 8, 0x1ab, 0x12, 0xf, 0, 0);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) MAP_MENU_TITLE_MESSAGE);
    TextLabel_Show(label, 1, 0);
    TownNameText_Destruct(&name);
    MenuScene_StartWipeCoveredOnWindow2(map_menu_scene(self), MAP_MENU_WIPE_LAYERS, 3, 0, MAP_MENU_WIPE_MARGIN);
    DisplayLayer_Show(MAP_MENU_LAYER_MAP);
    MenuScene_ScrollWipe(map_menu_scene(self), MAP_MENU_LAYER_MAP, 0, 0);
    DisplayLayer_Show(MAP_MENU_LAYER_LIST);
    MenuScene_ScrollWipe(map_menu_scene(self), MAP_MENU_LAYER_LIST, 0, MAP_MENU_LIST_TOP - self->scroll);
    MapMenu_SetFlags(self, MAP_MENU_FLAG_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(map_menu_scene(self));
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_WIPE_IN);
}
CLEAN_AS(func_ov118_0229c2a0, MapMenu_StateShow)

/* func_ov118_0229c35c (state 4): the residents' list shown (state 5). */
void MapMenu_StateList(MapMenu *self)
{
    MapMenu_ShowResidents(self);
    MapMenu_BuildShownRows(self);
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_SHOW);
}
CLEAN_AS(func_ov118_0229c35c, MapMenu_StateList)

/* func_ov118_0229c378 (state 3): the map finished (state 4; when not opening, state 4 at once
 * and the opening flag cleared). */
void MapMenu_StateMapEnd(MapMenu *self)
{
    MapMenu_FinishMap(self);
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_LIST);
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_OPENING) == 0) {
        MapMenu_StateList(self);
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_OPENING);
    }
}
CLEAN_AS(func_ov118_0229c378, MapMenu_StateMapEnd)

/* func_ov118_0229c3ac (state 2): the map's middle steps (state 3, at once when not opening). */
void MapMenu_StateMapMiddle(MapMenu *self)
{
    MapMenu_ContinueMap();
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_MAP_END);
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_OPENING) == 0) {
        MapMenu_StateMapEnd(self);
    }
}
CLEAN_AS(func_ov118_0229c3ac, MapMenu_StateMapMiddle)

/* func_ov118_0229c3d8 (state 1): the map started (state 2, at once when not opening). */
void MapMenu_StateMapStart(MapMenu *self)
{
    MapMenu_StartMap();
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_MAP_MIDDLE);
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_OPENING) == 0) {
        MapMenu_StateMapMiddle(self);
    }
}
CLEAN_AS(func_ov118_0229c3d8, MapMenu_StateMapStart)

/* func_ov118_0229c404 (state 0): the layers set up and their files loaded (state 1, at once
 * when not opening). */
void MapMenu_StateLoad(MapMenu *self)
{
    MapMenu_SetUpLayers();
    MapMenu_LoadBgFiles(self);
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_MAP_START);
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_OPENING) == 0) {
        MapMenu_StateMapStart(self);
    }
}
CLEAN_AS(func_ov118_0229c404, MapMenu_StateLoad)

/* func_ov118_0229c478: the bar's tabs, each frame in use (after the menu close's delay is
 * counted): a menu close asked for switches to the close tab; else, in sub states 0, 3 and 10,
 * the tab touched on the bar, or by the keys X or B the close tab, Y the pockets, SELECT tab 4.
 * Answers whether the menu switched. */
int MapMenu_CheckTabs(MapMenu *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked() != 0) {
        return MapMenu_SelectTab(self, MAP_MENU_TAB_CLOSE);
    }
    u8 sub_state = self->base.sub_state;
    if (sub_state != MAP_MENU_SUB_TOUCH && sub_state != MAP_MENU_SUB_KEYS && sub_state != MAP_MENU_SUB_POINTER) {
        return 0;
    }
    int tab = -1;
    if (StateFlags_IsClear2()) {
        tab = MenuTabs_TabAtTouch();
    } else {
        u16 pressed = data_021fbe40.pressed;
        if ((pressed & MAP_MENU_PAD_X) || (pressed & MAP_MENU_PAD_B)) {
            tab = MAP_MENU_TAB_CLOSE;
        } else if (pressed & MAP_MENU_PAD_Y) {
            tab = MAP_MENU_TAB_POCKETS;
        } else if (pressed & MAP_MENU_PAD_SELECT) {
            tab = MAP_MENU_TAB_4;
        }
    }
    return MapMenu_SelectTab(self, tab);
}
CLEAN_AS(func_ov118_0229c478, MapMenu_CheckTabs)

/* func_ov118_0229c510 (vtable slot 0x5c, phase 5): the menu asks to be deleted. */
int MapMenu_RequestDelete(MapMenu *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov118_0229c510, MapMenu_RequestDelete)

/* func_ov118_0229c520 (vtable slot 0x58, phase 4): nothing. */
int MapMenu_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov118_0229c520, MapMenu_Phase4)

/* func_ov118_0229c524 (vtable slot 0x54, phase 3): nothing. */
int MapMenu_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov118_0229c524, MapMenu_Phase3)

/* Obj_ov118_0229cc08::func_ov118_0229c528 (vtable slot 0x50, phase 2): a frame of the menu in
 * use, unless it switched tabs: the frame's start, the sub state, the frame's end. Answers 1. */
int MapMenu_RunInteractive(MapMenu *self)
{
    if (MapMenu_CheckTabs(self)) {
        return 1;
    }
    MapMenu_BeginInteractiveFrame(self);
    MapMenu_RunSubState(self);
    MapMenu_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov118_0229cc0819func_ov118_0229c528Ev, MapMenu_RunInteractive)

/* Obj_ov118_0229cc08::func_ov118_0229c554: the sub state's function (MapMenuSubState) through
 * the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 11; the game reads past the table for others. */
void MapMenu_RunSubState(MapMenu *self)
{
    static const MemberPointer *const sub_states[MAP_MENU_SUB_STATES] = {
        &data_ov118_0229cb10, &data_ov118_0229cb18, &data_ov118_0229caf8, &data_ov118_0229cb68,
        &data_ov118_0229cae8, &data_ov118_0229cac8, &data_ov118_0229cad0, &data_ov118_0229cb00,
        &data_ov118_0229cb08, &data_ov118_0229cb20, &data_ov118_0229caf0,
    };
    MemberTable_InitOnce(&data_ov118_0229cd40, data_ov118_0229cd90, sub_states, MAP_MENU_SUB_STATES);
    MemberPointer_CallVoid(&data_ov118_0229cd90[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov118_0229cc0819func_ov118_0229c554Ev, MapMenu_RunSubState)

/* Obj_ov118_0229cc08::func_ov118_0229c63c (vtable slot 0x4c, phase 1): the state's function
 * (MapMenuState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 9; the game reads past the table for others. */
int MapMenu_RunState(MapMenu *self)
{
    static const MemberPointer *const states[MAP_MENU_STATES] = {
        &data_ov118_0229cb60, &data_ov118_0229cb58, &data_ov118_0229cb50, &data_ov118_0229cb48, &data_ov118_0229cae0,
        &data_ov118_0229cb38, &data_ov118_0229cb30, &data_ov118_0229cb28, &data_ov118_0229cad8,
    };
    MemberTable_InitOnce(&data_ov118_0229cd44, data_ov118_0229cd48, states, MAP_MENU_STATES);
    MapMenu_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov118_0229cd48[self->base.state], self);
    MapMenu_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov118_0229cc0819func_ov118_0229c63cEv, MapMenu_RunState)

/* The cells at the screen's centre, lowered by the wipe, priority 2, unscaled. */
static void map_menu_draw_cells(const OamEntry *cells, int y, int palette)
{
    OamBuffer_DrawCell(1, cells, 0x80, y, palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* func_ov118_0229c714 (vtable slot 0x24): while the OBJs are drawn, lowered by the wipe: the
 * knob placed on its bar (when the list scrolls); with the keys in use, the cursor (on the knob
 * while it is held); the frame's cells and the two list buttons (the shown list's lit, palettes
 * 0xb-0xe); with the free pointer over a mark, its ring; the player's place, 12 frames of 16;
 * the extra marks and the marks, the selected one in palette 8 while it is in its on half; the
 * knob. Answers 1. */
int MapMenu_Draw(MapMenu *self)
{
    int y = self->wipe_y + 0x60;

    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_DRAWN) == 0) {
        return 1;
    }
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS) != 0) {
        DualCellSprite_SetOffset(map_menu_knob_sprite(self), 0x67, self->wipe_y - 0x12 + self->knob);
    }
    if (StateFlags_Test2() != 0) {
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_ON_KNOB) != 0) {
            int x = PushButton_FaceX(&self->knob_button);
            Glider_PlaceAt(&self->cursor, x, PushButton_FaceY(&self->knob_button));
        }
        Glider_DrawWrapped(&self->cursor);
    }
    map_menu_draw_cells(data_ov118_0229cbb0, y, -1);
    int places_palette;
    int residents_palette;
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES) != 0) {
        places_palette = 0xc;
        residents_palette = 0xd;
    } else {
        places_palette = 0xb;
        residents_palette = 0xe;
    }
    map_menu_draw_cells(data_ov118_0229cb70, y, residents_palette);
    map_menu_draw_cells(data_ov118_0229cb90, y, places_palette);

    if (StateFlags_Test2() != 0 && MapMenu_TestFlags(self, MAP_MENU_FLAG_POINTER) != 0 &&
        self->pointed_mark != MAP_MENU_NO_MARK && self->marks[self->pointed_mark].kind != MAP_MENU_MARK_NONE) {
        const MapMenuMark *mark = &self->marks[self->pointed_mark];
        MapMenu_DrawMark(self, mark->x, self->wipe_y + mark->y, MAP_MENU_MARK_POINTED, 0, -1);
    }
    self->frame = (u8) ((self->frame + 1) & 0xf);
    if ((self->frame & 0xc) != 0) {
        MapMenu_DrawMark(self, self->position_x, self->position_y + self->wipe_y, MAP_MENU_MARK_POSITION, 0, -1);
    }
    for (int i = 0; i < MAP_MENU_EXTRA_MARKS; i++) {
        u8 kind = self->extra_marks[i].kind;
        if (kind != MAP_MENU_MARK_NONE) {
            int flip = (kind & MAP_MENU_MARK_FLIP) != 0 ? 1 : 0;
            MapMenu_DrawMark(self, self->extra_marks[i].x, self->wipe_y + self->extra_marks[i].y,
                             (u8) (kind & ~MAP_MENU_MARK_FLIP), flip, -1);
        }
    }
    for (int i = 0; i < MAP_MENU_MARKS; i++) {
        const MapMenuMark *mark = &self->marks[i];
        if (mark->kind != MAP_MENU_MARK_NONE) {
            int palette;
            if (i == self->mark && MapMenu_TestFlags(self, MAP_MENU_FLAG_MARK_OFF) == 0) {
                palette = 8;
            } else {
                palette = -1;
            }
            MapMenu_DrawMark(self, mark->x, self->wipe_y + mark->y, mark->kind, 0, palette);
        }
    }
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS) != 0) {
        map_menu_call_slot(&self->knob_button, 2);
    }
    return 1;
}
CLEAN_AS(func_ov118_0229c714, MapMenu_Draw)

/* func_ov118_0229c9a4 (vtable slot 0x0c): the menu ends: the bar's menu told its child closed,
 * the members ended. Answers 1. */
int MapMenu_End(MapMenu *self)
{
    MenuTabs_ChildClosed((MenuTabs *) (void *) Process_GetParent((Process *) (void *) self));
    MapMenu_EndMembers(self);
    return 1;
}
CLEAN_AS(func_ov118_0229c9a4, MapMenu_End)

/* func_ov118_0229c9c0 (vtable slot 0x00): the menu starts: its setup, state 0 in phase 1.
 * Answers 1. */
int MapMenu_Start(MapMenu *self)
{
    MapMenu_Setup(self);
    MenuScene_SetState(map_menu_scene(self), MAP_MENU_STATE_LOAD);
    MenuScene_SetPhase(map_menu_scene(self), MAP_MENU_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov118_0229c9c0, MapMenu_Start)

/* func_ov118_0229c9e0: a new menu from the menu scenes' heap (NULL when it has no room): the
 * base, the menu's vtable and its members constructed in order, the arrays by __cxa_vec_ctor. */
MapMenu *MapMenu_New(void)
{
    MapMenu *self = MenuScene_Alloc(sizeof(MapMenu));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov118_0229cc08;
    LayerTask_Construct(&self->rows_task);
    LayerTask_Construct(&self->map_task);
    __cxa_vec_ctor(self->labels, MAP_MENU_ROWS, sizeof(TextLabel), func_02070c08, func_02070be8);
    PushButton_Construct(&self->knob_button);
    Glider0_Construct(&self->cursor);
    TownMapMarkers_Construct(self->spots);
    __cxa_vec_ctor(self->extra_marks, MAP_MENU_EXTRA_MARKS, sizeof(MapMenuMark), func_ov118_0229a43c, func_ov118_0229a438);
    __cxa_vec_ctor(self->marks, MAP_MENU_MARKS, sizeof(MapMenuMark), func_ov118_0229a43c, func_ov118_0229a438);
    return self;
}
CLEAN_AS(func_ov118_0229c9e0, MapMenu_New)
