/* func_02052118 @ 0x02052118, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_020e54a8;
extern void *data_021c80bc;
extern void *data_020ccf94;

extern int func_020b65c4(void);
extern void *func_0204d5c8(int);
extern int func_0204f538(void *, u16 *, int, int, int);
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, u32 *, int);
extern void func_02073770(void *, int, int);

void func_02052118(int a0, int a1, int a2, u16 *a3, u8 a4)
{
    u32 packed;
    void *obj;
    void *obj2;
    unsigned int cond;

    cond = (data_020e54a8 == 1);
    if (cond && func_020b65c4() == a0) {
        obj = data_021c80bc;
    } else {
        obj = func_0204d5c8(a0);
    }
    if (obj == 0) {
        return;
    }
    if (func_0204f538(obj, a3, a1, a2, 1) == 0) {
        return;
    }
    if (a4 == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }

    packed = (packed & ~0xf) | (a1 & 0xf);
    packed = (packed & ~0xf0) | ((a2 & 0xf) << 4);
    packed = (packed & 0xff0000ff) | (((u32) *a3 & 0xffff) << 8);

    obj2 = data_020ccf94;
    func_02073820(obj2);
    func_020737f0(obj2, &packed, 4);
    func_02073770(obj2, 0x1a, 4);
}
