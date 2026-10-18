/* __sinit_020c50b0 @ 0x020c50b0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203d6d4(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c69b4;
extern void *func_0203d698(void *);
extern int data_021c69a8;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c50b0(void)
{
    func_0203d6d4((void *) &data_021c69b4);
    __register_global_object((void *) ((void *) &data_021c69b4), (((void *) func_0203d698)),
                             (void *) ((void *) &data_021c69a8));
}

#pragma section INIT end
