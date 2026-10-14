/* func_ov104_0229e7b8 @ 0x0229e7b8, 0xac bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov104_0229f6d019func_ov104_0229e7b8Ev
 */

#include "cpp/ov104/Obj_ov104_0229f6d0.h"

extern "C" unsigned char data_021fbdd8;

typedef struct UnkStruct_0229e7b8 {
    unsigned char pad_00[0xb5];
    unsigned char unk_B5;
    unsigned char pad_B6[0xbf - 0xb5 - 1];
    unsigned char unk_BF;
    unsigned char pad_C0[0x23b8 - 0xbf - 1];
    unsigned char buffer[1];
} UnkStruct_0229e7b8;

extern "C" int func_ov104_0229c364(UnkStruct_0229e7b8 *p, int arg);
extern "C" void func_ov002_02208098(UnkStruct_0229e7b8 *p, int arg);
extern "C" void func_ov002_02207ce4(unsigned char *ptr, int size);
extern "C" int func_ov104_0229d6a4(UnkStruct_0229e7b8 *p);
extern "C" void func_ov104_0229dc20(UnkStruct_0229e7b8 *p, unsigned char byte);
extern "C" int AOSS_FD_SET(unsigned char *ptr);
extern "C" void func_ov104_0229cf14(UnkStruct_0229e7b8 *p, unsigned char byte, int arg);
extern "C" void func_ov002_02207d00(unsigned char *ptr);

void Obj_ov104_0229f6d0::func_ov104_0229e7b8()
{
    UnkStruct_0229e7b8 *p = (UnkStruct_0229e7b8 *) this;
    if (data_021fbdd8 == 0) {
        if (func_ov104_0229c364(p, 4) != 0) {
            func_ov002_02208098(p, 3);
            ((Obj_ov104_0229f6d0 *) p)->func_ov104_0229f05c();
        } else {
            func_ov002_02208098(p, 0);
            func_ov002_02207ce4(p->buffer, 0x3c);
        }
    } else {
        if (func_ov104_0229c364(p, 4) != 0) {
            if (func_ov104_0229d6a4(p) != 0) {
                func_ov104_0229dc20(p, p->unk_B5);
            } else {
                if (AOSS_FD_SET(p->buffer) != 0) {
                    if (p->unk_BF != 0) {
                        p->unk_BF--;
                    } else {
                        func_ov104_0229cf14(p, p->unk_B5, 1);
                        func_ov002_02208098(p, 2);
                    }
                } else {
                    goto common;
                }
            }
        } else {
            goto common;
        }
        goto done;
    common:
        func_ov002_02207d00(p->buffer);
    done:;
    }
}
