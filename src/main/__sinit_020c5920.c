/* __sinit_020c5920 @ 0x020c5920, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205e678(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021c9f5c;
extern void *func_0205e65c(void *);
extern int data_021c9f3c;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5920(void)
{
    func_0205e678((void *) &data_021c9f5c);
    __register_global_object((void *) ((void *) &data_021c9f5c), (((void *) func_0205e65c)),
                             (void *) ((void *) &data_021c9f3c));
}

#pragma section INIT end
