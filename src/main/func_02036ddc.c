/* func_02036ddc @ 0x02036ddc, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02041614(void);
extern void func_0209e474(void *buf);
extern int func_0203fc78(int id, void *ptr, int arg);
extern int func_02073d90(unsigned int val);
extern void func_02036d24(void *self, int flag);
extern void func_02036be4(void *self, int flag);
extern void func_02036bbc(void *self, int flag);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern unsigned int data_020ccf94;

void func_02036ddc(void *self)
{
    int r5, r6, r7;
    struct {
        unsigned int a[2];
        unsigned int b[2];
        unsigned int c[2];
        unsigned int d[2];
    } s;

    r5 = func_02041614();

    s.a[0] = 0;
    s.a[1] = 0;
    func_0209e474(s.a);

    MI_CpuCopy8(s.a, s.b, 8);
    r6 = (func_0203fc78(0x13, s.b, 0) != 0) ? 1 : 0;

    r7 = 1;
    if (r5 != 0x12) {
        MI_CpuCopy8(s.a, s.c, 8);
        if (func_0203fc78(0x12, s.c, 0) != 3) {
            r7 = 0;
        }
    }

    if (func_02073d90(data_020ccf94) != 0) {
        MI_CpuCopy8(s.a, s.d, 8);
        r5 = func_0203fc78(0xf, s.d, 0);
    } else {
        r5 = (r5 == 0xf) ? 1 : 0;
    }

    func_02036d24(self, r6);
    func_02036be4(self, r7);
    func_02036bbc(self, (r5 != 0) ? 1 : 0);
}
