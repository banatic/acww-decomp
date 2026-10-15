/* func_ov003_0221bc78 @ 0x0221bc78, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bc78Ev
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

struct UnkStruct_0221bc78 {
    int pad_00[2];
    int unk_08;
};

extern "C" {
int func_0206fbc0(void);
int func_0206fc6c(void);
int func_020ae270(void);
void func_0206844c(void *, char *, char *);
void func_020b23ec(unsigned short, int);
extern char data_ov003_02238778;
}

void Obj_ov003_02238630::func_ov003_0221bc78()
{
    char buf[8];
    int ret;

    ret = func_0206fbc0();
    if (ret == 0) {
        return;
    }
    if (func_0206fc6c() != 0) {
        func_020ae270();
        buf[0] = 3;
        func_0206844c(unk_40, buf, &data_ov003_02238778);
        ((UnkStruct_0221bc78 *) unk_40)->unk_08 = 1;
        func_ov003_0221bfa8(3);
    } else {
        buf[1] = 4;
        func_0206844c(unk_40, buf + 1, &data_ov003_02238778);
        ((UnkStruct_0221bc78 *) unk_40)->unk_08 = 1;
        func_ov003_0221bfa8(3);
        func_020b23ec(unk_136, 0);
    }
}
