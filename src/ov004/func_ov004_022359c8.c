/* func_ov004_022359c8 @ 0x022359c8, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_022359c8(char *a, char **bp)
{
    if (*(int *) (a + 0x1cc) < *(int *) (*bp + 0x1cc)) {
        *(a + 0x1ca) = -1;
        if (*(unsigned char *) (*bp + 0x1c9) == 0) {
            *(*bp + 0x1ca) = 1;
        }
    } else {
        *(a + 0x1ca) = 1;
        if (*(unsigned char *) (*bp + 0x1c9) == 0) {
            *(*bp + 0x1ca) = -1;
        }
    }
}
