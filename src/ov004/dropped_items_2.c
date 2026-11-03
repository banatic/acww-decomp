/* dropped_items_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02234008 @ 0x02234008, 0x1a bytes, Thumb
 * func_ov004_02233ff4 @ 0x02233ff4, 0x12 bytes, Thumb
 * func_ov004_02233fd8 @ 0x02233fd8, 0x1c bytes, Thumb
 */

extern void func_020f5958(void *);
extern void func_020f5948(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));

void *func_ov004_02234008(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x10) = 0x0;
    *(void **) (self + 0x14) = 0x0;
    func_020f5958(self + 0x4c);
    return self;
}

void *func_ov004_02233ff4(char *self)
{
    // DECLS
    // ENDDECLS
    func_020f5948(self + 0x4c);
    return self;
}

void *func_ov004_02233fd8(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0xf, 0x94, ((void (*)(void *)) func_ov004_02233ff4));
    return self;
}
