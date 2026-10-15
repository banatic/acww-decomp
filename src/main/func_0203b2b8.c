/* func_0203b2b8 @ 0x0203b2b8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ad68(void);

int func_0203b2b8(void *p)
{
    unsigned short *base;
    base = (unsigned short *) ((char *) p + 0x21c);
    base[2] = 0;
    base[3] = 0x2000;
    func_0203ad68();
    return 1;
}
