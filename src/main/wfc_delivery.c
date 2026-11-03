/* wfc_delivery: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203f5e0 @ 0x0203f5e0, 0x2 bytes, Thumb
 * func_0203f5dc @ 0x0203f5dc, 0x2 bytes, Thumb
 * func_0203f5d8 @ 0x0203f5d8, 0x4 bytes, Thumb
 * func_0203f5a4 @ 0x0203f5a4, 0x34 bytes, Thumb
 */

extern char data_021eed68;
extern int func_0207813c(void *p);
extern void func_02078130(void *p, unsigned short v);
extern void func_02077ed4(void *p);

void func_0203f5e0(void *self) {}

void func_0203f5dc(void *object) {}

int func_0203f5d8(int p0)
{
    return ((int) (p0) + (194));
}

int func_0203f5a4(void *self)
{
    char *base = &data_021eed68;
    unsigned short v = *(unsigned short *) ((char *) self + 0xC0);
    if (v != func_0207813c(base)) {
        func_02078130(base, v);
        func_02077ed4(self);
        return 1;
    } else {
        return 0;
    }
}
