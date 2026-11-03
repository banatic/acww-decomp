/* friend_code_entry_scene_3: 3 functions, module ov133
 * mwccarm 1.2/base -O4,s
 * func_ov133_0229c6ec @ 0x0229c6ec, 0x20 bytes, Thumb
 * func_ov133_0229c6c0 @ 0x0229c6c0, 0x2a bytes, Thumb
 * func_ov133_0229c62c @ 0x0229c62c, 0x94 bytes, Thumb
 */

#include "types.h"

extern void func_ov133_0229c210(void *p);
extern void func_ov002_02208090(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void *func_020ee45c(void *self);
extern int func_ov090_0229936c(void *x);
extern void func_ov090_022990d0(void *x);
extern void func_ov133_0229c1dc(void *self);
extern int func_ov133_0229ad88(char *self, int v);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(char *p);
extern void func_ov002_0220ad18(char *p, int v);
extern void func_ov130_0229a00c(int v);
extern void func_02088df8(int a0, const void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10,
                          int a11);
extern const char data_ov133_0229c868[];

int func_ov133_0229c6ec(void *p)
{
    func_ov133_0229c210(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0(p, 1);
    return 1;
}

int func_ov133_0229c6c0(void *self)
{
    void *x = func_020ee45c(self);

    if (func_ov090_0229936c(x) == 6) {
        func_ov090_022990d0(x);
    }
    func_ov133_0229c1dc(self);
    return 1;
}

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
