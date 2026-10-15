/* Flags in the large state block (state_block.h). */
#include "state_block.h"

#include "clean.h"

#define FLAGS_OFFSET 0x173f4 /* one word: flags 0-31 */

static volatile u32 *flags_of(u32 *block)
{
    return (volatile u32 *) ((u8 *) block + FLAGS_OFFSET);
}

/* func_0209f100. Flags 32 and above do not exist and are ignored. */
void StateBlock_ClearFlag(u32 *block, u32 flag)
{
    if (flag < 32) {
        *flags_of(block) &= ~(1u << flag);
    }
}
CLEAN_AS(func_0209f100, StateBlock_ClearFlag)

/* func_0209f128 */
void StateBlock_SetFlag(u32 *block, u32 flag)
{
    if (flag < 32) {
        *flags_of(block) |= 1u << flag;
    }
}
CLEAN_AS(func_0209f128, StateBlock_SetFlag)

/* func_0209f150: whether `flag` is set; flags 32 and above never are. */
int StateBlock_TestFlag(u32 *block, u32 flag)
{
    return flag < 32 && (*flags_of(block) & (1u << flag)) != 0;
}
CLEAN_AS(func_0209f150, StateBlock_TestFlag)
