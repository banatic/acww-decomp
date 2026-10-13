/* func_ov122_022a1220 @ 0x022a1220, 0x70 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern int func_ov002_0220a784(void *self, int a);
extern void func_ov122_0229ffac(void *self);
extern void func_ov122_0229f348(void *self, int a);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

void func_ov122_022a1220(void *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov122_0229ffac(self);
    } else {
        unsigned int flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (flag > 0) {
            if (func_ov002_0220a784((u8 *) self + 0x4698, 3) != 0) {
                func_ov122_0229f348(self, 3);
            } else if (func_ov002_0220a784((u8 *) self + 0x4698, 4) != 0) {
                func_ov122_0229f348(self, 4);
            }
        }
    }
}
