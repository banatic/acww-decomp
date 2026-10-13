/* func_ov133_0229c62c @ 0x0229c62c, 0x94 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov133_0229ad88(char *self, int v);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(char *p);
extern void func_ov002_0220ad18(char *p, int v);
extern void func_ov130_0229a00c(int v);
extern void func_02088df8(int a0, const void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10,
                          int a11);
extern const char data_ov133_0229c868[];

int func_ov133_0229c62c(char *self)
{
    if (func_ov133_0229ad88(self, 1) == 0) {
        return 1;
    }
    if (func_0206fe54()) {
        func_ov002_02209eb8(self + 0x11c);
    }
    func_ov002_0220ad18(self + 0x180, *(int *) (self + 0x94));
    func_ov130_0229a00c(*(int *) (self + 0x94));
    if (*(u8 *) (self + 0xa1) & 0x10) {
        func_02088df8(1, data_ov133_0229c868, (*(u8 *) (self + 0x9f) << 4) + 0x20, *(int *) (self + 0x94) + 0x40, -1, 1,
                      0x1000, 0x1000, 0, -1, 0, 0);
    }
    return 1;
}
