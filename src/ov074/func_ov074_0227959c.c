/* func_ov074_0227959c @ 0x0227959c, 0x3a bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201af58(void *dst, void *src, int a3, int a4);
extern int func_0201ae8c(void *src);

int func_ov074_0227959c(void *obj, int *out, int a3)
{
    int local[4];
    int result = 0;
    func_0201af58(local, (char *) obj + 0x5C, a3, *(signed short *) ((char *) obj + 0x94));
    if (func_0201ae8c(local) != 1) {
        out[0] = local[0];
        out[1] = local[1];
        out[2] = local[2];
        result = 1;
    }
    return result;
}
