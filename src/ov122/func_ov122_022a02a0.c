/* func_ov122_022a02a0 @ 0x022a02a0, 0x28 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bf48(void *);
extern int func_ov002_0220b8ac(void *, int);
extern unsigned char *func_ov122_022a0018(void *);

int func_ov122_022a02a0(void *self)
{
    int result;
    func_ov095_0229bf48((char *) self + 0xC0);
    result = func_ov002_0220b8ac((char *) self + 0x4864, 1);
    if (result) {
        return (int) func_ov122_022a0018(self);
    } else {
        return result;
    }
}
