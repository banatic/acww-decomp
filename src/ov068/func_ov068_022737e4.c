/* func_ov068_022737e4 @ 0x022737e4, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c394(void *p);
extern void func_ov004_0222c538(void *p);
extern void func_020551e0(void *p);
extern void func_020565b0(void *p);
extern void func_ov004_0222c7a0(void *p);

extern unsigned char data_ov068_022778f4[];

void *func_ov068_022737e4(void *arg)
{
    char *obj = (char *) arg;
    *(void **) obj = (void *) data_ov068_022778f4;
    func_ov004_0222c394(obj + 0x590);
    func_ov004_0222c538(obj + 0x4ec);
    func_020551e0(obj + 0x434);
    func_ov004_0222c394(obj + 0x42c);
    func_ov004_0222c538(obj + 0x388);
    func_020551e0(obj + 0x2d0);
    func_020565b0(obj + 0x2b0);
    func_020565b0(obj + 0x290);
    func_ov004_0222c7a0(arg);
    return arg;
}
