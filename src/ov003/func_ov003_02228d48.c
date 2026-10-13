/* func_ov003_02228d48 @ 0x02228d48, 0xb4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_0225f76c[];
extern char data_ov003_0225f4dc[];
extern void func_0209129c(int h);
extern void func_020604fc(int v, int z);

void func_ov003_02228d48(void *unused, int i)
{
    if (i >= 0 && i < 6) {
        char *rec = data_ov003_0225f76c + i * 0x24c;
        int *sl;
        int v;
        *(int *) (rec + 0x80) = 0;
        func_0209129c(*(int *) (rec + 0x204));
        *(int *) (rec + 0x204) = -1;
        if (*(u8 *) (rec + 0x1fc) == 0) {
            *(u8 *) (rec + 0x1fc) = 3;
        } else if (*(u8 *) (rec + 0x1fc) == 1) {
            *(u8 *) (rec + 0x1fc) = 4;
        }
        sl = (int *) (rec + 0x208);
        sl[0] = i;
        sl[1] = 0;
        v = *(int *) (rec + 0x22c);
        if (v != 0) {
            if (*(int *) (data_ov003_0225f4dc + *(s8 *) (rec + 0x227) * 0xa4 + 0x40) != 1) {
                func_020604fc(v, 0);
                *(int *) (rec + 0x22c) = 0;
                *(s8 *) (rec + 0x227) = -1;
                *(u8 *) (rec + 0x23c) = 0;
            }
            *(u8 *) (rec + 0x224) = 0;
        }
    }
}
