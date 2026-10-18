/* __sinit_020c5948 @ 0x020c5948, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205f570(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021ca16c;
extern void *func_0205f524(void *);
extern unsigned char data_021ca114;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5948(void)
{
    func_0205f570((void *) &data_021ca16c);
    __register_global_object((void *) ((void *) &data_021ca16c), (((void *) func_0205f524)),
                             (void *) ((void *) &data_021ca114));
}

#pragma section INIT end
