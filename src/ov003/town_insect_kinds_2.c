/* town_insect_kinds_2: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02230604 @ 0x02230604, 0x5c bytes, Thumb
 * func_ov003_022305fc @ 0x022305fc, 0x8 bytes, Thumb
 * func_ov003_022305bc @ 0x022305bc, 0x40 bytes, Thumb
 * func_ov003_022305b4 @ 0x022305b4, 0x8 bytes, Thumb
 */

extern void func_ov003_02230660(void *a, int b, int c, int d, unsigned char e, unsigned char f);
extern void func_ov003_02234600(void *argument0);
extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_ov003_02230f88(void *a);
extern int func_020644cc(int a);
extern void func_ov003_02233930(void *argument0);

void func_ov003_02230604(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x15:
            func_ov003_02230660(self, 0xc8, 0x3c, 0x28, 0x14, 1);
            break;
        case 0x16:
            func_ov003_02230660(self, 0xc8, 0x28, 0x2d, 0x1e, 3);
            break;
        case 0x17:
            func_ov003_02230660(self, 0x64, 0x46, 0x32, 0x78, 0x1e);
            break;
    }
}

void func_ov003_022305fc(void *argument0)
{
    func_ov003_02234600(argument0);
}

void func_ov003_022305bc(char *self)
{
    func_ov003_02230ce8(self, 0, 0x28, 0x50, 0, 0, 0, 0, 3, 1);
    func_ov003_02230f88(self);
    *(short *) (self + 0x232) = (short) (3 * func_020644cc(0x14));
}

void func_ov003_022305b4(void *argument0)
{
    func_ov003_02233930(argument0);
}
