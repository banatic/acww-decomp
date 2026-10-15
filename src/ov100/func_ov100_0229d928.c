/* func_ov100_0229d928 @ 0x0229d928, 0x40 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov100_0229cc3c(void *);

void func_ov100_0229d928(unsigned char *p)
{
    if (p[0x2928] != 0) {
        p[0x2928] = p[0x2928] - 1;
        return;
    }
    p[0x8c] = 4;
    func_ov002_022080a0((void *) (p), 1);
    func_ov002_02207d24(p + 0x218c, 0);
    func_ov100_0229cc3c(p);
}
