/* func_ov106_0229dd44 @ 0x0229dd44, 0x20 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e18(void *);
extern void func_ov106_0229c910(void *);

void func_ov106_0229dd44(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x2304) != 0) {
        func_ov106_0229c910(self);
    }
}
