/* func_02075ff8 @ 0x02075ff8, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern void *data_020ccf94;
extern void func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int mask);
extern u8 *func_02073d28(void *h, int n);
extern void func_02077b3c(u8 *p, int a, int b);
extern void MI_CpuCopy8(const void *s, void *d, int n);
extern int func_02073e30(void *h, u8 *p, int n, int mask, int a5, int a6, int a7, int a8, int a9, int a10);

int func_02075ff8(u8 *cnt, u8 *src, unsigned int len, int a4, u16 tag)
{
    void *h;
    u8 *p;
    unsigned int chunks;
    int off;
    unsigned int rem;

    chunks = len / 0xffb;
    if (len % 0xffb != 0) {
        chunks++;
    }
    func_02073044();
    if (func_020ebf70() == 0) {
        goto tail;
    }
    if (func_02077a8c(tag) == 0) {
        goto tail;
    }
    off = cnt[0] * 0xffb;
    rem = len - off;
    if (rem > 0xffb) {
        rem = 0xffb;
    }
    h = data_020ccf94;
    p = func_02073d28(h, 4);
    func_02077b3c(p, 0, a4);
    MI_CpuCopy8(&off, p + 1, 4);
    MI_CpuCopy8(src + off, p + 5, rem);
    if (func_02073e30(h, func_02073d28(h, 4), rem + 5, tag, 0, 0, 0, 0, 0, 0) == 0) {
        goto tail;
    }
    cnt[0] = (u8) (cnt[0] + 1);
tail:
    if (cnt[0] >= chunks) {
        return 1;
    }
    return 0;
}
