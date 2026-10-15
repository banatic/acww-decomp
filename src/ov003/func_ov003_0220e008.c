/* func_ov003_0220e008 @ 0x0220e008, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *, int b, int c, unsigned short d);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);
extern void func_0200f268(void *, int);
extern void func_02035638(int);
extern void func_02035684(int, int, int);

void func_ov003_0220e008(void *param, void *message, int previous)
{
    func_020109a0(param, 0x71, 3, 0);
    ((unsigned char *) param)[0x7d4] = 0;
    if (func_0200fbe0(param) == 3) {
        func_0205eae0((char *) param + 0x5a0, 0x13, 3, 0);
    }
    func_0200f268(param, 0x1a);
    func_02035638(0x3f);
    func_02035684(0x19, 0xf, 0);
}
