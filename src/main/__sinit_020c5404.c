/* __sinit_020c5404 @ 0x020c5404, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02053f00(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c8c48;
extern void *func_02053ed8(void *);
extern unsigned char data_021c8c3c;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5404(void)
{
    func_02053f00((void *) &data_021c8c48);
    __register_global_object((void *) ((void *) &data_021c8c48), (((void *) func_02053ed8)),
                             (void *) ((void *) &data_021c8c3c));
}

#pragma section INIT end
