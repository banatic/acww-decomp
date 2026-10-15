/* func_02027740 @ 0x02027740, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015094(unsigned char *p);
extern void func_0207df18(void *y, unsigned short *h);
void func_02027740(unsigned char *p)
{
    unsigned char *x = *(unsigned char **) (p + 0x100);
    void *y = *(void **) (x + 0x830);
    unsigned short *h;
    func_02015094(p);
    h = (unsigned short *) (p + 0x124);
    if (*h != 0xfff1) {
        func_0207df18(y, h);
    }
}
