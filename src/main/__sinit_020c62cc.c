/* __sinit_020c62cc @ 0x020c62cc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208ef58(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021d35f8;
extern void *func_0208ef34(void *);
extern unsigned char data_021d35cc;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c62cc(void)
{
    func_0208ef58((void *) &data_021d35f8);
    __register_global_object((void *) ((void *) &data_021d35f8), (((void *) func_0208ef34)),
                             (void *) ((void *) &data_021d35cc));
}

#pragma section INIT end
