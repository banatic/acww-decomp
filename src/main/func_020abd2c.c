/* func_020abd2c @ 0x020abd2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aca74(void *ptr);

int func_020abd2c(void *s)
{
    return func_020aca74((char *) s + 0xE4) + 0x60 - *(signed short *) ((char *) s + 0x1A);
}
