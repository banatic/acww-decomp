/* func_020abd44 @ 0x020abd44, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aca7c(void *p);

int func_020abd44(void *p)
{
    return func_020aca7c((char *) p + 0xE4) + 0x80 - *(short *) ((char *) p + 0x18);
}
