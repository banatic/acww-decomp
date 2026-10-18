/* __sinit_020c5c24 @ 0x020c5c24, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfbcc;
extern void *func_0206eac0(void *);
extern int data_021cfbb0;
extern void __register_global_object(void *, void *, void *);

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5c24(void)
{
    __register_global_object((void *) ((int) &data_021cfbcc), (((void *) func_0206eac0)), (void *) ((int) &data_021cfbb0));
}

#pragma section INIT end
