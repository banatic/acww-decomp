/* func_ov004_022460d0 @ 0x022460d0, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022461c4(void *);
extern void *data_021c80bc;
extern int func_0204f538(void *, void *, int, int, int);
int func_ov004_022460d0(void *self)
{
    void *glob;
    unsigned short item;
    func_ov004_022461c4(self);
    glob = data_021c80bc;
    item = 0xfff1;
    item = 0x3e04;
    func_0204f538(glob, (void *) &item, 6, 10, 0);
    item = 0x3e08;
    func_0204f538(glob, (void *) &item, 7, 10, 0);
    item = 0x3e0c;
    func_0204f538(glob, (void *) &item, 8, 10, 0);
    item = 0x3e10;
    func_0204f538(glob, (void *) &item, 9, 10, 0);
    item = 0x3e14;
    func_0204f538(glob, (void *) &item, 6, 11, 0);
    item = 0x3e18;
    func_0204f538(glob, (void *) &item, 7, 11, 0);
    item = 0x3e1c;
    func_0204f538(glob, (void *) &item, 8, 11, 0);
    item = 0x3e20;
    func_0204f538(glob, (void *) &item, 9, 11, 0);
    return 1;
}
