/* func_020873b4 @ 0x020873b4, 0xca bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0209dfd8(void *dst, const void *src, int size, int d, int e);
extern void func_0209e474(void *p);
extern void func_0209e140(void *p, int v);
extern int func_0209de88(int year, int month, int day);
extern int func_0209e3ac(void *p, void *q, int v);
extern void func_020872d0(void *p);
extern int func_0209e380(void *p, void *q);
extern void func_02087500(void *p, int v);
extern void func_02087358(void *p, void *q);
extern void func_02087274(void *p, void *q);

void func_020873b4(void *param, int days)
{
    u8 data[16];
    int r;
    int a;
    int b;

    func_0209dfd8(data, param, 6, 0, 0);

    *(u32 *) &data[8] = 0;
    *(u32 *) &data[12] = 0;
    func_0209e474(&data[8]);

    if (!(data[13] == 0 && data[12] == 1 && data[11] == 1)) {
        if (data[10] < 6) {
            func_0209e140(&data[8], 1);
            data[10] = 6;
            data[9] = 0;
            data[8] = 0;
        }
    }

    r = func_0209e3ac(&data[8], data, 0x38);
    func_020872d0(param);

    if (r == 1) {
        a = func_0209de88(data[5], data[4], data[3]);
        b = func_0209de88(data[13], data[12], data[11]);
        if (b < a || func_0209e380(data, &data[8]) >= 7) {
            func_02087500(param, 0);
            func_02087358(param, &data[8]);
        }
    } else if (r == -1) {
        func_02087500(param, 1);
        func_02087358(param, &data[8]);
        func_02087274(param, &data[8]);
    }
}
