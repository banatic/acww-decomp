/* func_02017c18 @ 0x02017c18, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bf0(int);
extern int func_02057d0c(int, int);
extern void func_02016764(int, int, int, unsigned short, int, int, int, int);
extern unsigned short data_020c80f8;

void func_02017c18(void *a, int b)
{
    if (func_02057bf0(3) == 0) {
        if (func_02057d0c(4, b) != 0) {
            func_02016764(b + 0x334, b, 0x2d, data_020c80f8, 1, 0x1000, 0, 0);
            *((char *) a + 0x98) = 0x11;
        }
    }
}
