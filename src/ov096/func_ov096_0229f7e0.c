/* func_ov096_0229f7e0 @ 0x0229f7e0, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f00(void *p);
extern int func_ov090_02298f84(int argument0);

void func_ov096_0229f7e0(void *p)
{
    char *base = (char *) p + 0x2500;
    int r;

    r = func_ov090_02298f84((int) func_ov002_02209f00(base));
    ((char *) p)[0xb5] = (char) (r + 0x19);
}
