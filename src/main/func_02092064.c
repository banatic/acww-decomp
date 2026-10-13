/* func_02092064 @ 0x02092064, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern int data_020e28dc;
extern int data_020e27b0;
extern void func_020920e4(void);
extern int func_0209418c(int, int, int, short *, int *, int *, void (*)(void));

int func_02092064(int a0, int a1, int a2, short *ptr)
{
    if (ptr) {
        short s = (short) (FX_Div((int) *ptr - 0x600, 0x1200));
        return func_0209418c(a0, a1, a2, &s, &data_020e28dc, &data_020e27b0, func_020920e4);
    } else {
        return 3;
    }
}
