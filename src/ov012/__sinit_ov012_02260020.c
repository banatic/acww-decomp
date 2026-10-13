/* __sinit_ov012_02260020 @ 0x02260020, 0x14 bytes, Thumb, module ov012
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02256914;
extern int data_ov012_02260084;

void __sinit_ov012_02260020(void)
{
    *(unsigned char *) ((char *) ((int) &data_ov012_02260084) + (9)) =
        *(unsigned char *) ((char *) ((int) &data_ov004_02256914) + (0));
}
