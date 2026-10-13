/* __sinit_020c6344 @ 0x020c6344, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020900ac(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021d36d4;
extern void func_0209008c(void);
extern unsigned char data_021d36c8;

void __sinit_020c6344(void)
{
    func_020900ac((void *) &data_021d36d4);
    __register_global_object((void *) &data_021d36d4, (void *) &func_0209008c, (void *) &data_021d36c8);
}
