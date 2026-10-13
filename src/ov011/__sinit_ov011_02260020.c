/* __sinit_ov011_02260020 @ 0x02260020, 0x14 bytes, Thumb, module ov011
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02256914;
extern int data_ov011_0226008c;

void __sinit_ov011_02260020(void)
{
    *(unsigned char *) ((char *) ((int) &data_ov011_0226008c) + (9)) =
        *(unsigned char *) ((char *) ((int) &data_ov004_02256914) + (0));
}
