/* func_ov052_022611f0 @ 0x022611f0, 0x50 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(void *, int, int, int);
extern int func_0201c2c8(void *, int);
extern void func_0201aff4(void *, int);

int func_ov052_022611f0(void *p)
{
    volatile int locals[7];
    int ret;

    locals[0] = 0;
    locals[1] = 0;
    locals[2] = 0;
    locals[3] = 0;
    locals[4] = 0;
    locals[5] = data_020c80f8;
    locals[6] = 0;

    func_02019d0c((char *) p + 0x564, 3, 1, 0);
    ret = func_0201c2c8(p, 4);
    func_0201aff4((char *) p + 0x350, ret);

    return 1;
}
