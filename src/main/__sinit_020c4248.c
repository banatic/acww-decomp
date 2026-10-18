/* __sinit_020c4248 @ 0x020c4248, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02011fd8(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c1284;
extern int func_02011fc0(void *);
extern unsigned char data_021c1278;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c4248(void)
{
    func_02011fd8((void *) &data_021c1284);
    __register_global_object((void *) ((void *) &data_021c1284), (((void *) func_02011fc0)),
                             (void *) ((void *) &data_021c1278));
}

#pragma section INIT end
