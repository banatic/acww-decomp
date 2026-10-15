/* __sinit_ov004_0224ebb0 @ 0x0224ebb0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d228(void *);
extern void __register_global_object(void *, void *destructor, void *);
extern unsigned char data_ov004_022585ac;
extern void func_0203d224(void *arg0);
extern unsigned char data_ov004_02258560;

void __sinit_ov004_0224ebb0(void)
{
    func_0203d228((void *) &data_ov004_022585ac);
    __register_global_object((void *) &data_ov004_022585ac, ((void *) &func_0203d224), (void *) &data_ov004_02258560);
}
