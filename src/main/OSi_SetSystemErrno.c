/* OSi_SetSystemErrno @ 0x020a5bf8, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void OSi_SetSystemErrno(int p0, int v)
{
    *(int *) ((char *) p0 + 0xa0) = v;
}
