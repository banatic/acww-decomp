/* func_0203c2d4 @ 0x0203c2d4, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u8 flag;
} UnkStruct_0203c2d4;

typedef struct {
    u8 pad_00[0x178];
    int unk_178;
    int unk_17C;
    int unk_180;
    int unk_184;
} UnkStruct_0203c2d4_2;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} CondStruct;

extern UnkStruct_0203c2d4 *data_021f6948;
extern int data_020ca0e8;
extern CondStruct *data_021c80bc;

extern void func_02030738(void *, void *, void *, void *);
extern int func_020b65c4(void);
extern int func_02037e84(u32);

void func_0203c2d4(UnkStruct_0203c2d4_2 *self)
{
    if (data_021f6948->flag == 0) {
        func_02030738(&self->unk_178, &self->unk_17C, &self->unk_180, &self->unk_184);
        if (self->unk_184 < data_020ca0e8) {
            self->unk_184 = data_020ca0e8;
        }
    }
    if (func_020b65c4() == 0x29) {
        self->unk_17C += 0x4000;
        self->unk_184 += 0x4000;
    } else {
        u32 arg;
        u32 zero = 0;
        if (data_021c80bc->unk_04 > zero && data_021c80bc->unk_08 > zero && data_021c80bc->unk_00 != 0) {
            arg = data_021c80bc->unk_00;
        } else {
            arg = 0;
        }
        switch (func_02037e84(arg)) {
            case 0x1009:
            case 0x100c:
                self->unk_178 += 0x2000;
                break;
            case 0x100a:
                self->unk_17C -= 0x2000;
                break;
            case 0x100b:
            case 0x100d:
                self->unk_178 += 0x2000;
                self->unk_17C -= 0x2000;
                break;
            default:
                break;
        }
    }
}