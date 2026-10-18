/* __sinit_020c5858 @ 0x020c5858, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205d6b4(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c9d1c;
extern void *func_0205d690(void *);
extern int data_021c9d10;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5858(void)
{
    func_0205d6b4((void *) &data_021c9d1c);
    __register_global_object((void *) ((void *) &data_021c9d1c), (((void *) func_0205d690)),
                             (void *) ((void *) &data_021c9d10));
}

#pragma section INIT end
