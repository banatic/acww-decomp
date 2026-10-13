/* __sinit_ov004_0224ee2c @ 0x0224ee2c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(void *, int, int, void *, void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_ov004_02258af4;
extern void func_ov004_02234008(void);
extern void func_ov004_02233ff4(void);
extern void func_ov004_02233fd8(void);
extern unsigned char data_ov004_02258ae8;

void __sinit_ov004_0224ee2c(void)
{
    func_02138d6c((void *) &data_ov004_02258af4, 15, 148, (void *) &func_ov004_02234008, (void *) &func_ov004_02233ff4);
    __register_global_object((void *) &data_ov004_02258af4, (void *) &func_ov004_02233fd8, (void *) &data_ov004_02258ae8);
}
