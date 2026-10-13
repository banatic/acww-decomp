/* func_020a5bac @ 0x020a5bac, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a5bac(void *r0, int r1);

void func_020a5bac(void *r0, int r1)
{
    int *ptr;
    ptr = (int *) ((char *) r0 + (r1 << 2) + 0xa8);
    *ptr = 6;
}
