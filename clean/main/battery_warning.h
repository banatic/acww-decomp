/* The check for a low battery that the field's actor of this console makes each frame
 * (field_actor_support.c): every 20th call the power manager is asked for the battery level
 * (PM_GetBattery), and a low level is reported, unless the check was switched off (by a
 * state of the field's actors, field_actor_states.c) since the game's state was last set up
 * (state_block.h). */
#ifndef CLEAN_MAIN_BATTERY_WARNING_H
#define CLEAN_MAIN_BATTERY_WARNING_H

#include "types.h"

void BatteryWarning_Reset(void);
void BatteryWarning_Disable(void);
int BatteryWarning_IsLow(void);

#endif
