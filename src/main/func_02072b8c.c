/* func_02072b8c @ 0x02072b8c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02072b8c(unsigned char *r0);

void func_02072b8c(unsigned char *r0)
{
    unsigned char i;
    i = 0;
    do {
        r0[i] = i;
        i = (unsigned char) (i + 1);
    } while (i < 8);
}
