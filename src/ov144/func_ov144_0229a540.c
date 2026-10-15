/* func_ov144_0229a540 @ 0x0229a540, 0x48 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a58c(void *, int arg1, int arg2);
extern void func_ov002_0220a574(void *);

int func_ov144_0229a540(void *self, int a2, int a3)
{
    int result;
    int *p;
    int *q;

    if (func_ov002_0220a58c((char *) self + 0x128, a2, a3)) {
        p = (int *) ((char *) self + 0xa8);
        *((int *) ((char *) self + 0xac)) = *p - a3;
        func_ov002_0220a574((char *) self + 0x128);
        q = (int *) ((char *) self + 0xa8);
        *((int *) ((char *) self + 0xb0)) = *q;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
