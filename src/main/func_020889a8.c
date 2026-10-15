/* func_020889a8 @ 0x020889a8, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern void func_02066694(void *);
extern int func_020644cc(int);
extern void func_0209df64(void *);
extern int func_0209767c(int, int);
extern int func_02099870(void *);
extern void func_02066024(void *, void *, void *, void *, void *, int);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern unsigned short func_02065ed0(void *, int, int);
extern void func_02063cc8(void *);
extern int func_020979f0(void *, int);
extern void func_02098fd0(void *, int);
extern void func_02066688(void *);
extern char data_020e1ff0[];
extern char data_020e1f58[];

void func_020889a8(void)
{
    void *p;
    unsigned char a[8];
    unsigned char c[0x10c];
    int v;

    p = func_020984e8();
    if (p == 0) {
        return;
    }
    if (func_02099020(p, 0x36) == 0) {
        return;
    }

    func_02066694(&c[8]);

    a[0] = 0;
    a[0] = (unsigned char) func_020644cc(3);
    func_0209df64(&a[4]);
    a[1] = (unsigned char) func_0209767c(3, a[5]);

    v = func_02099870(p);

    func_02066024(&c[8], a, data_020e1ff0, data_020e1f58, &a[1], v);
    func_02063ccc(c, 0, 0x1b);
    func_020638d4(&a[2], c, 0, 0, 1, 1, 0);
    func_02065ed0(&c[8], *(unsigned short *) &a[2], 1);
    func_02063cc8(c);

    if (func_020979f0(&c[8], 0) != 0) {
        func_02098fd0(p, 0x36);
    }

    func_02066688(&c[8]);
}
