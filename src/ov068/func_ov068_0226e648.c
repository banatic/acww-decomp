/* func_ov068_0226e648 @ 0x0226e648, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de8(const void *);
extern int func_020e8858(const void *);
extern int func_0203e020(const void *);
extern int func_020984e8(void);
extern void func_020a128c(void);

int func_ov068_0226e648(char *p)
{
    if (func_02019de8(p + 0x564) != 0 || func_020e8858(p + 0x724) == 0) {
        int r = func_0203e020(p);
        if (func_020984e8() != 0) {
            func_020a128c();
        }
    }
    return 1;
}
