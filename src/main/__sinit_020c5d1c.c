/* __sinit_020c5d1c @ 0x020c5d1c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d11c4[];
extern void func_02077bb4(void *);
extern int data_021d11b8[];
extern void __register_global_object(void *, void *, void *);

void __sinit_020c5d1c(void)
{
    data_021d11c4[0] = (~0);
    __register_global_object((void *) ((int) data_021d11c4), (((void *) func_02077bb4)), (void *) ((int) data_021d11b8));
}
