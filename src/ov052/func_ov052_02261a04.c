/* func_ov052_02261a04 @ 0x02261a04, 0x88 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *self);
extern void func_0201c280(void *a, void *b);
extern void func_ov052_022610d4(void *a, void *b);
extern void MI_CpuFill8(void *s, int c, unsigned int n);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern unsigned short data_020c80f8;

int func_ov052_02261a04(char *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov052_022610d4(self + 0x658, self);
    *(unsigned short *) (self + 0x71c) = data_020c80f8;
    MI_CpuFill8(self + 0x733, 0, 5);
    MI_CpuFill8(self + 0x738, 0, 5);
    func_0201af28(self + 0x350, 2, 0x400, 0x133, 0x199);
    return 1;
}
