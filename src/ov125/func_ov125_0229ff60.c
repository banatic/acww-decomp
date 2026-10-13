/* func_ov125_0229ff60 @ 0x0229ff60, 0x20 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov125_0229fbd0(void *);
extern int func_ov002_02208e18(void *);

void func_ov125_0229ff60(void *p)
{
    if (func_ov002_02208e18((char *) p + 0x180)) {
        func_ov125_0229fbd0(p);
    }
}
