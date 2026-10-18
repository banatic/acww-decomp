/* __sinit_ov007_02262da0 @ 0x02262da0, 0x14 bytes, Thumb, module ov007
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02256914;
extern int data_ov007_02262dc8;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov007_02262da0(void)
{
    *(unsigned char *) ((char *) ((int) &data_ov007_02262dc8) + (1)) =
        *(unsigned char *) ((char *) ((int) &data_ov003_02256914) + (0));
}

#pragma section INIT end
