/* OSi_GetSystemErrno @ 0x020a5bf0, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int OSi_GetSystemErrno(int p0)
{
    return *(int *) ((char *) p0 + 0xa0);
}
