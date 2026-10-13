/* func_ov068_022691d0 @ 0x022691d0, 0xa8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x560];
    u8 flag560;
    u8 pad_561[0xa04 - 0x561];
    u8 flagA04;
    u8 pad_A05[0xa0c - 0xa05];
    u32 unk_A0C;
} Param;

extern void func_ov068_0226cfd4(void *p);
extern int func_0201ce18(void *p);
extern int func_0201c2c8(void *p, unsigned char b);
extern void func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, void *f, int g, int h, int i);
extern unsigned short data_020c80f8;
extern char data_021fbee8;
extern int data_020c814c;

int func_ov068_022691d0(unsigned char *out, Param *param)
{
    func_ov068_0226cfd4(param);
    if (func_0201ce18(param) != 0 || param->unk_A0C != 3 || param->flagA04 != 0) {
        out[0x1c] = 1;
    } else {
        int x = func_0201c2c8(param, param->flag560);
        func_02019d0c((char *) param + 0x564, 3, 2, 0, 0, 0, x, 0, 0, (int) data_020c80f8, 0);
        func_ov068_02266c34((char *) param + 0x898, param, 1, 0, 0, (void *) &data_021fbee8, 4, data_020c814c, 1);
        out[0x1c] = 0;
    }
    return 1;
}
