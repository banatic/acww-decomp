/* func_ov096_022a0da8 @ 0x022a0da8, 0xa0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022a0da8 UnkStruct_022a0da8;
struct UnkStruct_022a0da8 {
    u8 unk_00[0xa4];
    char *unk_A4;
    char *unk_A8;
    u8 p1[8];
    u8 unk_B4;
};
extern int func_0206f56c(void);
extern void func_ov096_0229e898(UnkStruct_022a0da8 *, int, int);
extern int func_ov096_022a18dc(UnkStruct_022a0da8 *, int);
extern void func_ov096_0229ea88(UnkStruct_022a0da8 *);
extern void func_ov096_0229ed44(UnkStruct_022a0da8 *);
extern int func_ov096_0229f4f8(UnkStruct_022a0da8 *, char *, char *, int);
extern int func_ov096_0229f4ac(UnkStruct_022a0da8 *, int);
extern unsigned char *func_ov096_0229f90c(UnkStruct_022a0da8 *, int, int);
extern void func_ov094_022999d8(void);
extern void func_ov096_0229fb9c(UnkStruct_022a0da8 *);
extern void func_ov096_0229ec90(UnkStruct_022a0da8 *, unsigned int argument1);
extern u8 data_021fbdd8;

void func_ov096_022a0da8(UnkStruct_022a0da8 *self)
{
    int r;
    if (func_0206f56c() != 0) {
        func_ov096_0229e898(self, self->unk_B4, 1);
        func_ov096_022a18dc(self, 7);
    } else {
        func_ov096_0229ea88(self);
        func_ov096_0229ed44(self);
        r = func_ov096_0229f4f8(self, self->unk_A4 + 8, self->unk_A8 + 8, 0);
        if (r != 0x26) {
            if (data_021fbdd8 == 0) {
                if (func_ov096_0229f4ac(self, r) == 0) {
                    func_ov096_0229f90c(self, self->unk_B4, 4);
                }
                func_ov094_022999d8();
                func_ov096_0229fb9c(self);
            } else {
                func_ov096_0229ec90(self, r);
            }
        } else {
            if (data_021fbdd8 == 0) {
                func_ov096_0229f90c(self, self->unk_B4, 4);
            }
        }
    }
}
