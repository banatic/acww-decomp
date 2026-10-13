/* func_02094e2c @ 0x02094e2c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short FX_SinCosTable_[];
extern void func_02090db0(void *p);

typedef struct {
    int unk_00;
    int v1;
    int v2;
    short angle;
} In;

typedef struct {
    int *arr;
} UnkStruct_02094e2c;

typedef struct {
    char pad_00[0x18];
    UnkStruct_02094e2c *inner;
    char pad_1C[0x04];
    int pos[3];
    char pad_2C[0x10];
    short s1;
    short s2;
    short s3;
} UnkStruct_02094e2c_2;

void func_02094e2c(UnkStruct_02094e2c_2 *out, In *in)
{
    short t;
    unsigned short x;
    t = (short) (in->angle + 0x8000);
    out->pos[0] = in->unk_00 + out->inner->arr[1];
    out->pos[1] = in->v1 + out->inner->arr[2];
    out->pos[2] = in->v2 + out->inner->arr[3];
    x = (unsigned short) t;
    out->s1 = FX_SinCosTable_[(x >> 4) * 2];
    out->s2 = 0;
    out->s3 = FX_SinCosTable_[(x >> 4) * 2 + 1];
    func_02090db0(out);
}
