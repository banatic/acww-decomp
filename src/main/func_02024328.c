/* func_02024328 @ 0x02024328, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_02024328 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02024328;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02024328_2 {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    UnkStruct_02024328 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02024328_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02024328_3;

extern Cfg data_020d9208;
extern Pair data_020d8e30;
extern int data_020c8e74;
extern int data_020c8e80;
extern int data_020c8e8c;

extern int func_0202d9c4(UnkStruct_02024328_2 *self);
extern int func_0209bc40(int x);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(UnkStruct_02024328_2 *self, char *a, unsigned char *b, int n, int e, void *f, int g, int h, int i);

void func_02024328(UnkStruct_02024328_2 *self, UnkStruct_02024328_3 *out)
{
    Cfg cfg;

    cfg = data_020d9208;
    switch (func_0209bc40(func_0202d9c4(self))) {
        case 2:
            cfg.unk_00 = &data_020c8e74;
            break;
        case 3:
            cfg.unk_00 = &data_020c8e80;
            break;
        default:
            cfg.unk_00 = &data_020c8e8c;
            break;
    }
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), cfg.unk_00,
                  cfg.unk_04, 0, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
    self->unk_C8 = data_020d8e30;
}
