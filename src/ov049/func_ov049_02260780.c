/* func_ov049_02260780 @ 0x02260780, 0x2c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_0206fc8c(void);
extern int func_020996b8(int a);
extern int func_02072bb0(int a, int b);
extern int func_02072d4c(int a);
extern void func_02072e18(unsigned char *record, int value);

void func_ov049_02260780(int a, int b)
{
    int t1 = func_020984e8();
    int t2 = func_0206fc8c();
    unsigned char *record = (unsigned char *) func_02072d4c(func_02072bb0(func_020996b8(t1), t2));
    func_02072e18(record, b);
}
