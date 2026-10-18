/* __sinit_ov010_02260020 @ 0x02260020, 0x14 bytes, Thumb, module ov010
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02256914;
extern int data_ov010_02260098;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov010_02260020(void)
{
    *(unsigned char *) ((char *) ((int) &data_ov010_02260098) + (9)) =
        *(unsigned char *) ((char *) ((int) &data_ov004_02256914) + (0));
}

#pragma section INIT end
