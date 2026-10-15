/* func_ov068_02272338 @ 0x02272338, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272338Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

typedef struct {
    unsigned char pad_00[0x2db];
    unsigned char byte_at_2db;
} UnkStruct_02272338;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
} RetStruct;

extern "C" int func_ov003_02220174(int);
extern "C" int func_ov009_022630a0(void *obj);
extern "C" RetStruct *func_020961a8(int);
extern "C" int func_02095ab0(const unsigned int *, int, int);

void Obj_ov068_02277750::func_ov068_02272338()
{
    UnkStruct_02272338 *self = (UnkStruct_02272338 *) this;
    unsigned int arr[3];
    RetStruct *p;
    unsigned int *fp;

    int object = func_ov003_02220174(0x5000);
    if (object == 0) {
        return;
    }
    if (func_ov009_022630a0((void *) object) == 0) {
        return;
    }

    p = func_020961a8(4);
    if (p != 0) {
        if (self->byte_at_2db == 0) {
            fp = &p->unk_5C;
            arr[0] = *fp;
            arr[1] = fp[1];
            arr[2] = fp[2];
            arr[2] += 0x4000;
            if (func_02095ab0(arr, 0x400, 4) != 0) {
                ((Obj_ov068_02277750 *) self)->func_ov068_02272a7c(0xc);
            }
        }
    }

    if (self->byte_at_2db != 0) {
        self->byte_at_2db--;
    }
}
