/* The screen indicators process (vtable data_020e2288, 0x50 bytes, a process of the root class
 * data_020da13c): it creates, deletes, executes and draws the game's indicators over the
 * screen together: the screen icon (screen_icon.h), the wireless icons (wireless_icon.h), the
 * screen panels (screen_panels.h) and the object at data_021d35f8. Each of its phases is done
 * at once. */
#ifndef CLEAN_MAIN_SCREEN_INDICATORS_H
#define CLEAN_MAIN_SCREEN_INDICATORS_H

#include "autoload_2/process.h"
#include "types.h"

typedef struct ScreenIndicators {
    Process process;
} ScreenIndicators;

int ScreenIndicators_Draw(void);
int ScreenIndicators_Execute(void);
int ScreenIndicators_Delete(void);
int ScreenIndicators_Create(void);
ScreenIndicators *ScreenIndicators_DestructFree(ScreenIndicators *indicators);
ScreenIndicators *ScreenIndicators_Destruct(ScreenIndicators *indicators);
ScreenIndicators *ScreenIndicators_Construct(ScreenIndicators *indicators);
void ScreenIndicators_New(void);

#endif
