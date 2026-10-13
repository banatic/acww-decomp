/* __sinit_020c5d1c @ 0x020c5d1c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d11c4[];
extern int func_02077bb4[];
extern int data_021d11b8[];
extern void __register_global_object(int, int, int);

void __sinit_020c5d1c(void)
{
    data_021d11c4[0] = (~0);
    __register_global_object((int) data_021d11c4, (int) func_02077bb4, (int) data_021d11b8);
}
