/* func_02052b90 @ 0x02052b90, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Msg {
    u32 f0 : 6;
    u32 f6 : 1;
    u32 f7 : 1;
    u32 f8 : 4;
    u32 f12 : 4;
    u32 f16 : 5;
    u32 f21 : 8;
    u32 f29 : 1;
    u32 f30 : 1;
    u32 f31 : 1;
} Msg;

extern void *data_020ccf94;

extern int func_02052cac(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, Msg *buf, int len);
extern void func_02073770(void *p, int id, int len);

void func_02052b90(Msg *p)
{
    Msg tmp;
    void *obj;

    if (p->f29 == 1) {
        func_02052cac((u8) p->f0, p->f8, p->f12, (u8) p->f6, (u8) p->f16, p->f7 != 0, p->f30 != 0, p->f31 != 0, (u8) p->f21);
        tmp = *p;
        tmp.f29 = 0;
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &tmp, 4);
        func_02073770(obj, 0x18, 4);
    } else {
        func_02052cac((u8) p->f0, p->f8, p->f12, (u8) p->f6, (u8) p->f16, p->f7 != 0, p->f30 != 0, p->f31 != 0, (u8) p->f21);
    }
}
