/* func_ov125_0229f784 @ 0x0229f784, 0xe4 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x87c];
    unsigned char unk_87C;
} UnkStruct_0229f784;

extern void func_ov125_0229f74c(UnkStruct_0229f784 *self, int a);
extern int func_ov125_0229f8b8(UnkStruct_0229f784 *self, int a, int b);
extern int func_ov125_0229f8ec(UnkStruct_0229f784 *self, int a, int b);
extern int func_ov125_0229f76c(UnkStruct_0229f784 *self, int a);
extern int func_ov125_0229f890(UnkStruct_0229f784 *self, int a, int b, int c);
extern int func_ov125_0229f868(UnkStruct_0229f784 *self, int a, int b, int c);
extern int func_ov002_022088ac(int a);
extern int func_ov002_0220889c(int a);
extern int func_ov002_022088cc(int a);
extern int func_ov002_022088bc(int a);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a314(void *p);

int func_ov125_0229f784(UnkStruct_0229f784 *self, int param1)
{
    unsigned char original = self->unk_87C;
    func_ov125_0229f74c(self, 0xc);
    if (func_ov002_022088ac(param1)) {
        if (func_ov125_0229f8b8(self, 0, 3) == 0) {
            func_ov125_0229f8b8(self, 4, 7);
        }
    } else {
        if (func_ov002_0220889c(param1)) {
            if (func_ov125_0229f8ec(self, 0, 3) == 0) {
                func_ov125_0229f8ec(self, 4, 7);
            }
        }
    }
    if (func_ov125_0229f76c(self, 0xc) == 0) {
        if (func_ov002_022088cc(param1)) {
            if (func_ov125_0229f890(self, 4, 7, 0) == 0) {
                if (self->unk_87C == 8) {
                    self->unk_87C = 7;
                    func_ov002_0220a2b4((char *) self + 0x644);
                }
            }
        } else {
            if (func_ov002_022088bc(param1)) {
                if (func_ov125_0229f868(self, 0, 3, 4) == 0) {
                    if (self->unk_87C >= 4 && self->unk_87C <= 7) {
                        self->unk_87C = 8;
                        func_ov002_0220a314((char *) self + 0x644);
                    }
                }
            }
        }
    }
    return original != self->unk_87C;
}
