/* func_ov068_0226c7bc @ 0x0226c7bc, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226c820(void *a, void *b, void *c);
extern void func_020eaca0(void *a, void *unused1, void *unused2);

int func_ov068_0226c7bc(void *a, void *b, void *c)
{
    char sp[12];
    func_020eaca0(sp, b, c);
    return func_ov068_0226c820(a, c, sp);
}
