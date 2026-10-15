/* func_ov110_0229d928 @ 0x0229d928, 0x20 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229c920(void *);
extern int func_ov002_02208e18(void *);

void func_ov110_0229d928(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x2344)) {
        func_ov110_0229c920(self);
    }
}
