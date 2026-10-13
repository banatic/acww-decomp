/* func_0201bdb4 @ 0x0201bdb4, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f030(unsigned char *);
extern void func_0201c400(unsigned char *, unsigned short *);
extern void func_0201c3f4(unsigned char *, unsigned int);
extern void func_0201a7dc(unsigned char *);
extern void func_0201487c(unsigned char *);
extern void func_0201a74c(unsigned char *);
extern void func_0201b2e0(unsigned char *);
extern void MI_CpuFill8(unsigned char *, int, int);
extern void func_02004490(unsigned char *);
extern void func_02013c14(unsigned char *);
extern void func_02013aac(unsigned char *);
extern void func_0203ed98(unsigned char *);

int func_0201bdb4(unsigned char *param0)
{
    unsigned short local;

    if (func_0203f030(param0) == 0) {
        return 0;
    }

    local = (unsigned short) *(unsigned int *) (param0 + 8);
    func_0201c400(param0, &local);

    *(unsigned int *) (param0 + 0x634) = 0;
    func_0201c3f4(param0, 0xd00);
    func_0201a7dc(param0 + 0x418);
    func_0201487c(param0 + 0x618);
    func_0201a74c(param0 + 0x420);

    param0[0x560] = 0;
    func_0201b2e0(param0 + 0x350);

    param0[0x62c] = 0;
    MI_CpuFill8(param0 + 0x62d, 0, 4);

    func_02004490(param0 + 0x514);
    *(unsigned char **) (param0 + 0x438) = param0 + 0x514;
    func_02013c14(param0 + 0x558);

    param0[0x510] = 1;
    param0[0x511] = 1;
    func_02013aac(param0);

    param0[0x561] = 1;
    param0[0x562] = 1;
    *(unsigned int *) (param0 + 0x628) = 0;
    func_0203ed98(param0);

    return 1;
}
