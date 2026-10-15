/* func_ov066_022668c4 @ 0x022668c4, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int (*data_ov066_0226bde4)(int);

void func_ov066_022668c4(void *p)
{
    if (data_ov066_0226bde4 == 0) {
        return;
    }
    if (p == 0) {
        return;
    }
    data_ov066_0226bde4((int) p);
}
