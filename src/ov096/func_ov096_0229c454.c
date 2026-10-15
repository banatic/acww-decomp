/* func_ov096_0229c454 @ 0x0229c454, 0x88 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229c4dc(void *);
extern unsigned short func_ov096_0229f0dc(void *, unsigned char);
extern int func_0204bd5c(short *);
extern void func_020665f0(int, unsigned char);
extern int func_ov002_02208a24(void *, int, unsigned char);
extern void func_0206fcb0(int);
extern int func_ov096_022a18dc(void *, int);
extern void func_ov096_022a1540(void *);
extern unsigned int func_0204bd40(short *);
extern int func_0204bd20(int, int);
extern void func_ov096_0229f5e0(void *, unsigned char, int, int);

void func_ov096_0229c454(void *p)
{
    int r4;
    short s;
    int r6;
    unsigned int cond;
    int r2;

    r4 = func_ov096_0229c4dc(p);
    s = func_ov096_0229f0dc(p, *(unsigned char *) ((char *) p + 0xB8));
    r6 = func_0204bd5c(&s);
    func_020665f0(r4, (unsigned char) r6);
    func_ov002_02208a24((char *) p + 0x2564, r4, *(unsigned char *) ((char *) p + 0xBE));
    func_0206fcb0(r4);
    func_ov096_022a18dc(p, 8);
    func_ov096_022a1540(p);
    cond = func_0204bd40(&s);
    if (cond <= 1) {
        r2 = 0xFFF1;
    } else {
        r2 = func_0204bd20(r6, cond - 1);
    }
    func_ov096_0229f5e0(p, *(unsigned char *) ((char *) p + 0xB8), r2, 0);
}
