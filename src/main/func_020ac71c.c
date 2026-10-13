/* func_020ac71c @ 0x020ac71c, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, void *src, int n);
extern void func_020ac89c(void *p, int n);
extern void func_020ac478(void *p, int a, int b);
extern void func_020ac470(void *p, int a);

void func_020ac71c(char *self)
{
    MI_CpuCopy8(*(char **) (self + 4) + 0x2a2, *(char **) (self + 4) + 0x3a2, 0x1a);
    MI_CpuCopy8(*(char **) (self + 4) + 0x2e2, *(char **) (self + 4) + 0x3e2, 0x1a);
    MI_CpuCopy8(*(char **) (self + 4) + 0x25e, *(char **) (self + 4) + 0x35e, 0x22);
    MI_CpuCopy8(*(char **) (self + 4) + 0x51e, *(char **) (self + 4) + 0x41e, 0x22);

    *(unsigned short *) (*(char **) (self + 4) + 0x39e) = *(unsigned short *) (*(char **) (self + 4) + 0x29e);
    *(unsigned short *) (*(char **) (self + 4) + 0x3a0) = *(unsigned short *) (*(char **) (self + 4) + 0x2a0);
    *(unsigned short *) (*(char **) (self + 4) + 0x3be) = *(unsigned short *) (*(char **) (self + 4) + 0x2be);
    *(unsigned short *) (*(char **) (self + 4) + 0x3bc) = *(unsigned short *) (*(char **) (self + 4) + 0x2bc);
    *(unsigned short *) (*(char **) (self + 4) + 0x3de) = *(unsigned short *) (*(char **) (self + 4) + 0x4de);
    *(unsigned short *) (*(char **) (self + 4) + 0x3e0) = *(unsigned short *) (*(char **) (self + 4) + 0x4e0);
    *(unsigned short *) (*(char **) (self + 4) + 0x3fe) = *(unsigned short *) (*(char **) (self + 4) + 0x4fe);
    *(unsigned short *) (*(char **) (self + 4) + 0x3fc) = *(unsigned short *) (*(char **) (self + 4) + 0x4fc);

    func_020ac89c(*(char **) (self + 4) + 0x25e, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x29e, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x2de, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x31e, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x45e, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x49e, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x4de, 0x22);
    func_020ac89c(*(char **) (self + 4) + 0x51e, 0x22);

    func_020ac478(self, 0xd, 0x10);
    func_020ac470(self, 0xd);
    *(unsigned short *) (self + 0x1e) = 1;
}
