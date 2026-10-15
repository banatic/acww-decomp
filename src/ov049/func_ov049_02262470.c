/* func_ov049_02262470 @ 0x02262470, 0xf8 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02262470 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02262470;

struct UnkStruct_02262470_2;
typedef struct ObjVt {
    char pad_00[8];
    void (*unk_08)(struct UnkStruct_02262470_2 *o);
} ObjVt;
typedef struct UnkStruct_02262470_2 {
    ObjVt *vt;
} UnkStruct_02262470_2;

typedef struct UnkStruct_02262470_3 {
    char pad_00[0x658];
    UnkStruct_02262470_2 unk_658;
    char pad_65C[0x738 - 0x65c];
    u16 unk_738;
} UnkStruct_02262470_3;

extern UnkStruct_02262470 *data_020ccf94;
extern int func_0201c0e0(void *unused0);
extern int func_0201c040(UnkStruct_02262470_3 *self, int *a, int *b);
extern void func_0201c054(UnkStruct_02262470_3 *self, int a, int b, int c);
extern int func_0201c2a4(UnkStruct_02262470_3 *self, int a);
extern void func_02016108(UnkStruct_02262470_2 *o, int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_ov049_0226208c(UnkStruct_02262470_2 *o, int a);
extern void func_ov049_02262a94(UnkStruct_02262470_3 *self, int a);
extern int func_020a7278(void);
extern int func_ov049_02260500(UnkStruct_02262470_3 *self);

int func_ov049_02262470(UnkStruct_02262470_3 *self)
{
    u16 tmp;
    int r;
    unsigned int ok;
    int a;
    int b;

    if (func_0201c0e0(self) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(self, &a, &b) != 0 && a == data_020ccf94->unk_64 && a == b) {
            func_0201c054(self, 1, data_020ccf94->unk_64, data_020ccf94->unk_64);
            self->unk_658.vt->unk_08(&self->unk_658);
            func_02016108(&self->unk_658, func_0201c2a4(self, 4));
            if (func_0204bcdc(&self->unk_738) != 0) {
                tmp = 0xfff1;
                r = func_0204bc64(&self->unk_738);
                ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
            } else {
                ok = (self->unk_738 == 0xfff1) ? 1 : 0;
            }
            if (ok != 0) {
                func_ov049_0226208c(&self->unk_658, 2);
            }
            func_ov049_02262a94(self, 4);
        } else if (func_020a7278() != 0 && b == 4) {
            func_0201c054(self, 1, data_020ccf94->unk_64, 4);
            func_ov049_02262a94(self, 0xa);
        }
    } else {
        func_ov049_02260500(self);
    }
    return 1;
}
