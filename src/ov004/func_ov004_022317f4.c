/* func_ov004_022317f4 @ 0x022317f4, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020324c4(void *);
extern void func_02066994(void *);
extern void func_020b7f60(void *);
extern void func_020b82d0(void *);
extern void func_020edf54(void *);
extern void func_ov004_0222c7a0(void *);
extern void *data_ov004_022558f8;
extern void *data_ov004_02255974;

void *func_ov004_022317f4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022558f8;
    *(void **) (self + 0x290) = &data_ov004_02255974;
    func_020b7f60(self + 0x61c);
    func_020b82d0(self + 0x374);
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
