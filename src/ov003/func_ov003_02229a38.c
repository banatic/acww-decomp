/* func_ov003_02229a38 @ 0x02229a38, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    char pad_4C[8];
    Vec3 unk_54;
    char pad_60[0x1c];
    int unk_7C;
    char pad_80[4];
    int unk_84;
    char pad_88[8];
    void *unk_90;
    char pad_94[2];
    short unk_96;
    short unk_98;
    short unk_9A;
} UnkStruct_02229a38;

typedef struct {
    char pad_00[0x5c];
    Vec3 unk_5C;
} UnkStruct_02229a38_2;

void func_ov003_022299b8(UnkStruct_02229a38 *self);
void func_ov003_022298f0(UnkStruct_02229a38 *self);
void func_ov003_022294b4(UnkStruct_02229a38 *self, int k);
UnkStruct_02229a38_2 *func_020961a8(void *a);
void func_ov003_022293b0(UnkStruct_02229a38 *self, Vec3 *p);
void func_0204fdec(int a0, void *a1, Vec3 *a2, void *a3, int a4, int a5, int a6, int a7, int a8, int a9);

int func_ov003_02229a38(UnkStruct_02229a38 *self, void *a)
{
    int lim = 0x1e;
    int flag = 0;
    UnkStruct_02229a38_2 *o;

    switch (self->unk_48) {
        case 1:
            func_ov003_022299b8(self);
            flag = 1;
            break;
        case 2:
            func_ov003_022298f0(self);
            flag = 1;
            break;
        case 3:
            func_ov003_022294b4(self, 1);
            break;
        case 4:
            func_ov003_022294b4(self, flag);
            break;
        case 5:
            o = func_020961a8(a);
            if (o == 0) {
                self->unk_40 = 4;
                return flag;
            }
            func_ov003_022293b0(self, &o->unk_5C);
            lim -= self->unk_7C;
            if (lim < 1) {
                lim = 1;
            }
            break;
    }
    func_0204fdec(self->unk_44, self->unk_90, &self->unk_54, &self->unk_84, self->unk_96, self->unk_98, self->unk_9A, 1, flag,
                  lim);
    return 1;
}
