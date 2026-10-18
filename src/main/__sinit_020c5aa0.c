/* __sinit_020c5aa0 @ 0x020c5aa0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02062d7c(void *);
extern void __register_global_object(void *, void *, void *);
extern struct {
    unsigned short f0;
} data_021cb5b0;
extern unsigned char data_021cb5e0;
extern void *func_02062d44(void *);
extern unsigned char data_021cb5c8;
extern void func_020051b0(void *);
extern unsigned char data_021cb5d4;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5aa0(void)
{
    func_02062d7c((void *) &data_021cb5e0);
    __register_global_object((void *) ((void *) &data_021cb5e0), (((void *) func_02062d44)),
                             (void *) ((void *) &data_021cb5c8));
    data_021cb5b0.f0 = 65521;
    __register_global_object((void *) ((void *) &data_021cb5b0), (((void *) func_020051b0)),
                             (void *) ((void *) &data_021cb5d4));
}

#pragma section INIT end
