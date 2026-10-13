/* func_02017af0 @ 0x02017af0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(int);
extern int func_02057d0c(int, int);
extern void func_02016764(int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;

void func_02017af0(char *a, int b)
{
    if (func_020164cc(b + 0x334) != 0) {
        if (func_02057d0c(2, b) != 0) {
            func_02016764(b + 0x334, b, 0, data_020c80f8, 0, 0x1000, 0, 0);
            a[0x98] = 0x13;
        }
    }
}
