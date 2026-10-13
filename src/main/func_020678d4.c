/* func_020678d4 @ 0x020678d4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(void *);

void func_020678d4(void *param)
{
    unsigned char *base = (unsigned char *) param;
    base[0x1e75] = 0;
    base[0x1e76] = 0;
    func_020a8c1c((void *) ((unsigned char *) param + 0x1d2c));
}
