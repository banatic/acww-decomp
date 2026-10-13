/* __sinit_020c5c40 @ 0x020c5c40, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066694(void *, int);
extern void __register_global_object(void *, void *, void *);
extern struct {
    long f0;
    long f4;
} data_021cfca0;
extern struct {
    long f0;
    long f4;
} data_021cfc98;
extern unsigned char data_021cfd68;
extern void func_02066688(void);
extern unsigned char data_021cfcc0;
extern void func_02004b2c(void);
extern unsigned char data_021cfca8;

void __sinit_020c5c40(void)
{
    data_021cfca0.f0 = 0;
    data_021cfca0.f4 = 0;
    func_02066694((void *) &data_021cfd68, 0);
    __register_global_object((void *) &data_021cfd68, (void *) &func_02066688, (void *) &data_021cfcc0);
    data_021cfc98.f0 = 0;
    data_021cfc98.f4 = 0;
    __register_global_object((void *) &data_021cfc98, (void *) &func_02004b2c, (void *) &data_021cfca8);
}
