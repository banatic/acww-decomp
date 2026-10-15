/* func_ov108_0229cfc4 @ 0x0229cfc4, 0x88 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(char *);
extern int func_0208e4bc(char *);
extern int func_ov002_0220a6e0(char *);
extern int func_ov002_0220a768(char *, int);
extern int func_ov002_0220a72c(char *, int);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(char *, int);
extern void func_ov108_0229c794(char *);

void func_ov108_0229cfc4(char *p)
{
    if (func_ov002_0220a700(p + 0x2a0c) != 0) {
        if (func_0208e4bc(p + 0x2498) != 0) {
            int a = func_ov002_0220a6e0(p + 0x2a0c);
            int b = func_ov002_0220a768(p + 0x2a0c, -1);
            int c = func_ov002_0220a72c(p + 0x2a0c, -1);
            func_ov002_0220a0b4(p + 0x2498, a + b, a + c);
        }
    } else {
        func_0206fc4c(0);
        p[0x8c] = 3;
        func_ov002_022080a0((void *) (p), 1);
        func_ov002_02207d24(p + 0x23b0, 1);
        func_ov108_0229c794(p);
    }
}
