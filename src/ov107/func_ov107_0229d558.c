/* func_ov107_0229d558 @ 0x0229d558, 0x88 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(void *);
extern int func_0208e4bc(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov107_0229ce90(void *);

void func_ov107_0229d558(char *p)
{
    if (func_ov002_0220a700(p + 0x2828) != 0) {
        if (func_0208e4bc(p + 0x22B4) != 0) {
            int v4 = func_ov002_0220a6e0(p + 0x2828);
            int v6 = func_ov002_0220a768(p + 0x2828, -1);
            int v2 = func_ov002_0220a72c(p + 0x2828, -1);
            func_ov002_0220a0b4(p + 0x22B4, v4 + v6, v4 + v2);
        }
    } else {
        func_0206fc4c(0);
        p[0x8C] = 3;
        func_ov002_022080a0((void *) (p), 1);
        func_ov002_02207d24(p + 0x21CC, 1);
        func_ov107_0229ce90(p);
    }
}
