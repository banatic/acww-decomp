/* func_ov004_0223cec4 @ 0x0223cec4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea1bc(int, void *);
extern void *data_021fbe94;

int func_ov004_0223cec4(char *self, int n)
{
    if (*(void **) self == 0) {
        *(void **) self = func_020ea1bc(0x93e * n, data_021fbe94);
        return 1;
    }
    return 0;
}
