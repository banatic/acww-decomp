/* func_ov004_02239c40 @ 0x02239c40, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02089b68(void *);
extern void *data_ov004_02255d28;

void *func_ov004_02239c40(char *self)
{
    // DECLS
    // ENDDECLS
    func_02089b68(self);
    *(void **) (self) = &data_ov004_02255d28;
    *(void **) (self + 0x4c) = 0x0;
    return self;
}
