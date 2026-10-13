/* func_ov108_0229d960 @ 0x0229d960, 0x80 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);

void func_ov108_0229d960(void *self)
{
    char *base = (char *) self;
    int zero = 0;

    *(int *) (base + 0x94) = zero;
    func_ov094_0229af40(base + 0x2f0, 2);
    func_ov094_0229bbd8(base + 0xd50, 2);
    func_ov094_0229a2b0(base + 0xd78, 6);
    base[0x2ae] = 0x16;
    func_ov002_02209e18(base + 0x2480);
    base[0x2ac] = 0;
    base[0x2b0] = 0xb;
    func_ov002_02209984(base + 0x24fc, 3, 1, 0);
    base[0x2b6] = 0;
}