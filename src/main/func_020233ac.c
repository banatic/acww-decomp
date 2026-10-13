/* func_020233ac @ 0x020233ac, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_020233ac {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_020233ac;

typedef struct UnkStruct_020233ac_2 {
    char pad_00[0x100];
    UnkStruct_020233ac *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x15a - 0x123];
    unsigned short unk_15A;
} UnkStruct_020233ac_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_020233ac_3;

extern Cfg data_020c8e30;
extern Pair data_020d8e90;

extern void func_0206f80c(Pair *v);
extern void func_02029264(UnkStruct_020233ac_2 *self, Pair *v);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern void func_0202da38(UnkStruct_020233ac_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);
extern void func_0202db48(UnkStruct_020233ac_2 *self, Pair p);

void func_020233ac(UnkStruct_020233ac_2 *self, UnkStruct_020233ac_3 *out)
{
    Pair v;

    v.a = 0;
    v.b = 0;
    func_0206f80c(&v);
    func_02029264(self, &v);
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                  data_020c8e30.unk_00, data_020c8e30.unk_04, 0, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
    self->unk_15A = 0x5e;
    func_0202db48(self, data_020d8e90);
}
