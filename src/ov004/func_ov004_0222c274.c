/* func_ov004_0222c274 @ 0x0222c274, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int a);

int func_ov004_0222c274(int *out, int id, int kind)
{
    char *p = (char *) func_02096718(id);
    if (p != 0) {
        if (*(int *) (p + 0x7f0) == kind) {
            int *q = (int *) (p + 0x5c);
            out[0] = *(int *) (p + 0x5c);
            out[1] = q[1];
            out[2] = q[2];
            return 1;
        }
    }
    return 0;
}
