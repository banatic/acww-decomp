/* func_ov004_0223d52c @ 0x0223d52c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edf54(void *);
extern void func_020ee62c(void *);
extern void func_ov004_0223ab7c(void *);
extern void func_ov004_0223b174(void *);
extern void func_ov004_0223d010(void *);
extern void *data_020da13c;
extern void *data_ov004_02256018;

void *func_ov004_0223d52c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02256018;
    func_ov004_0223b174(self + 0x1c4);
    func_ov004_0223ab7c(self + 0x64);
    func_ov004_0223d010(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
