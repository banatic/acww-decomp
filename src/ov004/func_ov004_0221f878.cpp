/* func_ov004_0221f878 @ 0x0221f878, 0x118 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0221f878_2 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

typedef struct {
    int a, b, c;
} UnkStruct_0221f878;

extern "C" {

extern void *func_02095794(int);
extern void func_0201b458(void *dst, void *self, void *src);
extern int func_0201c378(void *self, int a);
extern void *data_021c80bc;
extern void func_0204ed30(void *a, void *b);
extern int func_02019e00(void *p);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, u16 i, int j);
extern void func_0201b044(void *a, void *b);
extern int func_020eaa6c(void *a, void *b);
extern int func_020e8858(void *a);
extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *a, int b);
extern void func_ov004_0221fdf4(void *self, int a);
extern u16 data_020c80f8;

int func_ov004_0221f878(char *self)
{
    UnkStruct_0221f878 t;
    UnkStruct_0221f878 obj28;
    int cnt;
    void *src;

    src = func_02095794(4);
    t.a = *(int *) src;
    t.b = *((int *) src + 1);
    t.c = *((int *) src + 2);
    func_0201b458(&obj28, self, &t);

    cnt = func_0201c378(self, 4);
    func_0204ed30(data_021c80bc, self + 0x5c);

    if (cnt > 0x4000) {
        if (func_02019e00(self + 0x564) == 1) {
            func_02019d0c(self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00(self + 0x564) == 2) {
            func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044(self + 0x350, &obj28);

    if (cnt <= 0x3000 || func_020eaa6c(&obj28, self + 0x5c) != 0 || func_020e8858(self + 0xa55) == 0) {
        ((UnkStruct_0221f878_2 *) (self + 0x8a8))->v2();
        func_02016108(self + 0x8a8, func_0201c2a4(self, 4));
        func_ov004_0221fdf4(self, 1);
    }
    return 1;
}
}
