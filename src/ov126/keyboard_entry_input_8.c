/* keyboard_entry_input_8: 3 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a0854 @ 0x022a0854, 0x70 bytes, Thumb
 * func_ov126_022a07e8 @ 0x022a07e8, 0x6c bytes, Thumb
 * func_ov126_022a0768 @ 0x022a0768, 0x80 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022a0854 {
    unsigned char pad_00[0x98];
    int unk_98;
    unsigned char pad_9C[0xa6 - 0x9c];
    unsigned char unk_A6;
    unsigned char pad_A7[0xab - 0xa7];
    unsigned char unk_AB;
    unsigned char pad_AC[0xaf - 0xac];
    unsigned char unk_AF;
} UnkStruct_022a0854;

extern int func_ov095_0229bb34(void *a, void *b, unsigned char c, unsigned char d, unsigned int e, unsigned char *f);
extern void func_ov126_022a0924(void *self, unsigned char val);
extern void func_ov126_022a0978(void *self);
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern void func_ov126_022a06b4(void *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov126_022a0168(void *self);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_02051c8c_unk(void *base, unsigned char value);

void func_ov126_022a0854(UnkStruct_022a0854 *self, int arg)
{
    int diff;
    unsigned int clamp;
    unsigned char *p;
    unsigned char result;

    diff = arg - self->unk_AB;
    if (diff < 0) {
        diff = 0;
    }
    clamp = (unsigned char) diff;
    p = &result;
    self->unk_98 = func_ov095_0229bb34((char *) self + 0x19c, (char *) self + 0x4248, self->unk_A6, self->unk_AF, clamp, p);
    self->unk_98 += self->unk_AB;
    func_ov126_022a0924(self, result);
    func_ov126_022a0978(self);
}

int func_ov126_022a07e8(void *obj)
{
    int v = data_021f6c58;
    int w = data_021f6c54;

    if (w < 0x28 || w > 0x38) {
        return 0;
    }
    if (v < ((u8 *) obj)[0xab] - 0xc) {
        return 0;
    }
    if (v > ((u8 *) obj)[0xac] + 0xc) {
        return 0;
    }
    func_ov126_022a0854((UnkStruct_022a0854 *) obj, v);
    func_ov126_022a06b4(obj);
    func_ov002_02208098((void *) (obj), 1);
    func_ov095_0229b3ec((char *) obj + 0x19c);
    func_ov126_022a0168(obj);
    return 1;
}

int func_ov126_022a0768(unsigned char *self, void *p)
{
    unsigned char idx;

    if (p == 0) {
        return 0;
    }
    idx = self[0xa8];
    if (func_ov002_022088ac(p)) {
        if (idx != 0) {
            func_ov126_022a0924(self, (unsigned char) (idx - 1));
            return 1;
        }
        return 3;
    }
    if (func_ov002_0220889c(p)) {
        int limit;

        limit = func_02051c8c_unk(self + 0x4248, self[0xa6]);
        if (idx + 1 <= limit) {
            func_ov126_022a0924(self, (unsigned char) (idx + 1));
            return 1;
        }
        return 4;
    }
    if (func_ov002_022088bc(p)) {
        return 2;
    }
    return 0;
}
