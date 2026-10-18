/* __sinit_020c6f5c @ 0x020c6f5c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f6ca0[];
extern int data_021f6c98[];

#pragma define_section INIT ".init" RX
#pragma section INIT begin

int __sinit_020c6f5c(void)
{
    data_021f6ca0[0] = 0;
    data_021f6ca0[1] = 0;
    data_021f6c98[0] = 0;
    data_021f6c98[1] = 0;
    return (int) data_021f6c98;
}

#pragma section INIT end
