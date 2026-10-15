/* func_020759e0 @ 0x020759e0, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern unsigned int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int mask);
extern u8 *func_02073d28(void *h, int n);
extern void func_02077b3c(u8 *p, int a, int b);
extern void func_020a6e4c(int i, u8 *a, u8 *b, u8 *c);
extern int func_020a7880(u8 *o);
extern void func_020a7850(u8 *o, int a, int b, int c, int d);
extern void MI_CpuCopy8(const void *s, void *d, int n);
extern int func_020a7870(u8 *o);
extern int func_02073e30(void *h, u8 *p, int n, int mask, int a5, int a6, int a7, int a8, int a9, int a10);

int func_020759e0(int bit)
{
    int mask;
    u8 *p;
    int n;
    unsigned int i;
    void *h;
    u8 buf[12];

    mask = (u16) (1 << bit);
    func_02073044();
    if (func_020ebf70() == 0) {
        goto fail;
    }
    if (func_02077a8c(mask) == 0) {
        goto fail;
    }
    p = func_02073d28(data_020ccf94, 4);
    n = 0;
    func_02077b3c(p, n, 0xf);
    p++;
    n++;
    for (i = 0; i < 4; i++) {
        func_020a6e4c(i, &buf[0], &buf[1], &buf[2]);
        func_020a7880(&buf[3]);
        func_020a7850(&buf[3], buf[0], buf[1], buf[2], 7);
        MI_CpuCopy8(&buf[3], p, 2);
        p += 2;
        n += 2;
        func_020a7870(&buf[3]);
    }
    h = data_020ccf94;
    return func_02073e30(h, func_02073d28(h, 4), n, mask, 0, 0, 0, 0, 0, 0);
fail:
    return 0;
}
