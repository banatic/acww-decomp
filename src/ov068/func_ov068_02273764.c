/* func_ov068_02273764 @ 0x02273764, 0x80 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_022778f4;
extern void func_ov004_0222c394(void *);
extern void func_ov004_0222c538(void *);
extern void func_020551e0(void *);
extern void func_020565b0(void *);
extern void func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);

void *func_ov068_02273764(void *p)
{
    *(void **) p = &data_ov068_022778f4;
    func_ov004_0222c394((char *) p + 0x590);
    func_ov004_0222c538((char *) p + 0x4ec);
    func_020551e0((char *) p + 0x434);
    func_ov004_0222c394((char *) p + 0x42c);
    func_ov004_0222c538((char *) p + 0x388);
    func_020551e0((char *) p + 0x2d0);
    func_020565b0((char *) p + 0x2b0);
    func_020565b0((char *) p + 0x290);
    func_ov004_0222c7a0(p);
    func_020edf54(p);
    return p;
}
