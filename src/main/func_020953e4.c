/* func_020953e4 @ 0x020953e4, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct ThreeInts {
    int a;
    int b;
    int c;
};

struct UnkStruct_020953e4 {
    char pad_00[0x68];
    int unk_68;
};

extern char *func_02096718(int arg);
extern void func_0200fa1c(struct ThreeInts *out, char *unused, struct ThreeInts *in, u16 *p, int *q);
extern int func_020b67d4(void);
extern int func_ov004_0223bbc0(int *a, int *b, int c, int d);
extern int func_0204f5a8(u32 a, struct ThreeInts *b, u32 c);
extern int func_0204f260(u32 a, struct ThreeInts *b);

extern int data_020e2f7c[];
extern u8 data_020e54a8;
extern struct UnkStruct_020953e4 *data_020ccf94;
extern u32 data_021c80bc;

int func_020953e4(void)
{
    struct ThreeInts out;
    int a4;
    int a8;
    char *base = func_02096718(4);
    int ret = 0;

    if (base == 0) {
        return ret;
    }
    if (*(u32 *) ((char *) base + 0x7f0) != 2) {
        return ret;
    }
    func_0200fa1c(&out, base, (struct ThreeInts *) (base + 0x5c), (u16 *) (base + 0x8e), data_020e2f7c);
    {
        unsigned int cond = (data_020e54a8 == 1);
        if (cond != 0) {
            if (func_020b67d4() != 0) {
                if (data_020ccf94->unk_68 == 0) {
                    if (func_ov004_0223bbc0(&a4, &a8, 0, 0) < 0) {
                        ret = func_0204f5a8(data_021c80bc, &out, 0);
                    }
                }
            }
        } else {
            u32 v = data_021c80bc;
            if (func_0204f260(v, &out) != 0) {
                return 0;
            }
            ret = func_0204f5a8(v, &out, 0);
        }
    }
    return ret;
}
