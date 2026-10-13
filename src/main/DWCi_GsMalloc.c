/* DWCi_GsMalloc @ 0x0209615c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int DWC_Alloc(int a, int b);

int DWCi_GsMalloc(int a)
{
    return DWC_Alloc(5, a);
}
