/* func_ov111_0229f9d4 @ 0x0229f9d4, 0x26 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229f9fc(void);
extern void func_ov111_0229f524(int);
extern void func_ov111_0229fd08(int);
extern void func_ov111_0229f854(int);

void func_ov111_0229f9d4(int r0)
{
    int r4 = r0;
    if (func_ov111_0229f9fc() != 0) {
        func_ov111_0229f524(r4);
        func_ov111_0229fd08(r4);
    } else {
        func_ov111_0229f854(r4);
    }
}
