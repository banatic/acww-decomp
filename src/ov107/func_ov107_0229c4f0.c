/* func_ov107_0229c4f0 @ 0x0229c4f0, 0x98 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
    char pad_BA[0xbe - 0xba];
    unsigned char unk_BE;
    char pad_BF[0xc0 - 0xbf];
    unsigned int unk_C0;
} UnkStruct_0229c4f0;

extern int func_ov107_0229c354(void *p);
extern int func_ov107_0229d0f0(void *p, int a);
extern int func_ov003_0222780c(int a, int b, void *c);
extern void func_ov107_0229c488(void *p, int a);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov107_0229caa8(void *p);

void func_ov107_0229c4f0(UnkStruct_0229c4f0 *self)
{
    if (self->unk_BE != 0) {
        self->unk_BE--;
        return;
    }
    {
        int r = func_ov107_0229c354(self);
        int w2 = func_ov107_0229d0f0(self, self->unk_B9);
        if (func_ov003_0222780c(r, w2, &self->unk_C0) != 0) {
            volatile u16 w;
            int ok;
            u16 lo;
            u16 hi;
            int v;

            w = (u16) w2;
            ok = 0;
            lo = w;
            hi = w;
            if (hi >= 0x12e8 && lo <= 0x131f) {
                ok = 1;
            }
            if (ok != 0) {
                v = lo - 0x12e8;
            } else {
                v = -1;
            }
            func_ov107_0229c488(self, (u8) v);
            self->unk_BE = 0x14;
            func_ov002_02208098((void *) (self), 0x13);
            func_ov107_0229caa8(self);
        }
    }
}
