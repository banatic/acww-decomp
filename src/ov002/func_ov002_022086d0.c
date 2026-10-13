/* func_ov002_022086d0 @ 0x022086d0, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022086d0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

extern int func_ov002_022087f4(struct UnkStruct_022086d0 *self, int val);
extern void func_ov002_02208348(struct UnkStruct_022086d0 *self, int val);

void func_ov002_022086d0(struct UnkStruct_022086d0 *self, int mode)
{
    self->unk_0C = func_ov002_022087f4(self, self->unk_10);
    switch (mode) {
        case 0:
            func_ov002_02208348(self, 2);
            break;
        case 1:
            func_ov002_02208348(self, 0);
    }
}
