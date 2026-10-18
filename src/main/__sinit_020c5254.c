/* __sinit_020c5254 @ 0x020c5254, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8188[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_020c5254(void)
{
    data_021c8188[0] = 0;
    data_021c8188[1] = (~2);
    return (~2);
}

#pragma section INIT end
