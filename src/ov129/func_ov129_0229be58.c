/* func_ov129_0229be58 @ 0x0229be58, 0x24 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229be7c(void *p0, int p1, int p2);

void func_ov129_0229be58(void *obj, unsigned short val, int param)
{
    unsigned char *q = (unsigned char *) obj + 0x2f98 + val;
    if (*q != 0) {
        return;
    }
    if (func_ov129_0229be7c(obj, val, param) != 0) {
        return;
    }
    *q = 3;
}
