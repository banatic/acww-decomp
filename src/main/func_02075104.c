/* func_02075104 @ 0x02075104, 0x13c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;

extern void func_020792a0(void);
extern void func_0208602c(void);
extern void func_02086130(void);
extern void func_02053010(void);
extern void func_0209d3e4(void);
extern void func_020b316c(void);
extern void func_0203f4c4(void);
extern void func_02070778(void);
extern int func_02073918(void *, int);
extern int func_0204bbd4(unsigned int);
extern void func_020b23ec(int, int);
extern void func_02051e38(int);
extern void func_0209d57c(u8, int);
extern void func_02096204(unsigned int);
extern void func_020ae4f0(void);
extern void func_020731a4(void *, int);

void func_02075104(int mode)
{
    void *p;
    unsigned int i;
    unsigned int j;
    unsigned int k;
    int n;
    int h;
    u8 b;

    if (mode == 4) {
        func_020792a0();
        func_0208602c();
        func_02086130();
    }
    func_02053010();
    func_0209d3e4();
    func_020b316c();
    func_0203f4c4();
    func_02070778();
    if (mode < 0) {
        p = data_020ccf94;
        if (func_02073918(p, 0) || func_02073918(p, 4)) {
            if (mode == -4) {
                for (i = 0; i < 0x22; i++) {
                    h = func_0204bbd4(i);
                    func_020b23ec(h, 1);
                    func_020b23ec(h, 2);
                    func_020b23ec(h, 3);
                }
                func_02051e38(1);
                func_02051e38(2);
                func_02051e38(3);
                for (j = 0; j < 0x33; j++) {
                    b = (u8) j;
                    func_0209d57c(b, 1);
                    func_0209d57c(b, 2);
                    func_0209d57c(b, 3);
                }
            } else {
                n = -mode;
                for (i = 0; i < 0x22; i++) {
                    func_020b23ec(func_0204bbd4(i), n);
                }
                func_02051e38(n);
                for (j = 0; j < 0x33; j++) {
                    func_0209d57c((u8) j, n);
                }
            }
        }
    }
    if (mode < 0) {
        if (mode == -4) {
            for (k = 0; k < 4; k++) {
                func_02096204(k);
            }
        } else {
            func_02096204(-mode);
        }
    }
    if (mode == -4) {
        func_020ae4f0();
    }
    if ((mode < 0 ? -mode : mode) < 4) {
        if (mode < 0) {
            mode = -mode;
        }
        func_020731a4(data_020ccf94, mode);
    }
}
