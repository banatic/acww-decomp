/* Single values kept next to the current activity (activity_vars.h). */
#include "activity_vars.h"

#include "clean.h"

extern u8 data_021f3c08;
extern u8 data_021f3c1c;
extern StateBlock *data_021f3c24;
extern int data_021f3c34;

/* func_020a13a0 */
void ActivityVars_SetFlag3C08(void)
{
    data_021f3c08 = 1;
}
CLEAN_AS(func_020a13a0, ActivityVars_SetFlag3C08)

/* func_020a13ac */
u8 ActivityVars_Flag3C08(void)
{
    return data_021f3c08;
}
CLEAN_AS(func_020a13ac, ActivityVars_Flag3C08)

/* func_020a13b8 */
StateBlock *ActivityVars_ReceivedBlock(void)
{
    return data_021f3c24;
}
CLEAN_AS(func_020a13b8, ActivityVars_ReceivedBlock)

/* func_020a13c4: the slot's low byte kept (overlay 48 gives this system's AID). */
void ActivityVars_SetSlot3C1C(u32 slot)
{
    data_021f3c1c = (u8) slot;
}
CLEAN_AS(func_020a13c4, ActivityVars_SetSlot3C1C)

/* func_020a13d0 */
u8 ActivityVars_Slot3C1C(void)
{
    return data_021f3c1c;
}
CLEAN_AS(func_020a13d0, ActivityVars_Slot3C1C)

/* func_020a13dc */
void ActivityVars_SetTownPlayer(int number)
{
    data_021f3c34 = number;
}
CLEAN_AS(func_020a13dc, ActivityVars_SetTownPlayer)
