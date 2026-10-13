/* func_020885d8 @ 0x020885d8, 0x14c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 w1;
} Key;

extern int func_0209de44(u8 a, u8 b, u32 c, u8 d);
extern int func_0209e380(void *k1, void *k2);
extern void func_0209e29c(void *k, int ptr);

extern u8 data_020d0704[];
extern u8 data_020d07a4[];

int func_020885d8(int a0, u8 a1, u8 a2, u8 *out)
{
    int r4;
    int r7;
    int r6;
    u8 byte1;
    u8 entry0;
    u32 word;
    int i;
    int ptr;
    u8 *row1;
    u8 *row2;
    u8 *row3;
    Key k1;
    Key k2;
    int res;
    int diff;

    k1.unk_00 = 0;
    k1.w1 = 0;
    ((u8 *) &k1)[5] = a0;
    ((u8 *) &k1)[4] = a1;
    ((u8 *) &k1)[3] = a2;

    for (r4 = a0 - 1; r4 <= a0; r4++) {
        if (r4 >= 0) {
            for (r7 = 0; r7 < 4; r7++) {
                for (r6 = 0, row1 = data_020d0704 + r7 * 0x28, row2 = data_020d07a4 + r7 * 0x8c; r6 < 5; r6++) {
                    u8 *entry = row1 + (r6 << 3);
                    entry0 = entry[0];
                    if (entry0 != 0) {
                        byte1 = entry[1];
                        word = *(u32 *) (entry + 4);
                        while (1) {
                            res = func_0209de44((u8) r4, entry0, word, byte1);
                            if (res != -1) {
                                break;
                            }
                            byte1 = (u8) (byte1 - 1);
                        }

                        k2.unk_00 = 0;
                        k2.w1 = 0;
                        ((u8 *) &k2)[5] = r4;
                        ((u8 *) &k2)[4] = entry0;
                        ((u8 *) &k2)[3] = res;

                        for (i = 0, row3 = row2 + r6 * 0x1c; i < 7; i++) {
                            ptr = *(int *) (row3 + (i << 2));
                            if (ptr != 0) {
                                diff = func_0209e380(&k1, &k2);
                                if (diff == 0) {
                                    diff = -func_0209e380(&k2, &k1);
                                }
                                if (diff + ptr > 0 && diff <= 0) {
                                    *out = (*out & ~3) | ((u8) r7 & 3);
                                    *out = (*out & ~0x1c) | (((u8) r6 & 7) << 2);
                                    *out = (*out & ~0xe0) | (((u8) i & 7) << 5);
                                    return 1;
                                }
                                func_0209e29c(&k2, ptr);
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
