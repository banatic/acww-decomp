/* __sinit_020c739c @ 0x020c739c, 0x34 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __register_global_object(void *, void *, void *, int);
extern struct {
    long f0;
    long f4;
    long f8;
} data_021fbee8;
extern void func_020012dc(void);
extern unsigned char data_021fbedc;

void __sinit_020c739c(void)
{
    data_021fbee8.f0 = 0;
    data_021fbee8.f4 = 0;
    data_021fbee8.f8 = 0;
    __register_global_object((void *) &data_021fbee8, (void *) &func_020012dc, (void *) &data_021fbedc, 0);
}
