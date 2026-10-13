/* func_ov004_02233508 @ 0x02233508, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055438(void *);
extern void func_020ee62c(void *);
extern void *data_020da13c;
extern void *data_ov004_02255bd4;

void *func_ov004_02233508(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255bd4;
    func_02055438(self + 0x174);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}
