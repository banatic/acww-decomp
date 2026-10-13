/* __sinit_020c6d2c @ 0x020c6d2c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063df4(void *);
extern void __register_global_object(void *, void *, void *);
extern void func_020b024c(void *);
extern struct {
    unsigned short f0;
} data_021f49f0;
extern struct {
    unsigned short f0;
} data_021f49f4;
extern unsigned char data_021f4a80;
extern void func_02063ddc(void);
extern unsigned char data_021f4aa4;
extern void func_020051b0(void);
extern unsigned char data_021f4a44;
extern unsigned char data_021f4ab0;
extern unsigned char data_021f49ec;
extern void func_020b023c(void);
extern unsigned char data_021f4a68;

void __sinit_020c6d2c(void)
{
    func_02063df4((void *) &data_021f4a80);
    __register_global_object((void *) &data_021f4a80, (void *) &func_02063ddc, (void *) &data_021f4aa4);
    data_021f49f0.f0 = 65521;
    __register_global_object((void *) &data_021f49f0, (void *) &func_020051b0, (void *) &data_021f4a44);
    data_021f49f4.f0 = 5447;
    __register_global_object((void *) &data_021f49f4, (void *) &func_020051b0, (void *) &data_021f4ab0);
    func_020b024c((void *) &data_021f49ec);
    __register_global_object((void *) &data_021f49ec, (void *) &func_020b023c, (void *) &data_021f4a68);
}
