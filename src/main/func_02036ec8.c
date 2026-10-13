/* func_02036ec8 @ 0x02036ec8, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036ddc(void);

void func_02036ec8(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    ptr[0x15] = 1;
    func_02036ddc();
}
