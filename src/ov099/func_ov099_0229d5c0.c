/* func_ov099_0229d5c0 @ 0x0229d5c0, 0xd8 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov099_0229d14c(void *self);
extern int func_ov002_02207d24(int *p, int val);
extern int func_ov002_02208008(void *self);
extern int func_ov099_0229c2c4(void *self, int a);
extern void func_ov099_0229c9d0(void *self);
extern void func_ov099_0229c6dc(void *self);
extern int func_ov099_0229ccc8(void *self, unsigned char b);
extern int func_ov099_0229cf30(void *self, unsigned char b);
extern int func_ov099_0229cc74(void *self, unsigned char b);
extern void func_ov099_0229c3e0(void *self, unsigned char b);
extern unsigned char *func_ov002_022080a0(void *self, unsigned char value);
extern void func_ov099_0229c754(void *self);
extern void func_ov002_02207d00(int *p);

struct GFlags {
    unsigned char pad_00[2];
    unsigned short flags;
};
extern struct GFlags data_021fbe40;

struct UnkStruct_0229d5c0 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x218c - 0x8d];
    int unk_218C;
    unsigned char pad_2190[0x2907 - 0x2190];
    unsigned char unk_2907;
};

void func_ov099_0229d5c0(struct UnkStruct_0229d5c0 *self)
{
    if (func_ov002_02208014(self)) {
        func_ov099_0229d14c(self);
        func_ov002_02207d24(&self->unk_218C, 1);
        return;
    } else {
        int tmp = func_ov002_02208008(self);
        if (func_ov099_0229c2c4(self, tmp)) {
            func_ov099_0229c9d0(self);
            func_ov099_0229c6dc(self);
            func_ov002_02207d24(&self->unk_218C, 0);
            return;
        }
        if (func_ov099_0229ccc8(self, self->unk_2907)) {
            goto D;
        }
        if ((data_021fbe40.flags & 1) == 0) {
            goto D;
        }
        if (func_ov099_0229cf30(self, self->unk_2907) == 0) {
            return;
        }
        if (func_ov099_0229cc74(self, self->unk_2907) != 0) {
            return;
        }
        func_ov099_0229c3e0(self, self->unk_2907);
        return;
    }
D:
    if ((data_021fbe40.flags & 0x800) == 0) {
        goto E;
    }
    self->unk_8C = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24(&self->unk_218C, 1);
    func_ov099_0229c754(self);
    return;
E:
    func_ov002_02207d00(&self->unk_218C);
    return;
}
