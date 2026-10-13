/* func_ov078_0227949c @ 0x0227949c, 0x90 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e92e8(void *);
extern int FX_MulFunc(int, int, int);
extern int func_0204f7e0(int *, int *);
extern int func_02078e98(int *, int);
extern short FX_SinCosTable_[];
extern int data_021cb5a0;

struct UnkStruct_0227949c {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

int func_ov078_0227949c(struct UnkStruct_0227949c *self, int *out1, int *out2)
{
    int r4;
    int r6;
    int r7;
    int local[3];
    int t1, t2;
    r6 = 0;
    local[0] = r6;
    local[1] = r6;
    local[2] = r6;
    r4 = r6;
    while (r4 < 6) {
        r7 = ((unsigned short) (short) func_020e92e8(&data_021cb5a0) >> 4) << 1;
        t1 = FX_MulFunc(0xc000, FX_SinCosTable_[r7], r7 * 2);
        local[0] = t1 + self->unk_5C;
        t2 = FX_MulFunc(0xc000, FX_SinCosTable_[r7 + 1], (r7 + 1) * 2);
        local[2] = t2 + self->unk_64;
        func_0204f7e0(local, local);
        if (func_02078e98(local, r6) != 0) {
            *out1 = local[0];
            *out2 = local[2];
            r6 = 1;
            break;
        }
        r4++;
    }
    return r6;
}
