/* func_0205c704 @ 0x0205c704, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205dab8(void);
extern void func_020b65c4(void);
extern int func_020b5df8(void);
extern int func_02085f08(void);
extern int func_020ea0e0(int, int);
extern int data_021c9aec;

void func_0205c704(int arg)
{
    int acc = 0;
    int total = 0;
    int a, b;

    acc += ((func_0205dab8() + 3) & ~3);
    func_020b65c4();
    a = func_020b5df8();
    b = func_02085f08();
    acc *= (a + b);

    total += acc;
    data_021c9aec = func_020ea0e0(total, arg);
}
