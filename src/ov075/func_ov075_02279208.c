/* func_ov075_02279208 @ 0x02279208, 0x3a bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(void *out, void *in, int a, int b);
extern int func_0201ae8c(void *ptr);

int func_ov075_02279208(void *p, int *q, int param)
{
    int local[4];
    int result = 0;

    func_0201af58(local, (char *) p + 0x5c, param, *(short *) ((char *) p + 0x94));
    if (func_0201ae8c(local) != 1) {
        q[0] = local[0];
        q[1] = local[1];
        q[2] = local[2];
        result = 1;
    }
    return result;
}
