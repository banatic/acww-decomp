/* func_ov112_022a15a0 @ 0x022a15a0, 0x5e bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xa0];
    u32 unk_A0;
    u32 pad_A4;
    u32 unk_A8;
} UnkStruct_022a15a0;

extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov112_0229f6e4(void *p);
extern int func_ov112_0229fefc(void *p);
extern void func_ov112_0229fd20(void *p);
extern void func_ov112_022a122c(void *p);
extern void func_ov112_0229fe60(void *p, int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov112_022a15a0(UnkStruct_022a15a0 *p)
{
    int zero = 0;

    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov112_0229f6e4(p);
        func_ov002_022080a0(p, 2);
        func_ov112_0229fefc(p);
        func_ov112_0229fd20(p);
        func_ov112_022a122c(p);
        func_ov112_0229fe60(p, 0x80);
    }

    func_ov002_02207e80(p, 6, zero, zero);
    p->unk_A0 = func_ov002_02207f60(p);
    p->unk_A8 = p->unk_A0;
}
