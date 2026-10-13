/* func_020972b4 @ 0x020972b4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020972f0(unsigned char);
extern int func_020972e4(unsigned char);
extern void func_02097204(int, int);

void func_020972b4(int param)
{
    int i;
    for (i = 1; i <= 12; i++) {
        if (i == param) {
            continue;
        }
        func_02097204(func_020972f0((unsigned char) i), func_020972e4((unsigned char) i));
    }
}
