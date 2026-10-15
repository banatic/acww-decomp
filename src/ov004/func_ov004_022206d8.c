/* func_ov004_022206d8 @ 0x022206d8, 0x124 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x830];
    void *unk_830;
    char pad_834[0xac8 - 0x834];
    u8 unk_AC8;
    char pad_AC9[0xadc - 0xac9];
    u8 unk_ADC;
} UnkStruct_022206d8;

#define OBJ (*(UnkStruct_022206d8 **) (self + 0x1a4))

extern void *func_0208150c(void *);
extern int func_0200366c(void *a, void *b, int c, void *d);
extern int func_020644cc(int);
extern void func_0206844c(void *, u8 *, void *);
extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern void func_0207d540(void *, void *);
extern void func_ov004_02221550(void *self, int a);
extern void func_0208b514(unsigned);

extern char data_ov004_02257e68;
extern char data_ov004_02253edc;
extern char data_021f43e8;

void func_ov004_022206d8(char *self)
{
    u8 state;
    u8 mode;
    u8 buf;

    {
        UnkStruct_022206d8 *obj = OBJ;
        mode = obj->unk_AC8;
    }
    if (mode == 5 || mode == 3) {
        if (mode == 5) {
            OBJ->unk_AC8 = 6;
        } else {
            OBJ->unk_AC8 = 4;
        }
        func_0200366c(func_0208150c(OBJ->unk_830), &data_ov004_02257e68, 0x28, &data_ov004_02253edc);
        buf = (u8) func_020644cc(3);
        func_0206844c(*(void **) (self + 0x40), &buf, &data_ov004_02257e68);
        return;
    }

    state = *(u8 *) (self + 0x1e);

    switch (state) {
        case 0:
        case 1:
        case 2:
            if (mode == 6 || mode == 1) {
                func_0206844c(*(void **) (self + 0x40), (u8 *) &data_021f43e8, 0);
            } else if (mode == 0) {
                void *have;
                if (func_020984e8() != 0) {
                    have = func_02099870(func_020984e8());
                } else {
                    have = 0;
                }
                if (OBJ->unk_830 != 0 && have != 0) {
                    func_0207d540(OBJ->unk_830, have);
                }
                OBJ->unk_AC8 = 1;
                OBJ->unk_ADC = 0x28;
                func_0206844c(*(void **) (self + 0x40), (u8 *) &data_021f43e8, 0);
                func_ov004_02221550(OBJ, 1);
            }
            break;
        case 8:
        case 9:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            func_0208b514(mode);
            break;
        default:
            break;
    }
}
