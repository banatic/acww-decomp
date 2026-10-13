/* func_0202bd40 @ 0x0202bd40, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_020808b0(unsigned char *arg);
extern void func_02015dd4(int a, int b, unsigned char *c, unsigned char *d, unsigned char *e);
extern unsigned char data_020d9fb4[];

void func_0202bd40(int arg0, int arg1, unsigned char *arg2)
{
    unsigned char *p = func_020808b0(arg2);
    if (p) {
        unsigned char buf[2];
        buf[0] = *p;
        buf[1] = 0;
        func_02015dd4(arg0, arg1, buf, data_020d9fb4, &buf[1]);
    }
}
