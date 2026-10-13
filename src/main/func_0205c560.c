/* func_0205c560 @ 0x0205c560, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f644(void);
extern void func_020b65c4(void);
extern int func_020b5df8(void);
extern int func_02085f08(void);
extern int func_020ea0e0(int, int);
extern int data_021c9ad8;

void func_0205c560(int arg)
{
    int acc = 0;
    int total = 0;
    int a, b;

    acc += ((func_0205f644() + 3) & ~3);
    func_020b65c4();
    a = func_020b5df8();
    b = func_02085f08();
    acc *= (a + b);

    total += acc;
    data_021c9ad8 = func_020ea0e0(total, arg);
}
