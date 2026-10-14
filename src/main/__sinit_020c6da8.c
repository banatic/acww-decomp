/* __sinit_020c6da8 @ 0x020c6da8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021f4ae8;
extern void func_020b0aa8(void);
extern void func_020b0aa4(void);
extern void func_020b0a88(void);
extern unsigned char data_021f4adc;

void __sinit_020c6da8(void)
{
    __cxa_vec_ctor((void *) &data_021f4ae8, 2, 16, (void *) &func_020b0aa8, (void *) &func_020b0aa4);
    __register_global_object((void *) &data_021f4ae8, (void *) &func_020b0a88, (void *) &data_021f4adc);
}
