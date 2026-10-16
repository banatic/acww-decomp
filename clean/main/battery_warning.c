/* The check for a low battery (battery_warning.h). */
#include "battery_warning.h"

#include "clean.h"

/* The calls between two questions to the power manager. */
#define BATTERY_WARNING_PERIOD 20
/* The SDK's answers: the call's success, and the low battery level. */
#define BATTERY_WARNING_PM_SUCCESS 0
#define BATTERY_WARNING_PM_LOW 1

/* Nonzero once the check is switched off; the calls left before the next question. */
extern u8 data_021c30b0;
extern s32 data_021c30b4;

/* The SDK's power manager: the battery level into `*level`; PM_RESULT_SUCCESS (0) or an
 * error. */
extern int PM_GetBattery(int *level);

/* func_0202f164: the check on, its next question 20 calls away. */
void BatteryWarning_Reset(void)
{
    data_021c30b0 = 0;
    data_021c30b4 = BATTERY_WARNING_PERIOD;
}
CLEAN_AS(func_0202f164, BatteryWarning_Reset)

/* func_0202f17c: the check off. */
void BatteryWarning_Disable(void)
{
    data_021c30b0 = 1;
}
CLEAN_AS(func_0202f17c, BatteryWarning_Disable)

/* func_0202f188: with the check on, the count of calls runs down, and when it is out it starts
 * again at 20 and the battery level is asked for: 1 when the power manager answers with a low
 * level, else 0. */
int BatteryWarning_IsLow(void)
{
    if (data_021c30b0 != 0) {
        return 0;
    }
    data_021c30b4 -= 1;
    if (data_021c30b4 > 0) {
        return 0;
    }
    data_021c30b4 = BATTERY_WARNING_PERIOD;
    int level;
    if (PM_GetBattery(&level) != BATTERY_WARNING_PM_SUCCESS) {
        return 0;
    }
    return level == BATTERY_WARNING_PM_LOW;
}
CLEAN_AS(func_0202f188, BatteryWarning_IsLow)
