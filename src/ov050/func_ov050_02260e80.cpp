/* func_ov050_02260e80 @ 0x02260e80, 0xa8 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov050_02265b1419func_ov050_02260e80Ei
 */

#include "types.h"
#include "cpp/ov050/Obj_ov050_02265b14.h"

typedef void (Obj_ov050_02265b14::*Pmf)(int);

struct UnkStruct_02260e80 {
    int key;
    Pmf pmf;
};

extern "C" {
extern int func_020160b4(Obj_ov050_02265b14 *self);
extern int func_020ab504(int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov050_02265834;
}

void Obj_ov050_02265b14::func_ov050_02260e80(int arg)
{
    u8 b;
    int t;
    unsigned int i;
    u8 *kp;
    int key;

    t = func_020ab504(func_020160b4(this));
    unk_D0 = 0xff;
    {
        static UnkStruct_02260e80 tbl[] = {{0x22, &Obj_ov050_02265b14::func_ov050_02260e50}};
        i = 0;
        kp = &unk_1E;
        goto test;
    body:
        key = tbl[i].key;
        if (key == *kp) {
            (this->*(((UnkStruct_02260e80 *) ((char *) tbl + i * sizeof(UnkStruct_02260e80)))->pmf))(t);
        }
        i++;
    test:
        if (i < 1) {
            goto body;
        }
    }
    if (unk_D0 != 0xff) {
        b = (u8) unk_D0;
        func_0206844c(unk_40, &b, (int) &data_ov050_02265834);
    }
}
