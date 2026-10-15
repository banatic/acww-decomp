/* func_0209a050 @ 0x0209a050, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02098f70(int index);
extern int func_02099734(int a);
extern int func_02098f0c(int a, void *b, int index, int d);

void func_0209a050(int index)
{
    int a;
    unsigned short b;

    a = func_020984e8();
    if (func_02098f70(index)) {
        b = 0xfff1;
        func_02098f0c(func_02099734(a), &b, index, 0);
    }
}
