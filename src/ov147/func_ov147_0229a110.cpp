/* func_ov147_0229a110 @ 0x0229a110, 0x84 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov147_0229aa2819func_ov147_0229a110Ev
 */

#include "cpp/ov147/Obj_ov147_0229aa28.h"

extern "C" void func_ov147_02299aac(unsigned char *, unsigned char *);
extern "C" int func_0203d4b8(void);
extern "C" void func_0203d28c(void *argument0);
extern "C" void func_0203e334(void);
extern "C" int func_0206e508(void);
extern "C" void func_ov147_0229a6ac(unsigned char *);
extern "C" int func_020a1768(void);
extern "C" int func_0203dedc(void);
extern "C" void func_ov147_0229a054(unsigned char *, int);
extern "C" void func_0203dec4(void);

int Obj_ov147_0229aa28::func_ov147_0229a110()
{
    unsigned char *p = (unsigned char *) this;
    func_ov147_02299aac(p + 0x54, p);

    func_0203d28c((void *) func_0203d4b8());
    func_0203e334();
    if (func_0206e508() == 3) {
        p[0xf4] = 1;
    }
    ((Obj_ov147_0229aa28 *) p)->func_ov147_02299fc8(0);
    p[0xaa] = 0;
    p[0xab] = 0;
    func_ov147_0229a6ac(p + 0xb0);
    if (func_020a1768() == 1) {
        p[0xa2] = 1;
    }
    func_ov147_0229a054(p, func_0203dedc() != 0);
    if (func_0203dedc() != 0) {
        p[0xaa] = 6;
        func_0203dec4();
    }
    return 1;
}
