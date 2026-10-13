/* func_ov146_02299af4 @ 0x02299af4, 0x28 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_02299b58(void *self);
extern void *_s32_div_f(int size, int align);

void func_ov146_02299af4(void *self)
{
    int index;
    void *ptr;

    index = *(int *) ((char *) self + 0xa4);
    ptr = _s32_div_f(index * 0x50, 0x1a0);
    *(void **) ((char *) self + 0x98) = ptr;
    func_ov146_02299b58(self);
}
