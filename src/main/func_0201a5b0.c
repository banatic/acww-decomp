/* func_0201a5b0 @ 0x0201a5b0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200454c(void);

void func_0201a5b0(unsigned char *arg0)
{
    unsigned char val;
    unsigned char val2;

    val = *(unsigned char *) (arg0 + 0x24);
    if (val == 1) {
        val2 = *(unsigned char *) (arg0 + 0x26);
        if (val2 != 0) {
            func_0200454c();
        }
    }
    *(unsigned char *) (arg0 + 0x24) = 2;
    return;
}
