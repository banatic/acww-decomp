/* func_ov096_0229f970 @ 0x0229f970, 0x6c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char b1;
    unsigned char pad_B2[2];
    unsigned char b4;
    unsigned char pad_B5[5];
    unsigned char ba;
    unsigned char bb;
    unsigned char pad_BC[0x2418 - 0xbc];
    unsigned char unk_2418;
} UnkStruct_0229f970;

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov096_0229e8e0(UnkStruct_0229f970 *self, int val);
extern void func_ov096_0229e90c(UnkStruct_0229f970 *self, int val);
extern int func_ov096_0229ea5c(UnkStruct_0229f970 *self);
extern void func_ov094_022999c0(int arg);

void func_ov096_0229f970(UnkStruct_0229f970 *self, int val)
{
    self->b4 = val;
    func_ov002_02207d24(&self->unk_2418, 1);
    if (self->bb == 0) {
        func_ov096_0229e8e0(self, val);
    } else {
        func_ov096_0229e90c(self, val);
    }
    switch (self->b1) {
        case 1:
            self->ba = 0xc;
            break;
        case 2:
            self->ba = 0xb;
            break;
    }
    func_ov094_022999c0(func_ov096_0229ea5c(self));
}
