/* func_ov068_02266d54 @ 0x02266d54, 0x54 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201ce18(void *);
extern void func_ov068_0226cfd4(void *);
extern int func_ov068_0226ccb0(void *, void *);
extern void func_ov068_0226cce8(void *, void *, int);
extern void func_ov068_0226cbf4(void *);
extern void func_0201ce5c(void *, int);
extern void func_0201ce44(void *, int);

int func_ov068_02266d54(void *self)
{
    if (func_0201ce18(self) == 0) {
        goto ret0;
    }
    func_ov068_0226cfd4(self);
    if (func_ov068_0226ccb0((char *) self + 0x8b8, self) == 0) {
        func_ov068_0226cce8((char *) self + 0x8b8, self, 0);
    }
    func_ov068_0226cbf4((char *) self + 0x8b8);
    func_0201ce5c(self, 0);
    func_0201ce44(self, 0);
    return 1;
ret0:
    return 0;
}
