/* func_020be9f8 @ 0x020be9f8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern unsigned int func_02099194(void);
extern void func_02099188(int a, unsigned char b);

void func_020be9f8(void)
{
    int a = func_020984e8();
    unsigned int b = func_02099194();
    if (b < 16) {
        func_02099188(a, b + 1);
    }
}
