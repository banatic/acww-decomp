/* __sinit_020c6b88 @ 0x020c6b88, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a6b88(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021f4320;
extern void *func_020a6b38(void *);
extern unsigned char data_021f42fc;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c6b88(void)
{
    func_020a6b88((void *) &data_021f4320);
    __register_global_object((void *) ((void *) &data_021f4320), (((void *) func_020a6b38)),
                             (void *) ((void *) &data_021f42fc));
}

#pragma section INIT end
