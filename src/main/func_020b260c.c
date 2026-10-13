/* func_020b260c @ 0x020b260c, 0x128 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct ModeIdx {
    u8 mode : 2;
    u8 idx : 6;
} ModeIdx;

typedef struct Nibble {
    u8 low : 4;
    u8 high : 4;
} Nibble;

extern Nibble data_021f4bac[];
extern u8 data_020d1f24[];
extern void *data_020ccf94;

extern int func_020b3fc0(int a);
extern void func_020b2a68(void *dst, const void *src);
extern unsigned int func_020b2a3c(void *buf);
extern int func_0204bbd4(int a);
extern int func_020b278c(int a);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *buf, int a);
extern void func_02073770(void *obj, int a, int b);
extern void func_020b2a64(void *buf);

void func_020b260c(u8 *p, int arg2)
{
    ModeIdx *m = (ModeIdx *) p;
    u32 mode = m->mode;
    u32 idx = m->idx;
    u8 buf[16];
    u32 res1;
    u32 res2;
    u8 val;
    Nibble *q;
    const u8 *src;
    void *obj;

    if (mode == 1) {
        goto set_mode;
    }
    if (mode == 2) {
        goto set_mode;
    }
    if (mode == 3) {
    set_mode:
        data_021f4bac[idx].high = mode;
        goto done;
    }

    q = &data_021f4bac[idx];
    val = q->low;
    res1 = func_020b3fc0(val);
    val = (u8) (val | (1 << arg2));
    res2 = func_020b3fc0(val);

    if (idx < 0x22) {
        src = &data_020d1f24[idx * 10];
    } else {
        src = &data_020d1f24[0];
    }

    func_020b2a68(&buf[2], src);

    if (res2 > func_020b2a3c(&buf[2])) {
        q->high = 2;
    } else {
        idx = func_0204bbd4(idx);
        if (func_020b278c(idx) != 0 && res1 == 0) {
            q->high = 3;
        } else {
            *(u8 *) q = (*(u8 *) q & ~0xf) | (val & 0xf);
            q->high = 1;
            func_020b278c(idx);
        }
    }

    buf[0] = *p;
    buf[0] = (buf[0] & ~3) | (q->high & 3);

    obj = data_020ccf94;
    func_02073820(obj);
    func_020737f0(obj, buf, 1);
    func_02073770(obj, 0x23, arg2);
    func_020b2a64(&buf[2]);

done:
    return;
}
