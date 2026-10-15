/* func_ov068_02274734 @ 0x02274734, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_020960f8(int, int);
extern int func_ov004_0222c070(int);
extern void func_02035624(int);
extern void func_020355cc(void);
extern int func_0203b144(void);
extern void func_ov068_022749dc(void *, int);

int func_ov068_02274734(char *self)
{
    if (func_02014868(self + 0x618)) {
        return 1;
    }
    if (!func_02014868(self + 0x618)) {
        func_0203e020(self);
        if (func_020960f8(0x28, 4)) {
            func_ov004_0222c070(0);
        }
        func_02035624(0x10);
        func_020355cc();
        func_0203b144();
        func_ov068_022749dc(self, 4);
    }
    return 1;
}
