/* func_ov099_0229d004 @ 0x0229d004, 0x4c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d004;

extern void func_ov002_02207d24(char *ptr, int val);
extern void func_ov002_02208098(struct UnkStruct_0229d004 *self, int val);
extern void func_ov099_0229c880(struct UnkStruct_0229d004 *self, int val);
extern void func_ov099_0229c95c(struct UnkStruct_0229d004 *self);

struct UnkStruct_0229d004 {
    char pad_00[0x218c];
    char unk_218C;
    char pad_218D[0x776];
    unsigned char unk_2903;
    char pad_2904[2];
    char unk_2906;
};

void func_ov099_0229d004(struct UnkStruct_0229d004 *self, int val)
{
    unsigned char field;

    self->unk_2906 = (char) val;
    func_ov002_02207d24(&self->unk_218C, 1);
    func_ov099_0229c880(self, val);
    field = self->unk_2903;
    if (field == 1) {
    } else if (field == 2) {
        func_ov002_02208098(self, 3);
    }
    func_ov099_0229c95c(self);
}
