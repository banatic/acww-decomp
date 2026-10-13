/* func_ov004_0223eba4 @ 0x0223eba4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d2b8(void *);
extern void func_020ee660(void *);
extern void func_02138d6c(void *, int, int, void *, void *);
extern void func_02089b38();
extern void func_02089b50();
extern void *data_020da13c;
extern void *data_ov004_022562c0;

void *func_ov004_0223eba4(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_022562c0;
    func_02138d6c(self + 0x50, 0x4, 0x4c, (void *) func_02089b50, (void *) func_02089b38);
    func_0209d2b8(self + 0x180);
    return self;
}
