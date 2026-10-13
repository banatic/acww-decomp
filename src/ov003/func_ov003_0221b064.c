/* func_ov003_0221b064 @ 0x0221b064, 0x110 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec48 {
    int data[12];
} Vec48;

typedef struct UnkStruct_0221b064 {
    char pad_00[0x8];
    int unk_08;
    char pad_0C[0x5c - 0xc];
    char unk_5C[0x198 - 0x5c];
    Vec48 unk_198;
    char pad_1C8[0x234 - 0x1c8];
    Vec48 unk_234;
    char pad_264[0x26c - 0x264];
    int unk_26C;
    char pad_270[0x2f8 - 0x270];
    char sub[0x308 - 0x2f8];
    char unk_308[1];
} UnkStruct_0221b064;

extern short FX_SinCosTable_[];
extern int data_021fbdd0;

extern void func_020eabc8(int *vec, int val);
extern void func_0209a204(int *vec, void *a, void *b);
extern void func_0209a3c8(void *a);
extern void func_01ffd070(void *dst, void *a, void *b);
extern int func_0203f8d0(void *a, void *b);
extern void func_020e96c8(void *dst, int a, int b, int c);
extern void func_020e9774(void *dst, int val);
extern void func_0209a2ec(void *a, void *b);
extern void MTX_Concat43(void *a, void *b, void *c);

void func_ov003_0221b064(UnkStruct_0221b064 *self, int param1, int param2)
{
    int vec0[3];
    int vec1[4];
    int arr1c[3];
    int arr28[3];
    Vec48 vec34;
    char arr64[0x30];
    int ret1;
    int idx1;
    int idx2;
    int k1;
    int k2;
    int tmp;

    if (param1 != 0) {
        idx2 = ((unsigned short) param2) >> 4;
        k2 = idx2 << 1;
        vec0[0] = FX_SinCosTable_[k2 + 1];
        vec0[1] = 0;
        vec0[2] = -FX_SinCosTable_[k2];

        idx1 = ((unsigned short) (param1 >> 1)) >> 4;
        k1 = idx1 << 1;
        func_020eabc8(vec0, FX_SinCosTable_[k1]);

        vec1[0] = vec0[0];
        vec1[1] = vec0[1];
        vec1[2] = vec0[2];
        vec1[3] = FX_SinCosTable_[k1 + 1];

        func_0209a204(vec1, &self->sub, &self->sub);

        if ((data_021fbdd0 & 7) == self->unk_08) {
            func_0209a3c8(&self->sub);
        }
    }

    func_01ffd070(arr28, &self->unk_5C, &self->unk_308);

    tmp = arr28[1] + self->unk_26C;
    arr28[1] = tmp;
    arr28[1] = tmp - 0x400;

    ret1 = func_0203f8d0(arr1c, arr28);
    func_020e96c8((void *) &vec34, arr1c[0], arr1c[1], arr1c[2]);
    func_020e9774((void *) &vec34, ret1);

    func_0209a2ec(&self->sub, (void *) arr64);
    MTX_Concat43((void *) arr64, (void *) &vec34, (void *) &vec34);

    self->unk_198 = vec34;
    self->unk_234 = vec34;
}