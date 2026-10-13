/* func_ov084_022791b4 @ 0x022791b4, 0x30 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *self);
extern void func_0201c280(void *a, void *b);
extern void func_ov084_02278f60(void *a, void *b);

int func_ov084_022791b4(void *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov084_02278f60((char *) self + 0x658, self);
    return 1;
}
