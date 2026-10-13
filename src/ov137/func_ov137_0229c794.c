/* func_ov137_0229c794 @ 0x0229c794, 0x44 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov137_0229c574(void *p, int a);
extern void *func_ov134_022999e0(void *p);
extern void *func_ov002_0220a768(void *p, int a);
extern void *data_ov137_0229d368[];

void *func_ov137_0229c794(void *p)
{
    unsigned char v;

    if (func_ov137_0229c574(p, 2)) {
        return func_ov134_022999e0((char *) p + 0x2c4);
    }

    v = *(unsigned char *) ((char *) p + 0x2b77);
    if (v == 2) {
        p = (char *) p + 0xf8;
        return func_ov002_0220a768(p, 6);
    }

    return data_ov137_0229d368[v];
}
