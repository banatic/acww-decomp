/* func_020eae80 @ 0x020eae80, 0xc8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern int DWC_CanChangeFriendList(void);
extern unsigned short data_021fbefc;
extern unsigned int data_0213e6c4;
extern void *data_021fbf3c;
extern void func_ov065_022797a4(void *param);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);

int func_020eae80(int idx)
{
    void *base;

    if (!DWC_CanChangeFriendList() || data_021fbefc < 5 || data_0213e6c4 != 0) {
        return 0;
    }

    base = data_021fbf3c;
    func_ov065_022797a4((u8 *) base + idx * 0xc);

    MI_CpuFill8((u8 *) data_021fbf3c + idx * 0xc, 0, 0xc);
    MI_CpuFill8((u8 *) data_021fbf3c + 0x180 + idx * 0x23, 0, 0x23);
    *((u8 *) data_021fbf3c + idx * 0x23 + 0x1a0) = 0;

    return 1;
}
