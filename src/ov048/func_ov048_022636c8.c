/* func_ov048_022636c8 @ 0x022636c8, 0x10c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern int func_02073d90(int);
extern int func_020b65c4(void);
extern int func_0201c0e0(void *);
extern void func_ov048_022635f4(void *, int);
extern void func_0208602c(void);
extern int func_020860cc(void);
extern int func_02087e84(int);
extern int func_02087e78(int);
extern int func_02087e8c(int);
extern void func_0203e334(void);
extern void func_ov048_02262678(void *, int);
extern int data_020ccf94;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[4];
    short unk_94;
    char pad_96[0x4e8 - 0x96];
    unsigned int unk_4E8;
    char pad_4EC[0x658 - 0x4ec];
    char unk_658;
    char pad_659[0xe6c - 0x659];
    short unk_E6C;
} UnkStruct_022636c8;

int func_ov048_022636c8(UnkStruct_022636c8 *self)
{
    if (func_0202ec58() == 0) {
        return 0;
    }
    self->unk_E6C = self->unk_8E;
    self->unk_4E8 |= 2;
    if (func_02073d90(data_020ccf94) != 0 && func_020b65c4() == 0xb) {
        if (func_0201c0e0(self) != 0) {
            func_ov048_022635f4(self, 1);
        } else {
            func_ov048_022635f4(self, 0xf);
        }
        return 1;
    } else {
        int r4;
        func_0208602c();
        r4 = func_020860cc();
        if (func_02087e84(r4) == 1 || func_02087e84(r4) == 2) {
            if (func_02087e84(r4) == 1) {
                func_ov048_02262678(&self->unk_658, 6);
            } else {
                func_ov048_02262678(&self->unk_658, 7);
            }
            func_ov048_022635f4(self, 0);
            self->unk_8E = (short) func_02087e78(r4);
            self->unk_94 = (short) func_02087e78(r4);
            func_02087e8c(r4);
        } else {
            if (func_020b65c4() == 0xd) {
                func_0203e334();
                func_ov048_022635f4(self, 9);
            } else if (func_020b65c4() == 0xe) {
                func_0203e334();
                func_ov048_022635f4(self, 0xb);
            } else {
                func_ov048_022635f4(self, 1);
            }
        }
        return 1;
    }
}
