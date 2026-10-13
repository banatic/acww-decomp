/* func_02066478 @ 0x02066478, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065eac(void *param1, int param2);
extern void func_02065ef4(void *param1, int param2);

void func_02066478(void *param0)
{
    unsigned char *ptr;
    unsigned short val;
    void *base;

    base = param0;
    func_02065eac(base, 2);

    ptr = (unsigned char *) base + 0xfb;
    *ptr = 0x11;

    val = *(unsigned short *) ((unsigned char *) base + 0xfc);
    if (val != 0xfff1) {
        func_02065ef4(base, 1);
    }
}
