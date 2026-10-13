/* func_ov068_02273860 @ 0x02273860, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c87c(void *);
extern void func_020565c8(void *);
extern void func_02055210(void *);
extern void func_ov004_0222c548(void *);
extern void func_ov004_0222c398(void *);
extern char data_ov068_022778f4[];

void *func_ov068_02273860(void *self)
{
    func_ov004_0222c87c(self);
    *(void **) self = data_ov068_022778f4;
    func_020565c8((char *) self + 0x290);
    func_020565c8((char *) self + 0x2b0);
    func_02055210((char *) self + 0x2d0);
    func_ov004_0222c548((char *) self + 0x388);
    func_ov004_0222c398((char *) self + 0x42c);
    func_02055210((char *) self + 0x434);
    func_ov004_0222c548((char *) self + 0x4ec);
    func_ov004_0222c398((char *) self + 0x590);
    return self;
}
