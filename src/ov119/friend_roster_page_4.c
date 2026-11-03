/* friend_roster_page_4: 2 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229c218 @ 0x0229c218, 0x90 bytes, Thumb
 * func_ov119_0229c1a0 @ 0x0229c1a0, 0x78 bytes, Thumb
 */

#include "types.h"

extern void *data_021fbe94;
extern u8 data_ov119_0229cf5c[];
extern u8 data_ov119_0229cf70[];
extern u8 data_ov119_0229cf84[];
extern u8 data_ov119_0229cf98[];
extern u8 data_ov119_0229cfb0[];
extern u8 data_ov119_0229cfc8[];
extern int func_02002d14(u8 *a, void *h, int n, int p, int q, int r);
extern int func_02064af4(u8 *a, u8 *dst, int len);
extern int func_02002c6c(u8 *a, void *h, int n, int p, int q, int r);
extern int func_02002ca4(u8 *a, void *h, int n);
extern char data_ov119_0229cf00[];
extern char data_ov119_0229cf18[];
extern char data_ov119_0229cf30[];
extern char data_ov119_0229cf44[];

void func_ov119_0229c218(u8 *self)
{
    void *h;

    h = data_021fbe94;
    func_02002d14(data_ov119_0229cf5c, h, 6, 1, 1, 5);
    func_02064af4(data_ov119_0229cf70, self + 0x1e30, 0x20);
    func_02002c6c(data_ov119_0229cf84, h, 6, 0x11, 0x11, 0x89);
    func_02002ca4(data_ov119_0229cf98, h, 6);
    func_02064af4(data_ov119_0229cfb0, self + 0xe0c, 0x800);
    func_02064af4(data_ov119_0229cfc8, self + 0x160c, 0x800);
}

void func_ov119_0229c1a0(int a1)
{
    void *p;

    p = data_021fbe94;
    func_02002c6c((u8 *) ((void *) data_ov119_0229cf00), p, 8, 0xc0, 0xc0, 0x15d);
    func_02002c6c((u8 *) ((void *) data_ov119_0229cf18), p, 8, 0x1a0, 0x1a0, 0x1df);
    func_02002d14((u8 *) ((void *) data_ov119_0229cf30), p, 8, 4, 4, 0xa);
    func_02064af4((u8 *) ((void *) data_ov119_0229cf44), (u8 *) ((void *) (a1 + 0x1e10)), 0x20);
}
