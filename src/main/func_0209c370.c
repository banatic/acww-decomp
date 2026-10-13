/* func_0209c370 @ 0x0209c370, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_0209c370(void *arg0)
{
    unsigned char val;
    val = *(unsigned char *) ((char *) arg0 + 0x10);
    if (val < 0xc) {
        return 1;
    }
    return 0;
}
