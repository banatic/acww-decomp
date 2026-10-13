/* func_ov003_02229c04 @ 0x02229c04, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    char pad_4C[0x38];
    int unk_84;
    char pad_88[8];
    void *unk_90;
} UnkStruct_02229c04;

typedef struct {
    char pad_00[0xb0];
    int unk_B0;
} UnkStruct_02229c04_2;

int func_0204fea4(void);
void func_ov003_0222aaa0(void *p, void *q);
int func_ov003_02229b54(UnkStruct_02229c04 *self, void *a);
UnkStruct_02229c04_2 *func_020961a8(void *a);

int func_ov003_02229c04(UnkStruct_02229c04 *self, void *a)
{
    UnkStruct_02229c04_2 *o;
    int st, v, c1, c2;

    if (self->unk_44 != -1) {
        return 0;
    }
    self->unk_44 = func_0204fea4();
    st = self->unk_48;
    if (st != 5) {
        func_ov003_0222aaa0(&self->unk_84, self->unk_90);
    }
    st = self->unk_48;
    if (st == 1) {
        if (func_ov003_02229b54(self, a) == 0) {
            return 0;
        }
    } else if (st == 2) {
        if (func_ov003_02229b54(self, a) == 0) {
            return 0;
        }
        o = func_020961a8(a);
        if (o != 0) {
            v = o->unk_B0;
            c1 = (v & 4) ? 1 : 0;
            if (c1) {
                c2 = (v & 2) ? 1 : 0;
                if (c2) {
                    self->unk_40 = 2;
                    return 1;
                }
            }
        }
    }
    self->unk_40 = 3;
    return 1;
}
