/* func_02024288 @ 0x02024288, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_02024288 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02024288;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02024288_2 {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    UnkStruct_02024288 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02024288_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02024288_3;

extern Cfg data_020c8fb8[1];
extern Pair data_020d9270;

extern int func_0202d9c4(UnkStruct_02024288_2 *self);
extern int func_0209bd04(int x);
extern int func_0209bcc4(int x, int *idx);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(UnkStruct_02024288_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);

void func_02024288(UnkStruct_02024288_2 *self, UnkStruct_02024288_3 *out)
{
    int idx;
    Cfg *cfg;

    cfg = data_020c8fb8;
    if (func_0209bd04(func_0202d9c4(self)) == 0) {
        idx = 0;
        if (func_0209bcc4(func_0202d9c4(self), &idx) != 0) {
            cfg = &data_020c8fb8[idx];
        }
    }
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), cfg->unk_00,
                  cfg->unk_04, 0, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
    self->unk_C8 = data_020d9270;
}
