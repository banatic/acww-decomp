/* func_ov049_02262100 @ 0x02262100, 0x58 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_02019c6c(void *p, int a, unsigned short b);
extern void *func_0201c2c8(void *p, int a);
extern void func_0201aff4(void *p, void *q);
extern int func_0203e0a8(void *p, int a);

int func_ov049_02262100(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_02019c6c((char *) self + 0x564, 1, *(unsigned short *) ((char *) self + 0x972));
        }
    }
    func_0201aff4((char *) self + 0x350, func_0201c2c8(self, 4));
    func_0203e0a8(self, 0);
    return 1;
}
