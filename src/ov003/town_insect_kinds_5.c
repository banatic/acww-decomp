/* town_insect_kinds_5: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02230b48 @ 0x02230b48, 0xf4 bytes, Thumb
 * func_ov003_02230b40 @ 0x02230b40, 0x8 bytes, Thumb
 * func_ov003_02230ab4 @ 0x02230ab4, 0x8c bytes, Thumb
 * func_ov003_02230a74 @ 0x02230a74, 0x40 bytes, Thumb
 * func_ov003_02230a6c @ 0x02230a6c, 0x8 bytes, Thumb
 * func_ov003_02230a48 @ 0x02230a48, 0x22 bytes, Thumb
 * func_ov003_02230a40 @ 0x02230a40, 0x8 bytes, Thumb
 */

extern void func_ov003_02230c3c(void *self, int a, int b, int c, int d, int e);
extern void func_ov003_02232a44(void *argument0);
extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_020644cc(int a);
extern void func_ov003_0222d518(void *a, int b);
extern void func_ov003_022337d8(void *argument0);
extern void func_ov003_02233890(void *argument0);

void func_ov003_02230b48(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0:
            func_ov003_02230c3c(self, 0x64, 0x50, 0x25, 8, 0x119a);
            break;
        case 1:
            func_ov003_02230c3c(self, 0x64, 0x50, 0x25, 8, 0x119a);
            break;
        case 2:
            func_ov003_02230c3c(self, 0x50, 0x50, 0x28, 9, 0x1000);
            break;
        case 3:
            func_ov003_02230c3c(self, 0x50, 0x50, 0x28, 9, 0x1000);
            break;
        case 4:
            func_ov003_02230c3c(self, 0x3c, 0x50, 0x2f, 0xa, 0xe66);
            break;
        case 5:
            func_ov003_02230c3c(self, 0x46, 0x50, 0x14, 0xc, 0x1000);
            break;
        case 6:
            func_ov003_02230c3c(self, 0x64, 0x1e, 0x32, 0xf, 0x1000);
            break;
        case 7:
            func_ov003_02230c3c(self, 0x3c, 0x50, 0x34, 0xc, 0x1000);
            break;
        default:
            func_ov003_02230c3c(self, 0x3c, 0x50, 0x2d, 0xa, 0x1000);
            break;
    }
}

void func_ov003_02230b40(void *argument0)
{
    func_ov003_02232a44(argument0);
}

void func_ov003_02230ab4(char *self)
{
    int *v = (int *) (self + 0x1e0);
    int *s;
    func_ov003_02230ce8(self, 0x384, 0xc8, 0x28, 1, -0x8000, 0x2f, 0, 0xa, 0);
    *(char *) (self + 0x252) = 0x3c;
    *(char *) (self + 0x256) = (char) func_020644cc(0x12);
    *(char *) (self + 0x24c) = 1;
    *(int *) (self + 0x220) = 0;
    s = (int *) (self + 0x204);
    *(int *) (self + 0x1e0) = s[0];
    v[1] = s[1];
    v[2] = s[2];
    func_ov003_0222d518(self, 0x1000);
}

void func_ov003_02230a74(char *self)
{
    int save = *(int *) (self + 0x21c);
    func_ov003_02230ce8(self, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 6, 1);
    *(int *) (self + 0x21c) = save;
    *(char *) (self + 0x252) = 0x3c;
}

void func_ov003_02230a6c(void *argument0)
{
    func_ov003_022337d8(argument0);
}

void func_ov003_02230a48(void *self)
{
    func_ov003_02230ce8(self, 0, 0, 0, 0, 0, 0x19, 0, 0x19, 0);
}

void func_ov003_02230a40(void *argument0)
{
    func_ov003_02233890(argument0);
}
