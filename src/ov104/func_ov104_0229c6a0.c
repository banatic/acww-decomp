/* func_ov104_0229c6a0 @ 0x0229c6a0, 0x13c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229c6a0 {
    unsigned char pad_00[0x100];
};
struct UnkStruct_0229c6a0_2 {
    unsigned char pad_00[0x20];
};
extern int func_020978bc(struct UnkStruct_0229c6a0 *, int);
extern int func_02065e9c(struct UnkStruct_0229c6a0 *);
extern int func_02097958(struct UnkStruct_0229c6a0 *);
extern int func_02097a74(struct UnkStruct_0229c6a0 *, int, int);
extern void func_02066650(struct UnkStruct_0229c6a0 *);
extern int func_02097900(struct UnkStruct_0229c6a0 *);
extern void func_02097a44(struct UnkStruct_0229c6a0 *);
extern int func_020682e0(int);
extern void *func_02094fd4(struct UnkStruct_0229c6a0_2 *);
extern int func_02098844(void *, int);
extern int func_02099870(int);
extern void *func_02095074(int, struct UnkStruct_0229c6a0_2 *);
extern void func_02068404(int, int, struct UnkStruct_0229c6a0_2 *);
extern void *func_02094fbc(struct UnkStruct_0229c6a0_2 *);
extern void *data_021dc7bc;
u16 func_ov104_0229c6a0(int unused, struct UnkStruct_0229c6a0 *p)
{
    struct UnkStruct_0229c6a0_2 buf;
    u16 ret;
    int n;
    int mask;
    int obj;
    int idx;
    volatile int zero;
    int count;
    int i;
    int j;
    int k;
    ret = 0;
    n = func_020978bc(p, 10);
    if (n == 0) {
        return ret;
    }
    mask = 0;
    count = 0;
    i = 0;
    for (i = 0; i < n; i++) {
        if (func_02065e9c(p) == 0) {
            idx = func_02097958(p);
            if ((idx != (~1)) & 0xFFFFFFFFFFFFFFFFu) {
                if (idx != (~0)) {
                    if (func_02097a74(p, idx, 1)) {
                        func_02066650(p);
                        ret = (u16) (ret | 0x200);
                    } else if ((mask & (1 << idx)) == 0) {
                        mask = mask | (1 << idx);
                        count++;
                    }
                } else if (func_02097900(p) >= 0) {
                    func_02097a44(p);
                    func_02066650(p);
                    ret = (u16) (ret | 0x200);
                }
            }
        }
        p = (struct UnkStruct_0229c6a0 *) (((char *) p) + 0x100);
    }

    if (count != 0) {
        j = 0;
        obj = func_020682e0(j);
        func_02094fd4(&buf);
        for (k = j; k < 4; k++) {
            if (mask & (1 << k)) {
                func_02095074(func_02099870(func_02098844(&data_021dc7bc, k)), &buf);
                switch (j) {
                    case 0:
                        func_02068404(obj, 7, &buf);
                        break;

                    case 1:
                        func_02068404(obj, 8, &buf);
                        break;

                    case 2:
                        func_02068404(obj, 9, &buf);
                        break;
                }

                j++;
            }
        }

        ret = (u16) (ret | (count << 6));
        func_02094fbc(&buf);
    }
    return ret;
}
