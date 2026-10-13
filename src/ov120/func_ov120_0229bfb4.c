/* func_ov120_0229bfb4 @ 0x0229bfb4, 0x16 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct GXDLInfo GXDLInfo;

extern void func_ov120_0229b9dc(GXDLInfo *info, int op, u32 param0, u32 param1);
extern void func_ov002_02208090(GXDLInfo *info, int n);

void func_ov120_0229bfb4(GXDLInfo *info, int op, u32 param0, u32 param1)
{
    func_ov120_0229b9dc(info, op, param0, param1);

    func_ov002_02208090(info, 2);
}
