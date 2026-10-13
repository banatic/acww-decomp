/* __sinit_020c4aa8 @ 0x020c4aa8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c8120;
extern int data_021c30ac;

void __sinit_020c4aa8(void)
{
    *(int *) ((char *) ((int) &data_021c30ac) + (0)) = ((int) (*(int *) ((char *) ((int) &data_020c8120) + (0))) - (32768));
}
