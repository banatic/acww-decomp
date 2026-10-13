/* func_0207ffac @ 0x0207ffac, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02080b64(void);

int func_0207ffac(void)
{
    unsigned char *p = (unsigned char *) func_02080b64();
    int shift = 0;
    if (p != 0) {
        shift = ((int) ((unsigned) (p[0] << 27) >> 27)) >> 2;
        if (shift < 0 || shift >= 5) {
            shift = 0;
        }
    }
    return shift + 0x1010;
}
