/* func_ov004_02243c30 @ 0x02243c30, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02245188(void *self);
extern int func_ov004_022447c0(int a, void *p);
extern int func_020644cc(int k);
extern void func_ov004_02244f48(void *a, void *b, int c, int d);
extern int func_0200322c(void *a, void *b);

void *func_ov004_02243c30(void *self, short *out)
{
    void *p = func_ov004_02245188(self);
    int t;
    short m;
    if (p != 0) {
        *(short *) ((char *) self + 0xac) = (short) func_ov004_022447c0(*(short *) ((char *) self + 0x192), p);
        m = *(short *) ((char *) self + 0xac);
        t = func_020644cc(3);
        func_ov004_02244f48((char *) self + 0x34, (char *) self + 0x2c8, m, (*((unsigned char *) self + 0xa4) + t) << 12);
        *(short *) ((char *) self + 0xac) = (short) func_0200322c((char *) self + 0x2c8, (char *) self + 0x34);
        *(short *) ((char *) self + 0x172) = 0xf;
        *(int *) ((char *) self + 0x4c) += 1;
        *out = 0;
    }
    return p;
}
