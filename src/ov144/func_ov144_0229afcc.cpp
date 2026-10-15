/* func_ov144_0229afcc @ 0x0229afcc, 0x60 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov144_0229b3f819func_ov144_0229afccEv
 */

#include "cpp/ov144/Obj_ov144_0229b3f8.h"

extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov144_0229a17c(void *obj);
extern "C" void func_ov144_0229a798(void *obj);
extern "C" unsigned char *func_ov002_022080a0(void *obj, unsigned char value);
extern "C" void func_ov144_0229add8(void *obj);
extern "C" void func_ov144_0229add0(void *obj);

int Obj_ov144_0229b3f8::func_ov144_0229afcc()
{
    void *obj = (void *) this;
    func_0206f58c();
    if (func_0206f56c() != 0) {
        unsigned char val = ((unsigned char *) obj)[0x8d];
        switch (val) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                func_ov144_0229a17c(obj);
                func_ov144_0229a798(obj);
                func_ov002_022080a0(obj, 1);
                break;
        }
    }
    func_ov144_0229add8(obj);
    ((Obj_ov144_0229b3f8 *) obj)->func_ov144_0229b02c();
    func_ov144_0229add0(obj);
    return 1;
}
