/* model_matrix: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070d4c @ 0x02070d4c, 0x28 bytes, Thumb
 * func_02070d24 @ 0x02070d24, 0x28 bytes, Thumb
 * func_02070cf4 @ 0x02070cf4, 0x30 bytes, Thumb
 * func_02070cc4 @ 0x02070cc4, 0x30 bytes, Thumb
 * func_02070ca4 @ 0x02070ca4, 0x20 bytes, Thumb
 * func_02070c50 @ 0x02070c50, 0x54 bytes, Thumb
 */

typedef struct {
    unsigned long long data[6];
} UnkStruct_02070d4c;

typedef struct {
    unsigned long long data[6];
} UnkStruct_02070d24;

typedef struct {
    unsigned int a, b, c;
} Src;

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24, unk_28, unk_2C;
} UnkStruct_02070cf4;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02070cc4;

extern UnkStruct_02070d4c data_021cfe98[];
extern void MTX_Copy33To43_(void *a, void *b);
extern void MTX_Concat43(void *a, void *b, void *c);
extern char data_021cfe68[];
extern void MTX_Identity43_(void *buf);
extern int FX_MulFunc(int a, int b);

void func_02070d4c(int index)
{
    data_021cfe98[index] = (*(UnkStruct_02070d4c *) data_021cfe68);
}

void func_02070d24(int idx)
{
    (*(UnkStruct_02070d24 *) data_021cfe68) = ((UnkStruct_02070d24 *) data_021cfe98)[idx];
}

void func_02070cf4(void *param0, Src *param1)
{
    UnkStruct_02070cf4 local;
    MTX_Copy33To43_(param0, &local);
    local.unk_24 = param1->a;
    local.unk_28 = param1->b;
    local.unk_2C = param1->c;
    MTX_Concat43(&local, data_021cfe68, data_021cfe68);
}

void func_02070cc4(UnkStruct_02070cc4 *src)
{
    unsigned int buf[12];
    MTX_Identity43_(buf);
    buf[9] = src->unk_00;
    buf[10] = src->unk_04;
    buf[11] = src->unk_08;
    MTX_Concat43(buf, ((unsigned int *) data_021cfe68), ((unsigned int *) data_021cfe68));
}

void func_02070ca4(void *arg)
{
    char buf[0x34];

    MTX_Copy33To43_(arg, buf);
    MTX_Concat43(buf, data_021cfe68, data_021cfe68);
}

void func_02070c50(int param0, int *a, int *b)
{
    int mtx[13];

    MTX_Copy33To43_((void *) param0, mtx);
    if (b == 0) {
        mtx[9] = a[0];
        mtx[10] = a[1];
        mtx[11] = a[2];
    } else {
        mtx[9] = FX_MulFunc(a[0], b[0]);
        mtx[10] = FX_MulFunc(a[1], b[1]);
        mtx[11] = FX_MulFunc(a[2], b[2]);
    }
    MTX_Concat43(mtx, ((int *) data_021cfe68), ((int *) data_021cfe68));
}
