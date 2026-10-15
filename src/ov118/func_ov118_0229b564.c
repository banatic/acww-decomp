/* func_ov118_0229b564 @ 0x0229b564, 0xcc bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0209871c(void *, int);
extern int func_020988a4(void *, int);
extern int func_0207cee4(void *, int);
extern u8 data_021dc7bc[];
extern u8 data_021e5a2c[];

void func_ov118_0229b564(u8 *self)
{
    int n;
    int i;
    int j;
    int k;
    int cur;

    n = 0;
    cur = func_0209871c(data_021dc7bc, func_02099870((int) func_020984e8()));
    if (cur != -1) {
        self[0x478a] = 1;
        n++;
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && func_020988a4(data_021dc7bc, i) != 0) {
            (self + n)[0x478a] = (u8) (i + 2);
            n++;
        }
    }
    self[0xb0] = (u8) n;
    for (i = 0; i < 8; i++) {
        if (func_0207cee4(data_021e5a2c, i) != 0) {
            (self + n)[0x478a] = (u8) (i + 6);
            n++;
        }
    }
    self[0xa1] = (u8) n;
    for (; n < 13; n++) {
        (self + n)[0x4797] = 0;
    }
    k = 0;
    for (j = 0; j < 5; j++) {
        (self + k)[0x4797] = (u8) (j + 0xe);
        k++;
    }
    self[0xa2] = (u8) k;
    for (; k < 13; k++) {
        (self + k)[0x4797] = 0;
    }
}
