/* func_ov003_0220ff40 @ 0x0220ff40, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0220ff40 {
    char pad_00[0x7d4];
    int vec2[3];
    char pad_7E0[0x800 - 0x7d4 - 0xc];
    int unk_800;
} UnkStruct_0220ff40;

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0200f290(UnkStruct_0220ff40 *, int);
extern void func_0200f268(UnkStruct_0220ff40 *, int);
extern int func_ov003_02220db4(int, int *);

void func_ov003_0220ff40(UnkStruct_0220ff40 *self, int param)
{
    int r;

    r = func_02073908(data_020ccf94, self->unk_800);
    if (r == 0) {
        if (param == 2) {
            func_0200f268(self, 0x1c);
            return;
        }
        if (param != 0x67) {
            if (func_0200f290(self, 0x1c) != 0) {
                int tmp[3];
                int *v = self->vec2;
                tmp[0] = v[0];
                tmp[1] = v[1];
                tmp[2] = v[2];
                func_ov003_02220db4(self->unk_800, tmp);
                func_0200f268(self, 0x1c);
            }
        } else {
            func_0200f268(self, 0x1c);
        }
        return;
    }
    func_0200f268(self, 0x1c);
}
