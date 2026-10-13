/* func_ov068_022766b0 @ 0x022766b0, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e364(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov068_022761d0(void *a, void *b);
extern void *data_ov068_022788ec;

int func_ov068_022766b0(void *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    data_ov068_022788ec = self;
    func_0201c280(self, (char *) self + 0x89c);
    func_ov068_022761d0((char *) self + 0x89c, self);
    return 1;
}
