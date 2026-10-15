/* __sinit_ov004_0224ede4 @ 0x0224ede4, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __register_global_object(void *, void *destructor, void *);
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_02258a30;
extern struct {
    unsigned short f0;
} data_ov004_022589ec;
extern void func_020012dc(void *arg0);
extern unsigned char data_ov004_02258ad8;
extern void func_020051b0(void *arg0);
extern unsigned char data_ov004_02258a84;

void __sinit_ov004_0224ede4(void)
{
    data_ov004_02258a30.f0 = 0;
    data_ov004_02258a30.f4 = 0;
    data_ov004_02258a30.f8 = 0;
    __register_global_object((void *) &data_ov004_02258a30, ((void *) &func_020012dc), (void *) &data_ov004_02258ad8);
    data_ov004_022589ec.f0 = 65521;
    __register_global_object((void *) &data_ov004_022589ec, ((void *) &func_020051b0), (void *) &data_ov004_02258a84);
}
