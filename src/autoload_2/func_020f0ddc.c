/* func_020f0ddc @ 0x020f0ddc, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f0ddc(void *r0, int r1);

void func_020f0ddc(void *r0, int r1)
{
    *(int *) ((char *) r0 + 4) = r1 << 12;
    *(unsigned short *) ((char *) r0 + 2) = 0;
}
