/* func_020abd14 @ 0x020abd14, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020aca6c(void *);

int func_020abd14(void *p)
{
    return (int) ((char *) func_020aca6c((char *) p + 0xE4) + 0x60) - *(signed short *) ((char *) p + 0x1A);
}
