/* CARDi_GetTargetMode @ 0x0209dedc, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int cardi_common__autoload_3_021dc744;

int CARDi_GetTargetMode(void)
{
    return *(int *) ((char *) ((int) &cardi_common__autoload_3_021dc744) + (24));
}
