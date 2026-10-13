/* func_ov108_0229d718 @ 0x0229d718, 0x94 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;

struct UnkStruct_0229d718 {
    unsigned char pad_00[0x2ad];
    unsigned char unk_2AD;
    unsigned char pad_2AE[8];
    unsigned char unk_2B6;
    unsigned char pad_2B7[0x20f9];
    char sub;
};

int func_ov108_0229c2dc(struct UnkStruct_0229d718 *, int);
void func_ov002_02208098(struct UnkStruct_0229d718 *, int);
void func_ov108_0229db9c(struct UnkStruct_0229d718 *);
void func_ov002_02207ce4(void *, int);
int AOSS_FD_SET(void *);
void func_ov002_02207d00(void *);
void func_ov108_0229c404(struct UnkStruct_0229d718 *, unsigned char, int);

void func_ov108_0229d718(struct UnkStruct_0229d718 *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov108_0229c2dc(self, 4) != 0) {
            func_ov002_02208098(self, 3);
            func_ov108_0229db9c(self);
        } else {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4(&self->sub, 0x3c);
        }
    } else {
        if (func_ov108_0229c2dc(self, 4) != 0 && AOSS_FD_SET(&self->sub) != 0) {
            if (self->unk_2B6 != 0) {
                self->unk_2B6--;
            } else {
                func_ov108_0229c404(self, self->unk_2AD, 1);
                func_ov002_02208098(self, 2);
            }
        } else {
            func_ov002_02207d00(&self->sub);
        }
    }
}
