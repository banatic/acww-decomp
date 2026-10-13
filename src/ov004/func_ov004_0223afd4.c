/* func_ov004_0223afd4 @ 0x0223afd4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea0e0(int, void *);
extern void *data_021fbe94;

int func_ov004_0223afd4(char *self)
{
    if (*(void **) (self + 0x10) == 0) {
        *(void **) (self + 0x10) = func_020ea0e0(0x2800, data_021fbe94);
        if (*(void **) (self + 0x10) != 0) {
            return 1;
        }
    }
    return 0;
}
