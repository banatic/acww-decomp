/* func_0205a1dc @ 0x0205a1dc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021e5a2c;
extern unsigned char data_020dd3cc[];
extern void *func_0207ce98(void *p);
extern unsigned char *func_02080a2c(void *p);
extern void func_0203d7b0(int a, unsigned char b);
extern void func_0203d79c(int a, unsigned char b);
extern int func_020644cc(int a);
extern int func_0205a240(void *data, unsigned char u, int a, int b, int c, int d);

int func_0205a1dc(int a, int b)
{
    void *p;

    p = func_0207ce98(&data_021e5a2c);
    if (p != 0) {
        func_0203d7b0(2, func_02080a2c(p)[0]);
        func_0203d79c(3, func_02080a2c(p)[1]);
        return func_0205a240(data_020dd3cc, (unsigned char) func_020644cc(3), a, b, 0, 0x1a);
    }
    return 0;
}
