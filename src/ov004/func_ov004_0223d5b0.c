/* func_ov004_0223d5b0 @ 0x0223d5b0, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern void *func_ov004_0223ab98(void *);
extern void *func_ov004_0223b18c(void *);
extern void func_ov004_0223d020(void *);
extern void *data_020da13c;
extern void *data_ov004_02256018;

void *func_ov004_0223d5b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_02256018;
    func_ov004_0223d020(self + 0x50);
    func_ov004_0223ab98(self + 0x64);
    func_ov004_0223b18c(self + 0x1c4);
    return self;
}
