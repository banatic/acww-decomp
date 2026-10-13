/* func_ov004_0221124c @ 0x0221124c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220cdd8(void *self, int k);

int func_ov004_0221124c(void *self)
{
    if (func_ov004_0220cdd8(self, 0) == 0 && func_ov004_0220cdd8(self, 5) == 0 && *(int *) ((char *) self + 0x780) == 0x10) {
        return 1;
    }
    return 0;
}
