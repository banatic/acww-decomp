/* __sinit_020c5a78 @ 0x020c5a78, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e930c(void *, int);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021cb5a0;
extern void func_0206154c(void *);
extern unsigned char data_021cb5a4;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5a78(void)
{
    func_020e930c((void *) &data_021cb5a0, 1);
    __register_global_object((void *) ((void *) &data_021cb5a0), (((void *) func_0206154c)),
                             (void *) ((void *) &data_021cb5a4));
}

#pragma section INIT end
