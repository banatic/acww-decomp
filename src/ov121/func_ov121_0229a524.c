/* func_ov121_0229a524 @ 0x0229a524, 0x16 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern BOOL CARD_IsEnabled(void);
extern int func_0203ac44(void);

void func_ov121_0229a524(void *receiver)
{
    if (!CARD_IsEnabled()) {
        func_0203ac44();
    }
}
