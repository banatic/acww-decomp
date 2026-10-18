/* __sinit_ov006_02262da0 @ 0x02262da0, 0x14 bytes, Thumb, module ov006
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02239ad8;
extern int data_ov006_02262df4;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov006_02262da0(void)
{
    *(unsigned char *) ((char *) ((int) &data_ov006_02262df4) + (1)) =
        *(unsigned char *) ((char *) ((int) &data_ov003_02239ad8) + (0));
}

#pragma section INIT end
