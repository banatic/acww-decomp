/* func_ov126_022a07e8 @ 0x022a07e8, 0x6c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021f6c58;
extern u8 data_021f6c54;

extern void func_ov126_022a0854(void *self, int arg);
extern void func_ov126_022a06b4(void *self);
extern void func_ov002_02208098(void *self, int v);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov126_022a0168(void *self);

int func_ov126_022a07e8(void *obj)
{
    int v = data_021f6c58;
    int w = data_021f6c54;

    if (w < 0x28 || w > 0x38) {
        return 0;
    }
    if (v < ((u8 *) obj)[0xab] - 0xc) {
        return 0;
    }
    if (v > ((u8 *) obj)[0xac] + 0xc) {
        return 0;
    }
    func_ov126_022a0854(obj, v);
    func_ov126_022a06b4(obj);
    func_ov002_02208098(obj, 1);
    func_ov095_0229b3ec((char *) obj + 0x19c);
    func_ov126_022a0168(obj);
    return 1;
}
