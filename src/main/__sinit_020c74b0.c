/* __sinit_020c74b0 @ 0x020c74b0, 0x14 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f24bc(void *);
extern unsigned char data_021fd1bc;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c74b0(void)
{
    func_020f24bc((void *) &data_021fd1bc);
}

#pragma section INIT end
