/* func_ov004_0221bfd4 @ 0x0221bfd4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202de4c();
extern void func_0202e5e0();
extern void func_020edf54();
extern void *data_ov004_022535e4;
extern void *data_ov004_02253674;

void *func_ov004_0221bfd4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02253674;
    *(void **) (self + 0x8a0) = &data_ov004_022535e4;
    func_0202de4c(self + 0x8a0);
    func_0202e5e0(self);
    func_020edf54(self);
    return self;
}
