/* func_ov108_0229d4b4 @ 0x0229d4b4, 0xd4 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct GlobalHW {
    unsigned short unk_00;
    unsigned short unk_02;
};

struct UnkStruct_0229d4b4 {
    unsigned char pad_00[0x2b0];
    unsigned char flag;
    unsigned char pad_2B1[0x20ff];
    unsigned char obj[1];
};

extern volatile struct GlobalHW data_021fbe40;
extern int func_ov002_02208014(struct UnkStruct_0229d4b4 *self);
extern int func_ov002_02208008(struct UnkStruct_0229d4b4 *self);
extern void func_ov002_02207d24(void *obj, int val);
extern void func_ov002_02207d00(void *obj);
extern int func_ov108_0229cfa8(struct UnkStruct_0229d4b4 *self);
extern int func_ov108_0229c2f0(struct UnkStruct_0229d4b4 *self, int val, int zero);
extern int func_ov108_0229c9d8(struct UnkStruct_0229d4b4 *self);
extern int func_ov108_0229c72c(struct UnkStruct_0229d4b4 *self);
extern int func_ov108_0229cb88(struct UnkStruct_0229d4b4 *self, unsigned char flag);
extern int func_ov108_0229cd70(struct UnkStruct_0229d4b4 *self, unsigned char flag);
extern int func_ov108_0229cb54(struct UnkStruct_0229d4b4 *self, unsigned char flag);
extern int func_ov108_0229c404(struct UnkStruct_0229d4b4 *self, unsigned char flag, int zero);
extern int func_ov108_0229c5b4(struct UnkStruct_0229d4b4 *self);
extern int func_ov108_0229c794(struct UnkStruct_0229d4b4 *self);
extern int func_ov108_0229cd90(struct UnkStruct_0229d4b4 *self);

void func_ov108_0229d4b4(struct UnkStruct_0229d4b4 *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov108_0229cfa8(self);
        func_ov002_02207d24(self->obj, 1);
        return;
    } else {
        int val = func_ov002_02208008(self);
        if (func_ov108_0229c2f0(self, val, 0) != 0) {
            func_ov108_0229c9d8(self);
            func_ov108_0229c72c(self);
            func_ov002_02207d24(self->obj, 0);
            return;
        } else {
            if (func_ov108_0229cb88(self, self->flag) == 0 && (data_021fbe40.unk_02 & 1) != 0) {
                if (func_ov108_0229cd70(self, self->flag) != 0) {
                    if (func_ov108_0229cb54(self, self->flag) != 0) {
                        return;
                    } else {
                        func_ov108_0229c404(self, self->flag, 0);
                        return;
                    }
                } else {
                    func_ov108_0229c5b4(self);
                    return;
                }
            } else {
                if ((data_021fbe40.unk_02 & 2) != 0) {
                    func_ov108_0229c794(self);
                    func_ov108_0229cd90(self);
                    func_ov002_02207d24(self->obj, 0);
                    return;
                } else {
                    func_ov002_02207d00(self->obj);
                    return;
                }
            }
        }
    }
}
