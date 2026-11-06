/* music_show_overlay: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02246a2c @ 0x02246a2c, 0x48 bytes, Thumb
 * func_ov004_02246a04 @ 0x02246a04, 0x28 bytes, Thumb
 * func_ov004_022469dc @ 0x022469dc, 0x28 bytes, Thumb
 * func_ov004_02246988 @ 0x02246988, 0x54 bytes, Thumb
 * func_ov004_02246954 @ 0x02246954, 0x34 bytes, Thumb
 * func_ov004_0224692c @ 0x0224692c, 0x28 bytes, Thumb
 * func_ov004_02246900 @ 0x02246900, 0x2c bytes, Thumb
 */

#include "types.h"

extern void func_0204f934(int);
extern int SDK_OVERLAY_ov093_ID;
extern void *data_021c9b28;
extern void *func_020e9948(void *, unsigned long);
extern void *func_ov093_022997f8(void *);
extern void func_ov093_0229976c(void *);
extern void *data_ov004_0225ff54;
extern unsigned char data_ov004_0225ff50;
extern void func_ov093_02299630(void *p);
extern void func_ov093_022995b0(void *p);
extern void func_ov093_0229959c(void *);
extern void *func_ov093_022997b4(void *);
extern void func_020e993c(void *, void *);
extern void func_0204f8ec(int);
extern void func_ov093_022994ac(void *, int);
extern void func_ov093_02299424(void *p);
extern int func_ov093_02299418(int p);

// Overlay ids are linker symbols, so the id comes from the literal pool.
void func_ov004_02246a2c(void)
{
    func_0204f934((int) &SDK_OVERLAY_ov093_ID);
    data_ov004_0225ff54 = func_020e9948(data_021c9b28, 0x2520);
    if (data_ov004_0225ff54 != 0) {
        func_ov093_022997f8(data_ov004_0225ff54);
    }
    func_ov093_0229976c(data_ov004_0225ff54);
    data_ov004_0225ff50 = 1;
}

void func_ov004_02246a04(void)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        func_ov093_02299630(data_ov004_0225ff54);
    }
}

void func_ov004_022469dc(void)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        func_ov093_022995b0(data_ov004_0225ff54);
    }
}

void func_ov004_02246988(void)
{
    void *h;
    if (data_ov004_0225ff50 & 1) {
        func_ov093_0229959c(data_ov004_0225ff54);
        h = data_021c9b28;
        func_ov093_022997b4(data_ov004_0225ff54);
        func_020e993c(h, data_ov004_0225ff54);
        data_ov004_0225ff54 = 0;
        func_0204f8ec((int) &SDK_OVERLAY_ov093_ID);
    }
    data_ov004_0225ff50 = 0;
}

void func_ov004_02246954(int x)
{
    if (((*(u8 *) &data_ov004_0225ff50) & 1) != 0) {
        if (x <= 0) {
            x = 0x125c;
        }
        func_ov093_022994ac(data_ov004_0225ff54, x);
    }
}

void func_ov004_0224692c(void)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        func_ov093_02299424(data_ov004_0225ff54);
    }
}

int func_ov004_02246900(void)
{
    // DECLS
    // ENDDECLS
    if ((*(u8 *) ((char *) ((void **) &data_ov004_0225ff50)) & 0x1) != 0x0) {
        return func_ov093_02299418(*(int *) ((char *) &data_ov004_0225ff54));
    }
    return 0x0;
}
