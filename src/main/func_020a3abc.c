/* func_020a3abc @ 0x020a3abc, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct PtrData {
    u8 pad_00[0x6c];
    u8 unk_6C;
} PtrData;

typedef struct UnkStruct_020a3abc {
    u8 pad_00[0xa1];
    u8 state;
    u8 pad_A2[0xd6 - 0xa2];
    u8 flag_d6;
    u8 pad_D7[0xd8 - 0xd7];
    u8 buf_d8[1];
    u8 pad_D9[0xe4 - 0xd9];
    u8 flag_e4;
} UnkStruct_020a3abc;

extern PtrData *data_020ccf94;
extern u8 data_021f3c1c;

extern int func_02073fdc(int);
extern void func_02074078(void);
extern int func_02073d70(PtrData *);
extern int func_020a7394(int, int, int, int, int);
extern int func_020738f4(PtrData *, u8);
extern int func_02073de0(PtrData *, u8, int);
extern int func_02075104(u8);
extern int func_02075dcc(void *, u16);
extern int func_02073044(void);
extern int func_020ebf70(int);
extern int func_02073d74(PtrData *, int);

void func_020a3abc(UnkStruct_020a3abc *self)
{
    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_02073d70(data_020ccf94) == 1) {
                PtrData *p;
                func_020a7394(data_021f3c1c, 0xc, 1, 0, 7);
                p = data_020ccf94;
                func_020738f4(p, (u8) (p->unk_6C + 1));
                func_02073de0(p, data_021f3c1c, 1);
                func_02075104(data_021f3c1c);
                self->state = 1;
            }
            break;
        case 1:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_02075dcc(self->buf_d8, (u16) (1 << data_021f3c1c))) {
                self->state = 2;
            }
            break;
        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_020ebf70(func_02073044()) && self->flag_e4) {
                func_02073d74(data_020ccf94, 2);
                self->flag_d6 = 1;
                self->state = 3;
            }
            break;
    }
}
