/* func_ov119_0229bee0 @ 0x0229bee0, 0x9c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206f56c(void *p);
extern void func_ov119_0229a4e4(void *p);
extern int func_ov002_02208014(void *p);
extern void func_ov119_0229b9a4(void *p);
extern void func_ov002_02208098(void *p, int v);
extern int func_ov002_02208008(void *p);
extern int func_ov119_0229a420(void *p, int v);
extern int func_ov002_02209044(void *p, int v, void *q, u8 b);
extern void func_ov119_0229b8e4(void *p);
extern void func_ov002_0220a1dc(void *p);
extern void func_ov119_0229b884(void *p);

extern struct {
    u16 _pad0;
    u16 flags;
} data_021fbe40;

void func_ov119_0229bee0(char *param)
{
    if (func_0206f56c(param) != 0) {
        func_ov119_0229a4e4(param);
    } else if (func_ov002_02208014(param) != 0) {
        func_ov119_0229b9a4(param);
        func_ov002_02208098(param, 1);
    } else {
        int x = func_ov002_02208008(param);
        u8 y = (u8) func_ov119_0229a420(param, 0x10);
        if (func_ov002_02209044((char *) param + 0xdc, x, (char *) param + 0xae, y) != 0) {
            func_ov119_0229b8e4(param);
        } else {
            if (data_021fbe40.flags & 1) {
                func_ov002_0220a1dc((char *) param + 0xda8);
                func_ov002_02208098(param, 7);
            } else if (data_021fbe40.flags & 2) {
                func_ov119_0229b884(param);
            }
        }
    }
}
