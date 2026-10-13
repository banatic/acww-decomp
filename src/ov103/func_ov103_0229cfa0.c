/* func_ov103_0229cfa0 @ 0x0229cfa0, 0x20 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov103_0229cffc(int);
extern void func_ov103_0229cfc0(int);

void func_ov103_0229cfa0(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov103_0229cffc(r4);
    } else {
        func_ov103_0229cfc0(r4);
    }
}
