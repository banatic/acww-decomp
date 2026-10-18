/* __sinit_020c50d8 @ 0x020c50d8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c72c4[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_020c50d8(void)
{
    data_021c72c4[0] = 0;
    data_021c72c4[1] = 0;
    return (int) data_021c72c4;
}

#pragma section INIT end
