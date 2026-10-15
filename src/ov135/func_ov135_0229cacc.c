/* func_ov135_0229cacc @ 0x0229cacc, 0x62 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(void *);
extern int func_0208e4bc(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov135_0229c738(void *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

void func_ov135_0229cacc(void *p)
{
    if (func_ov002_0220a700((char *) p + 0xFC)) {
        if (func_0208e4bc((char *) p + 0x98)) {
            int a = func_ov002_0220a6e0((char *) p + 0xFC);
            int b = func_ov002_0220a768((char *) p + 0xFC, -1);
            int c = func_ov002_0220a72c((char *) p + 0xFC, -1);
            p = (char *) p + 0x98;
            func_ov002_0220a0b4(p, a + b, a + c);
        }
    } else {
        func_ov135_0229c738(p);
        func_ov002_022080a0((void *) (p), 1);
    }
}
