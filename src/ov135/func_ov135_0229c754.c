/* func_ov135_0229c754 @ 0x0229c754, 0x54 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov135_0229c574(void *, int);
extern void *func_ov134_022999ac(void *);
extern void *func_ov002_0220a72c(void *, int);
extern void *data_ov135_0229d538[];

void *func_ov135_0229c754(void *self)
{
    unsigned char v;

    if (func_ov135_0229c574(self, 2)) {
        return func_ov134_022999ac((char *) self + 0x2c8);
    }
    v = *(unsigned char *) ((char *) self + 0x95);
    switch (v) {
        case 5:
            return func_ov002_0220a72c((char *) self + 0xfc, 6);
        case 6:
            return func_ov002_0220a72c((char *) self + 0xfc, 7);
        default:
            return data_ov135_0229d538[v];
    }
}
