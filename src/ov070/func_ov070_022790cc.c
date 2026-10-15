/* func_ov070_022790cc @ 0x022790cc, 0x158 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022790cc_3 {
    char pad_00[0xc4];
    u16 unk_C4;
    u16 unk_C6;
    u16 unk_C8;
} UnkStruct_022790cc_3;

typedef struct UnkStruct_022790cc_2 {
    u16 h;
    u8 n;
} UnkStruct_022790cc_2;

typedef struct UnkStruct_022790cc {
    u16 a;
    u16 b;
    u16 c;
    UnkStruct_022790cc_2 q;
} UnkStruct_022790cc;

extern unsigned char func_02099f1c(void *flags, int (*callback)(void *));
extern int func_ov070_02279224(void *element);
extern void func_ov070_02279238(UnkStruct_022790cc_3 *self);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);

int func_ov070_022790cc(UnkStruct_022790cc_3 *self)
{
    UnkStruct_022790cc s;
    u8 count;
    int r;
    unsigned int ok;
    unsigned int in;

    func_02099f1c(&s.q, func_ov070_02279224);
    count = 0;
    func_ov070_02279238(self);

    if (func_0204bcdc(&self->unk_C4) != 0) {
        s.a = 0xfff1;
        r = func_0204bc64(&self->unk_C4);
        ok = (r == func_0204bc64(&s.a)) ? 1 : 0;
    } else {
        ok = (self->unk_C4 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        in = 0;
        if (self->unk_C4 >= 0x1429 && self->unk_C4 <= 0x1430) {
            in = 1;
        }
        if (in == 0) {
            count++;
        }
    }

    if (func_0204bcdc(&self->unk_C6) != 0) {
        s.b = 0xfff1;
        r = func_0204bc64(&self->unk_C6);
        ok = (r == func_0204bc64(&s.b)) ? 1 : 0;
    } else {
        ok = (self->unk_C6 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        count++;
    }

    if (func_0204bcdc(&self->unk_C8) != 0) {
        s.c = 0xfff1;
        r = func_0204bc64(&self->unk_C8);
        ok = (r == func_0204bc64(&s.c)) ? 1 : 0;
    } else {
        ok = (self->unk_C8 == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        in = 0;
        if (self->unk_C8 >= 0x12a8 && self->unk_C8 <= 0x12af) {
            in = 1;
        }
        if (in == 0) {
            count++;
        }
    }

    return (s.q.n >= count) ? 1 : 0;
}
