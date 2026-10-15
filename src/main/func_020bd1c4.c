/* func_020bd1c4 @ 0x020bd1c4, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020bd1c4 {
    u8 pad_00[0x1464];
    int unk_1464;
    u8 pad_1468[0x2f18 - 0x1468];
    u8 unk_2F18;
    u8 pad_2F19[1];
    u8 unk_2F1A;
    u8 pad_2F1B[0x2f25 - 0x2f1b];
    u8 unk_2F25;
    u8 unk_2F26;
};

struct UnkStruct_020bd1c4_2 {
    int x;
    int y;
};
struct UnkStruct_020bd1c4_3 {
    u8 pad_00[0x64];
    int unk_64;
};

extern int data_021dc7a8[];
extern struct UnkStruct_020bd1c4_3 *data_020ccf94;
extern int func_0209f150(void *, int);
extern void func_0209e474(struct UnkStruct_020bd1c4_2 *);
extern void MI_CpuCopy8(struct UnkStruct_020bd1c4_2 *, struct UnkStruct_020bd1c4_2 *, u32);
extern int func_0203fc78(int, struct UnkStruct_020bd1c4_2 *, int);
extern int func_02073dd4(struct UnkStruct_020bd1c4_3 *, int);
extern int func_0208602c(void);
extern int func_020860bc(int);
extern int func_02087b1c(void *);
extern int func_020644cc(int);
extern void *func_020bdc50(struct UnkStruct_020bd1c4 *, int, int, int, int);

void func_020bd1c4(struct UnkStruct_020bd1c4 *p)
{
    struct UnkStruct_020bd1c4_2 a;
    struct UnkStruct_020bd1c4_2 b;
    int t;
    int v;
    int rem;
    int c;

    if (p->unk_2F26) {
        if (func_0209f150(data_021dc7a8, 9)) {
            p->unk_2F26 = 0;
        } else {
            a.x = 0;
            a.y = 0;
            func_0209e474(&a);
            MI_CpuCopy8(&a, &b, 8);
            t = func_0203fc78(0x44, &b, 0) ? 0 : 1;
            if (t) {
                p->unk_2F26 = 0;
            }
        }
    }
    if (p->unk_2F26) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
            v = p->unk_2F18;
            rem = (unsigned int) v % 10;
            if (p->unk_2F1A != v) {
                if (rem == 2 || rem == 7) {
                    if (func_02087b1c((void *) func_020860bc((int) func_0208602c())) == 0) {
                        if (p->unk_1464 != 6) {
                            if (p->unk_2F25 == 0) {
                                p->unk_2F25 = func_020644cc(8) + 1;
                            }
                            c = p->unk_2F25;
                            if (func_020644cc(8) < c) {
                                func_020bdc50(p, 6, 0x2d, 0, 0);
                                p->unk_2F25 = 1;
                            } else if (c < 8U) {
                                p->unk_2F25++;
                            }
                        }
                    }
                }
            }
        }
    }
}
