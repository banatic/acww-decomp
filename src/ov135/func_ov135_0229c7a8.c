/* func_ov135_0229c7a8 @ 0x0229c7a8, 0x54 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov135_0229c574(void *, int);
extern void *func_ov134_022999e0(void *);
extern void *func_ov002_0220a768(void *, int);
extern void *data_ov135_0229d51c[];

void *func_ov135_0229c7a8(void *self)
{
    unsigned char v;

    if (func_ov135_0229c574(self, 2)) {
        return func_ov134_022999e0((char *) self + 0x2c8);
    }
    v = *(unsigned char *) ((char *) self + 0x95);
    switch (v) {
        case 5:
            return func_ov002_0220a768((char *) self + 0xfc, 6);
        case 6:
            return func_ov002_0220a768((char *) self + 0xfc, 7);
        default:
            return data_ov135_0229d51c[v];
    }
}
