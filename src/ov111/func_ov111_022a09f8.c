/* func_ov111_022a09f8 @ 0x022a09f8, 0x64 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022a09f8 {
    u8 pad_00[0x8c];
    u8 byte;
};

extern void *func_020ee45c(struct UnkStruct_022a09f8 *a, int b, int c);
extern void func_ov090_022993cc(void *p, u8 b);
extern void func_ov111_0229f1d8(struct UnkStruct_022a09f8 *a);
extern void func_ov002_022080a0(struct UnkStruct_022a09f8 *a, int b);
extern void func_ov111_0229efc8(struct UnkStruct_022a09f8 *a, int b);
extern void func_0206f4f4(char *p);
extern void func_0206f4e4(void);

int func_ov111_022a09f8(struct UnkStruct_022a09f8 *a, int b, int c)
{
    void *p = func_020ee45c(a, b, c);
    if (b != -1 && b != 4) {
        func_ov090_022993cc(p, (u8) b);
        func_ov111_0229f1d8(a);
        a->byte = 4;
        func_ov002_022080a0(a, 1);
        if (b == 7) {
            func_ov111_0229efc8(a, 0x10);
        }
        if (c != 0) {
            func_0206f4f4((char *) a + 0x3d16);
        } else {
            func_0206f4e4();
        }
        return 1;
    }
    return 0;
}
