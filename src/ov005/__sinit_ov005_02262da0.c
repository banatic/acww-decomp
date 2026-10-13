/* __sinit_ov005_02262da0 @ 0x02262da0, 0x14 bytes, Thumb, module ov005
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02239ad8;
extern int data_ov005_02262e0c;

void __sinit_ov005_02262da0(void)
{
    *(unsigned char *) ((char *) ((int) &data_ov005_02262e0c) + (1)) =
        *(unsigned char *) ((char *) ((int) &data_ov003_02239ad8) + (0));
}
