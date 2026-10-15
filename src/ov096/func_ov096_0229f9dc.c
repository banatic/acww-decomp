/* func_ov096_0229f9dc @ 0x0229f9dc, 0x68 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f9dc {
    unsigned char pad_00[0xB1];
    unsigned char mode;
    unsigned char pad_B2[2];
    unsigned char unk_B4;
    unsigned char pad_B5[4];
    unsigned char unk_B9;
    char pad_BA[0x2418 - 0xBA];
    char unk_2418[1];
};

extern int func_ov002_02207d24(void *p, int n);
extern void func_ov096_0229e90c(struct UnkStruct_0229f9dc *self, int param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229ea88(struct UnkStruct_0229f9dc *self);
extern void func_ov096_0229c2dc(struct UnkStruct_0229f9dc *self, unsigned int size);
extern void func_ov094_022999c0(void);

void func_ov096_0229f9dc(struct UnkStruct_0229f9dc *self, int param)
{
    unsigned char mode;

    self->unk_B4 = param;
    func_ov002_02207d24((char *) self + 0x2418, 1);
    func_ov096_0229e90c(self, param);

    mode = self->mode;
    switch (mode) {
        case 1:
            func_ov002_02208098((void *) (self), 6);
            break;
        case 2:
            func_ov002_02208098((void *) (self), 5);
            break;
        default:
            break;
    }

    func_ov096_0229ea88(self);
    ((void) (func_ov096_0229c2dc(self, 0x4000)), func_ov094_022999c0());

    self->unk_B9 = 0x26;
}
