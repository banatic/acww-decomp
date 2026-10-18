/* __sinit_020c6c7c @ 0x020c6c7c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205577c(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021f472c;
extern void *func_02055764(void *);
extern unsigned char data_021f4720;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c6c7c(void)
{
    func_0205577c((void *) &data_021f472c);
    __register_global_object((void *) ((void *) &data_021f472c), (((void *) func_02055764)),
                             (void *) ((void *) &data_021f4720));
}

#pragma section INIT end
