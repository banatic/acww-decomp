/* func_ov046_02261750 @ 0x02261750, 0x84 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int gt2GetIncomingBufferSize(u8 *p);
extern int func_0201c314(u8 *self, int r);
extern void func_0209129c(int v);
extern void func_020147fc(u8 *p, int a, int b, int c);
extern void func_0201ad18(u8 *p, int a, int b, int c, void *d, int e, int f, int g);
extern u8 data_021fbee8[];
extern int data_020c814c;

int func_ov046_02261750(u8 *self)
{
    int a;
    int r;

    r = gt2GetIncomingBufferSize(self + 0x658);
    a = 0;
    if (r != 0) {
        a = func_0201c314(self, r);
    }
    if (*(int *) (self + 0x740) != -1) {
        func_0209129c(*(int *) (self + 0x740));
        *(int *) (self + 0x740) = -1;
    }
    func_020147fc(self + 0x618, 0, a, 0);
    func_0201ad18(self + 0x3b0, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    return 1;
}
