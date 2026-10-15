/* func_ov106_0229e734 @ 0x0229e734, 0xac bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov106_0229f6e019func_ov106_0229e734Ev
 */

#include "cpp/ov106/Obj_ov106_0229f6e0.h"

extern "C" unsigned char data_021fbdd8;

typedef struct UnkStruct_0229e734 {
    unsigned char pad_00[0xb5];
    unsigned char unk_B5;
    unsigned char pad_B6[0xbf - 0xb5 - 1];
    unsigned char unk_BF;
    unsigned char pad_C0[0x21b8 - 0xbf - 1];
    unsigned char buffer[1];
} UnkStruct_0229e734;

extern "C" int func_ov106_0229c364(UnkStruct_0229e734 *p, int arg);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern "C" void func_ov002_02207ce4(unsigned char *ptr, int size);
extern "C" int func_ov106_0229cf8c(UnkStruct_0229e734 *p);
extern "C" void func_ov106_0229d5c4(UnkStruct_0229e734 *p, unsigned char byte);
extern "C" int func_ov002_02207cc0(int object);
extern "C" void func_ov106_0229c798(UnkStruct_0229e734 *p, unsigned char byte, int arg);
extern "C" void func_ov002_02207d00(unsigned char *ptr);

void Obj_ov106_0229f6e0::func_ov106_0229e734()
{
    UnkStruct_0229e734 *p = (UnkStruct_0229e734 *) this;
    if (data_021fbdd8 == 0) {
        if (func_ov106_0229c364(p, 4) != 0) {
            func_ov002_02208098((void *) (p), 3);
            ((Obj_ov106_0229f6e0 *) p)->func_ov106_0229ef8c();
        } else {
            func_ov002_02208098((void *) (p), 0);
            func_ov002_02207ce4(p->buffer, 0x3c);
        }
    } else {
        if (func_ov106_0229c364(p, 4) != 0) {
            if (func_ov106_0229cf8c(p) != 0) {
                func_ov106_0229d5c4(p, p->unk_B5);
            } else {
                if (func_ov002_02207cc0((int) (p->buffer)) != 0) {
                    if (p->unk_BF != 0) {
                        p->unk_BF--;
                    } else {
                        func_ov106_0229c798(p, p->unk_B5, 1);
                        func_ov002_02208098((void *) (p), 2);
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
