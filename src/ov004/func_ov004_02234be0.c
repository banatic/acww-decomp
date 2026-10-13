/* func_ov004_02234be0 @ 0x02234be0, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02234be0 {
    u8 pad_00[0x54];
    int arr[1];
};

extern int _s32_div_f(int n, int k);
extern void func_02064328(char *buf, const char *fmt, int a, int b, int c);
extern int func_02064b2c(char *buf, int h, int k, int m);
extern const char data_ov004_02255f38[];
extern const char data_ov004_02255f54[];
extern int data_021fbe94;

int func_ov004_02234be0(void *unused, struct UnkStruct_02234be0 **rp, int n, int count)
{
    char buf[28];
    volatile int t;
    volatile int j;
    int i;
    int r;

    r = _s32_div_f(n, 0xa);
    t = r;
    t = r + 0xa;
    i = 0;
    j = 0;
    while (i < count) {
        if (n < 0xa) {
            func_02064328(buf, data_ov004_02255f38, t, n, i);
        } else {
            func_02064328(buf, data_ov004_02255f54, t, n, i);
        }
        (*rp)->arr[i] = func_02064b2c(buf, data_021fbe94, 4, j);
        if ((*rp)->arr[i] == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}
