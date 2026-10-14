/* CARDi_GetTargetMode @ 0x0209dedc, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc744;

int CARDi_GetTargetMode(void)
{
    return *(int *) ((char *) ((int) &data_021dc744) + (24));
}
