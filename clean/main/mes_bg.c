/* The background of a message window kind and its marker and slider sprites (mes_bg.h). */
#include "mes_bg.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(MesBg, colours_dirty) == 0x12, "MesBg layout");
static_assert(offsetof(MesBg, lines) == 0x1e, "MesBg layout");
static_assert(sizeof(MesBg) == 0x20, "MesBg layout");
static_assert(offsetof(MesBgMarker, unk_28) == 0x28, "MesBgMarker layout");
static_assert(sizeof(MesBgMarker) == 0x4c, "MesBgMarker layout");
static_assert(offsetof(MesBgIndicator, state) == 0x3c, "MesBgIndicator layout");
static_assert(sizeof(MesBgIndicator) == 0x48, "MesBgIndicator layout");
static_assert(offsetof(MesBgSlider, indicator) == 0x10, "MesBgSlider layout");
static_assert(sizeof(MesBgSlider) == 0x58, "MesBgSlider layout");

#define FS_READ_FAILED (-1)
#define SCALE_ONE 0x1000

/* The classes' vtables. */
extern const u8 data_020e3fb4[];
extern const MesBgSpriteVtable data_020e4030;
extern const MesBgSpriteVtable data_020e4014;
/* "/a_mes/a_mes1a_bg_nsc.bin" */
extern const char data_020e40c4[];
/* The cells the slider's knob is drawn with: the first entry. */
extern const void *const *data_020d5b3c;

extern int FS_OpenFile(void *file, const char *path);
extern s32 FS_ReadFile(void *file, void *dst, s32 size);
extern int FS_CloseFile(void *file);
extern void func_020ac8a8(MesBg *bg); /* frees the screen */

/* main's sprite classes */
extern void *func_0208e8d4(void *sprite, u8 kind);     /* constructor */
extern void *func_0208e7f0(void *sprite);              /* destructor */
extern void func_0208af30(void *sprite);               /* the base class's constructor: place (0x80, 0x60) */
extern void func_0208af00(void *sprite);               /* the base class's destructor */
extern void func_0208aef4(void *sprite, int x, int y); /* place at (0x80 + x, 0x60 + y) */
extern int func_0208aeec(void *sprite);                /* y */
extern int func_0208aef0(void *sprite);                /* x */
extern MesBgIndicator *func_0208ec40(MesBgIndicator *indicator, u8 kind); /* constructor */
extern MesBgIndicator *func_0208ec14(MesBgIndicator *indicator);          /* destructor */
extern void func_0208ea6c(MesBgIndicator *indicator, int value);
extern void func_0208ea70(MesBgIndicator *indicator, int x, int y); /* the offset */
extern void *func_0208e95c(MesBgIndicator *indicator, int state);
extern int func_0208e958(MesBgIndicator *indicator); /* the state */
extern int func_0208e930(MesBgIndicator *indicator); /* both animations at their end */
extern void func_0208e9e0(MesBgIndicator *indicator, int *dx, int *dy);
extern void func_02088df8(int a0, const void *cell, int x, int y, int palette, int priority, int scale_x, int scale_y,
                          int rotation, int p9, int p10, int p11);

/* func_020ac8f0: reads the first MES_BG_SCREEN_SIZE bytes of /a_mes/a_mes1a_bg_nsc.bin into a
 * block of the current heap kept in `screen`. Returns 1 when the file opened, the block was
 * had, the read worked and the file closed.
 * QUIRK: the block is asked for, and the file closed, even when it did not open. */
int MesBg_LoadScreen(MesBg *bg, void *file)
{
    int opened = FS_OpenFile(file, data_020e40c4);
    bg->screen = Heap_AllocCurrentBack(MES_BG_SCREEN_SIZE);
    int read = 0;
    if (bg->screen != NULL) {
        read = FS_ReadFile(file, bg->screen, MES_BG_SCREEN_SIZE) != FS_READ_FAILED;
    }
    int closed = FS_CloseFile(file);
    return opened && read && closed && bg->screen != NULL;
}
CLEAN_AS(func_020ac8f0, MesBg_LoadScreen)

/* func_020ac954: the destructor the derived classes' destructors end with (the same as
 * MesBg_Destruct). */
MesBg *MesBg_DestructBase(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    func_020ac8a8(bg);
    return bg;
}
CLEAN_AS(func_020ac954, MesBg_DestructBase)

/* func_020ac96c: the class's deleting destructor (vtable slot 1). */
MesBg *MesBg_DestructDelete(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    func_020ac8a8(bg);
    Heap_OperatorDeleteB(bg);
    return bg;
}
CLEAN_AS(func_020ac96c, MesBg_DestructDelete)

/* func_020ac98c: the class's destructor (vtable slot 0). */
MesBg *MesBg_Destruct(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    func_020ac8a8(bg);
    return bg;
}
CLEAN_AS(func_020ac98c, MesBg_Destruct)

/* func_020ac9a4 */
void MesBg_Construct(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    bg->screen = NULL;
    bg->colours_dirty = 0;
    bg->columns = 0;
    bg->scroll_x = 0;
    bg->scroll_y = 0;
    bg->lines_top = 0;
    bg->lines = 0;
    for (int i = 0; i < MES_BG_COLOURS; i++) {
        bg->colours[i] = 0;
    }
}
CLEAN_AS(func_020ac9a4, MesBg_Construct)

/* func_020ac9cc: the marker's deleting destructor (vtable slot 1). */
MesBgMarker *MesBgMarker_DestructDelete(MesBgMarker *marker)
{
    marker->vtable = &data_020e4030;
    func_0208e7f0(marker);
    Heap_OperatorDeleteB(marker);
    return marker;
}
CLEAN_AS(func_020ac9cc, MesBgMarker_DestructDelete)

/* func_020ac9ec: the marker's destructor (vtable slot 0). */
MesBgMarker *MesBgMarker_Destruct(MesBgMarker *marker)
{
    marker->vtable = &data_020e4030;
    func_0208e7f0(marker);
    return marker;
}
CLEAN_AS(func_020ac9ec, MesBgMarker_Destruct)

/* func_020aca04 */
MesBgMarker *MesBgMarker_Construct(MesBgMarker *marker)
{
    func_0208e8d4(marker, 1);
    marker->vtable = &data_020e4030;
    marker->unk_28 = 0;
    return marker;
}
CLEAN_AS(func_020aca04, MesBgMarker_Construct)

/* func_020aca24 */
void MesBgSlider_PlayIndicatorB(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 3);
}
CLEAN_AS(func_020aca24, MesBgSlider_PlayIndicatorB)

/* func_020aca30 */
void MesBgSlider_PlayIndicatorA(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 2);
}
CLEAN_AS(func_020aca30, MesBgSlider_PlayIndicatorA)

/* func_020aca3c: indicator state 0, in which the slider is not drawn. */
void MesBgSlider_Hide(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 0);
}
CLEAN_AS(func_020aca3c, MesBgSlider_Hide)

/* func_020aca48 */
void MesBgSlider_ShowStill(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 1);
}
CLEAN_AS(func_020aca48, MesBgSlider_ShowStill)

/* func_020aca54 */
int MesBgSlider_IndicatorDone(MesBgSlider *slider)
{
    return func_0208e930(&slider->indicator);
}
CLEAN_AS(func_020aca54, MesBgSlider_IndicatorDone)

/* func_020aca60: how far the indicator's animations move (0 unless it plays them). */
void MesBgSlider_IndicatorMove(MesBgSlider *slider, int *dx, int *dy)
{
    func_0208e9e0(&slider->indicator, dx, dy);
}
CLEAN_AS(func_020aca60, MesBgSlider_IndicatorMove)

/* func_020aca6c: the top of the track, from the slider's place. */
int MesBgSlider_TrackTop(MesBgSlider *slider)
{
    (void) slider;
    return 0;
}
CLEAN_AS(func_020aca6c, MesBgSlider_TrackTop)

/* func_020aca70: the bottom of the track, from the slider's place. */
int MesBgSlider_TrackBottom(MesBgSlider *slider)
{
    (void) slider;
    return MES_BG_SLIDER_TRACK;
}
CLEAN_AS(func_020aca70, MesBgSlider_TrackBottom)

/* func_020aca74: the knob's offset down the track. */
int MesBgSlider_KnobY(MesBgSlider *slider)
{
    return MesBgSlider_LevelToY(slider);
}
CLEAN_AS(func_020aca74, MesBgSlider_KnobY)

/* func_020aca7c: the indicator's offset across, from the slider's place. */
int MesBgSlider_TrackX(MesBgSlider *slider)
{
    (void) slider;
    return 6;
}
CLEAN_AS(func_020aca7c, MesBgSlider_TrackX)

/* func_020aca80: the level as an offset down the track, 0 at the top level to 32 at level 0.
 * QUIRK: the product is formed in 32 bits and shifted down with its sign, so a level outside
 * 0-0x1000 gives an offset outside the track (and wraps for levels beyond 2^26 away). */
int MesBgSlider_LevelToY(MesBgSlider *slider)
{
    s32 scaled = (s32) ((u32) (MES_BG_SLIDER_LEVEL_TOP - slider->level) * MES_BG_SLIDER_TRACK);
    return scaled >> 12;
}
CLEAN_AS(func_020aca80, MesBgSlider_LevelToY)

/* func_020aca94 */
void MesBgSlider_SetLevel(MesBgSlider *slider, fx32 level)
{
    slider->level = level;
}
CLEAN_AS(func_020aca94, MesBgSlider_SetLevel)

/* func_020aca98: the class's place function (vtable slot 4): the slider's place, and the
 * indicator's own place function with the same values. */
void MesBgSlider_SetPlace(MesBgSlider *slider, int x, int y)
{
    func_0208aef4(slider, x, y);
    slider->indicator.vtable->set_place(&slider->indicator, x, y);
}
CLEAN_AS(func_020aca98, MesBgSlider_SetPlace)

/* func_020acab8: the class's update (vtable slot 3): the indicator goes beside the knob and
 * updates. */
void MesBgSlider_Update(MesBgSlider *slider)
{
    int x = MesBgSlider_TrackX(slider);
    int y = MesBgSlider_KnobY(slider);
    func_0208ea70(&slider->indicator, x, y);
    slider->indicator.vtable->update(&slider->indicator);
}
CLEAN_AS(func_020acab8, MesBgSlider_Update)

/* func_020acae8: the class's draw (vtable slot 2): unless hidden, the indicator, then the knob
 * at the slider's place. */
void MesBgSlider_Draw(MesBgSlider *slider)
{
    if (func_0208e958(&slider->indicator) == 0) {
        return;
    }
    slider->indicator.vtable->draw(&slider->indicator);
    const void *cell = data_020d5b3c[0];
    int y = func_0208aeec(slider);
    int x = func_0208aef0(slider);
    func_02088df8(0, cell, x, y, -1, 0, SCALE_ONE, SCALE_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_020acae8, MesBgSlider_Draw)

/* func_020acb48: the slider's deleting destructor (vtable slot 1). */
MesBgSlider *MesBgSlider_DestructDelete(MesBgSlider *slider)
{
    slider->vtable = &data_020e4014;
    func_0208ec14(&slider->indicator);
    func_0208af00(slider);
    Heap_OperatorDeleteB(slider);
    return slider;
}
CLEAN_AS(func_020acb48, MesBgSlider_DestructDelete)

/* func_020acb70: the slider's destructor (vtable slot 0). */
MesBgSlider *MesBgSlider_Destruct(MesBgSlider *slider)
{
    slider->vtable = &data_020e4014;
    func_0208ec14(&slider->indicator);
    func_0208af00(slider);
    return slider;
}
CLEAN_AS(func_020acb70, MesBgSlider_Destruct)

/* func_020acb94: a slider at half level, its indicator of kind 1 hidden. */
MesBgSlider *MesBgSlider_Construct(MesBgSlider *slider)
{
    func_0208af30(slider);
    slider->vtable = &data_020e4014;
    slider->level = MES_BG_SLIDER_LEVEL_TOP / 2;
    func_0208ec40(&slider->indicator, 1);
    func_0208ea6c(&slider->indicator, 0);
    return slider;
}
CLEAN_AS(func_020acb94, MesBgSlider_Construct)
