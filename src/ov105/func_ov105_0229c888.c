/* func_ov105_0229c888 @ 0x0229c888, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088cc(int x);
extern void func_ov002_0220a2b4(void *ptr);

void func_ov105_0229c888(void *p, int x)
{
    if (func_ov002_022088cc(x) != 0) {
        func_ov002_0220a2b4((char *) p + 0x24a4);
        *((char *) p + 0x2ba) = 0x22;
    }
}
