/* func_02081660 @ 0x02081660, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *p, int a, int b);
extern void func_02003738(void *p);
extern void func_02080b50(void *p);
extern void func_02081ef0(void *p);
extern void func_020642e0(void *p);
extern void func_02081f94(void *p);
extern void func_0209b604(void *p);
extern void func_02066650(void *p);
extern void func_0207dfec(void *p);

void func_02081660(void *self)
{
    int i;
    int j;

    MI_CpuFill8(self, 0, 0x7ec);
    func_02003738((char *) self + 0x7a0);
    *(unsigned short *) ((char *) self + 0x7d2) = 0x11a8;
    func_02080b50(self);

    for (i = 0; i < 8; i++) {
        func_02081ef0((char *) self + (i << 7));
    }

    func_020642e0((char *) self + 0x7b8);

    for (j = 0; j < 10; j++) {
        *(unsigned short *) ((char *) self + (j << 1) + 0x78c) = 0xfff1;
    }

    func_02081f94((char *) self + 0x7ce);
    func_0209b604((char *) self + 0x734);
    *(unsigned char *) ((char *) self + 0x7d6) = 3;
    func_02066650((char *) self + 0x634);
    func_0207dfec(self);
    func_020642e0((char *) self + 0x7dc);
}
