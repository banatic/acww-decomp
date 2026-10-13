/* func_ov068_02266cf4 @ 0x02266cf4, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201cc48(void *);
extern int func_ov068_0226ccb0(void *, void *);
extern void func_ov068_0226cce8(void *, void *, int);
extern void func_0201ce5c(void *, int);
extern void func_0201ce44(void *, int);
extern void func_ov068_0226cbf4(void *);

void func_ov068_02266cf4(void *self)
{
    func_0201cc48((char *) self + 0x83c);
    if (func_ov068_0226ccb0((char *) self + 0x8b8, self) == 0) {
        func_ov068_0226cce8((char *) self + 0x8b8, self, 0);
    }
    func_0201ce5c(self, 0);
    func_0201ce44(self, 0);
    func_ov068_0226cbf4((char *) self + 0x8b8);
}
