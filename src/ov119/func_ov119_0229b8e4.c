/* func_ov119_0229b8e4 @ 0x0229b8e4, 0x4c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *addr);
extern int func_ov002_02208ad8(void *addr, unsigned char byte);
extern int func_ov002_0220a08c(void *addr, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *addr, unsigned char value);

void func_ov119_0229b8e4(unsigned char *p)
{
    volatile int unused;
    int v1;
    int v2;

    v1 = func_ov002_02208ae4((void *) (p + 0xDC));
    v2 = func_ov002_02208ad8((void *) (p + 0xDC), p[0xAE]);
    func_ov002_0220a08c((void *) (p + 0xDA8), v1, v2, 2);
    p[0x9F] = p[0x8D];
    func_ov002_02208098(p, 3);
}
