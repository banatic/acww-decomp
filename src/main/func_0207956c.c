/* func_0207956c @ 0x0207956c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd5c(void *);
extern void func_0209c52c(void *);
extern void func_02079450(void *);
extern void MI_CpuFill8(void *, int, int);

void func_0207956c(void *r0)
{
    MI_CpuFill8(r0, 0, 0x2c);
    *(unsigned char *) r0 = 0;
    *(unsigned char *) ((char *) r0 + 1) = 3;
    func_0209bd5c((char *) r0 + 4);
    func_0209c52c((char *) r0 + 0x10);
    *(unsigned char *) ((char *) r0 + 0x18) = 5;
    *(unsigned char *) ((char *) r0 + 0x1c) = 0xc;
    *(unsigned int *) ((char *) r0 + 0x20) = 0;
    *(unsigned short *) ((char *) r0 + 0x24) = 0;
    func_02079450(r0);
}
