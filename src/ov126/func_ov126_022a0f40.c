/* func_ov126_022a0f40 @ 0x022a0f40, 0xe0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a0f40 {
    unsigned char pad_00[0xa8];
    unsigned char unk_A8;
    unsigned char pad_A9[0x19c - 0xa8 - 1];
    unsigned char unk_19C[1];
    unsigned char pad_19D[0x3f90 - 0x19c - 1];
    unsigned char unk_3F90[1];
} UnkStruct_022a0f40;

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(UnkStruct_022a0f40 *self);
extern int func_ov126_022a0768(UnkStruct_022a0f40 *self, int val);
extern void func_ov095_0229b3ec(unsigned char *ptr);
extern void func_ov126_022a0728(UnkStruct_022a0f40 *self);
extern void func_ov126_022a08c4(UnkStruct_022a0f40 *self);
extern void func_ov126_022a0168(UnkStruct_022a0f40 *self);
extern void func_ov126_0229ff0c(UnkStruct_022a0f40 *self);
extern void RtcSendPxiCommand(int cmd);
extern int func_ov002_02209f00(unsigned char *ptr);
extern void func_ov095_0229a134(unsigned char *ptr, int val);
extern void func_ov126_022a0f20(UnkStruct_022a0f40 *self);
extern int func_ov126_0229fdd4(UnkStruct_022a0f40 *self);
extern int func_ov126_0229fcfc(UnkStruct_022a0f40 *self);
extern int func_ov126_0229fd64(UnkStruct_022a0f40 *self);
extern int func_ov126_0229fcd8(UnkStruct_022a0f40 *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov126_022a06b4(UnkStruct_022a0f40 *self);
extern unsigned char *func_ov126_022a0c1c(UnkStruct_022a0f40 *self);

extern struct {
    unsigned short pad;
    unsigned short flag;
} data_021fbe40;

void func_ov126_022a0f40(UnkStruct_022a0f40 *self)
{
    int stat;
    int val;
    unsigned char prev;

    if (func_ov002_02208014() != 0) {
        func_ov126_022a0c1c(self);
        return;
    }
    stat = func_ov126_022a0768(self, func_ov002_02208008(self));
    switch (stat) {
        case 1:
            func_ov095_0229b3ec(self->unk_19C);
            func_ov126_022a0728(self);
            func_ov126_022a08c4(self);
            func_ov126_022a0168(self);
            func_ov126_0229ff0c(self);
            RtcSendPxiCommand(0xb);
            break;
        case 2:
            val = func_ov002_02209f00(self->unk_3F90);
            func_ov095_0229a134(self->unk_19C, val);
            func_ov126_022a0f20(self);
            break;
        default:
            prev = self->unk_A8;
            if (func_ov126_0229fdd4(self) != 0) {
                if (prev != self->unk_A8) {
                    func_ov126_0229ff0c(self);
                }
                break;
            }
            if (func_ov126_0229fcfc(self) == 0 && func_ov126_0229fd64(self) == 0 && func_ov126_0229fcd8(self) == 0 &&
                (data_021fbe40.flag & 1) != 0) {
                func_ov002_02208098((void *) (self), 7);
                func_ov126_022a06b4(self);
            }
            break;
    }
}
