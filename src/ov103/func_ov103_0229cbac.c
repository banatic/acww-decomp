/* func_ov103_0229cbac @ 0x0229cbac, 0x40 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(int arg0, unsigned int arg1);
extern int func_ov103_0229cde8(int, int);
extern void func_ov103_0229cbec(int);
extern void func_ov094_0229b950(int, int);
extern void func_ov094_0229ab5c(int);

void func_ov103_0229cbac(int param1, int param2)
{
    int r4 = param1;
    int r5 = param2;
    int result;

    if (func_ov103_0229cdfc(param1, param2) != 0) {
        result = func_ov103_0229cde8(r4, r5);
        func_ov094_0229b950(r4 + 0xb2c, result);
        func_ov094_0229ab5c(r4 + 0xcc);
    } else {
        func_ov103_0229cbec(r4);
    }
}
