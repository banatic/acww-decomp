/* func_ov004_02221bf8 @ 0x02221bf8, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202de4c();
extern void func_0202e5e0();
extern void func_02084f84();
extern void func_020edf54();
extern void *data_ov004_02254148;
extern void *data_ov004_022541d8;

void *func_ov004_02221bf8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022541d8;
    func_02084f84(self + 0xa54);
    *(void **) (self + 0x8a0) = &data_ov004_02254148;
    func_0202de4c(self + 0x8a0);
    func_0202e5e0(self);
    func_020edf54(self);
    return self;
}
