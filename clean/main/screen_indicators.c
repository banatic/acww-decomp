/* The screen indicators process (screen_indicators.h). */
#include "screen_indicators.h"

#include "autoload_2/heap.h" /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "clean.h"
#include "screen_icon.h"
#include "wireless_icon.h"
#include "screen_mark.h"
#include "screen_panels.h"

static_assert(sizeof(ScreenIndicators) == 0x50, "ScreenIndicators");

extern const u32 data_020e2288[]; /* the process's vtable */
extern const u32 data_020da13c[]; /* its base class's */

/* func_0208af44 (vtable slot 9, the DRAW phase): the indicators drawn. */
int ScreenIndicators_Draw(void)
{
    ScreenIcons_DrawIcon();
    WirelessIcons_Draw();
    ScreenPanels_DrawGlobal();
    ScreenMark_DrawInstance();
    return 1;
}
CLEAN_AS(func_0208af44, ScreenIndicators_Draw)

/* func_0208af60 (vtable slot 6, the EXECUTE phase): the indicators updated. */
int ScreenIndicators_Execute(void)
{
    WirelessIcons_Update();
    ScreenIcons_UpdateIcon();
    ScreenMark_UpdateInstance();
    ScreenPanels_UpdateGlobal();
    return 1;
}
CLEAN_AS(func_0208af60, ScreenIndicators_Execute)

/* func_0208af7c (vtable slot 3, the DELETE phase): the indicators rewound. */
int ScreenIndicators_Delete(void)
{
    ScreenPanels_RewindGlobal();
    ScreenMark_RewindInstance();
    ScreenIcons_RestartIconAnim();
    WirelessIcons_Rewind();
    return 1;
}
CLEAN_AS(func_0208af7c, ScreenIndicators_Delete)

/* func_0208af98 (vtable slot 0, the CREATE phase): the indicators reset. */
int ScreenIndicators_Create(void)
{
    WirelessIcons_Reset();
    ScreenIcons_ResetIcon();
    ScreenMark_ResetInstance();
    ScreenPanels_ResetGlobal();
    return 1;
}
CLEAN_AS(func_0208af98, ScreenIndicators_Create)

/* func_0208afb4: the destructor, then the process freed. */
ScreenIndicators *ScreenIndicators_DestructFree(ScreenIndicators *indicators)
{
    indicators->process.vtable = data_020e2288;
    indicators->process.vtable = data_020da13c;
    Process_Destruct(&indicators->process);
    Heap_FreeAux(indicators);
    return indicators;
}
CLEAN_AS(func_0208afb4, ScreenIndicators_DestructFree)

/* func_0208afdc: the destructor. */
ScreenIndicators *ScreenIndicators_Destruct(ScreenIndicators *indicators)
{
    indicators->process.vtable = data_020e2288;
    indicators->process.vtable = data_020da13c;
    Process_Destruct(&indicators->process);
    return indicators;
}
CLEAN_AS(func_0208afdc, ScreenIndicators_Destruct)

/* func_0208affc: the constructor. */
ScreenIndicators *ScreenIndicators_Construct(ScreenIndicators *indicators)
{
    Process_Construct(&indicators->process);
    indicators->process.vtable = data_020da13c;
    indicators->process.vtable = data_020e2288;
    return indicators;
}
CLEAN_AS(func_0208affc, ScreenIndicators_Construct)

/* func_0208b01c: the profile's create: a new process (zeroed, from the auxiliary heap),
 * nothing when there is no room.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * process (or NULL) in r0, the register a profile's create returns it in. */
void ScreenIndicators_New(void)
{
    ScreenIndicators *indicators = Heap_AllocAuxZeroed(sizeof(ScreenIndicators));
    if (indicators != NULL) {
        ScreenIndicators_Construct(indicators);
    }
}
CLEAN_AS(func_0208b01c, ScreenIndicators_New)
