/* func_0201d398 @ 0x0201d398, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *p);
extern unsigned char *func_020992e4(void *p);
extern unsigned char func_02082274(unsigned char a, unsigned char b);
extern void func_02015ed0(void *p, unsigned char b, int c);
extern void func_02015ea0(void *p, unsigned char b, int c);
extern void func_02015dd4(void *p, int a, void *b, void *c, void *d);
extern char data_020d9f48;

void func_0201d398(void *arg0)
{
    unsigned char *q;
    unsigned char x;
    unsigned char buf[2];

    q = func_020992e4(func_020984e8(arg0));
    x = func_02082274(q[1], q[0]);
    func_02015ed0(arg0, q[1], 0);
    func_02015ea0(arg0, q[0], 1);
    buf[0] = x;
    buf[1] = 0;
    func_02015dd4(arg0, 2, buf, &data_020d9f48, &buf[1]);
}
