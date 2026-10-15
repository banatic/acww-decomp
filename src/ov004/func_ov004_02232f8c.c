/* func_ov004_02232f8c @ 0x02232f8c, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_common_subs off
extern void func_020ad408(void);
extern void func_020ace24(void);
extern short func_ov004_02231b98(void *self);
extern unsigned int NNS_G3dMdlSetMdlDiff(int a, int b, int c);
extern void func_0205510c(void *p, int k);

int func_ov004_02232f8c(void *self)
{
    volatile unsigned short t[2];

    func_020ad408();
    func_020ace24();
    if (*(signed char *) ((char *) self + 0x3540) != -1) {
        t[0] = (unsigned short) func_ov004_02231b98(self);
        t[1] = t[0];
        NNS_G3dMdlSetMdlDiff(*(int *) ((char *) self + 0xac), *(signed char *) ((char *) self + 0x3540), t[1]);
    }
    func_0205510c((char *) self + 0x50, 0);
    return 1;
}
