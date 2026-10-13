/* func_02025d2c @ 0x02025d2c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02025d2c {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02025d2c;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02025d2c_2 {
    char pad_00[0x100];
    UnkStruct_02025d2c *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x164 - 0x123];
    int unk_164;
} UnkStruct_02025d2c_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02025d2c_3;

extern Cfg data_020d9308;
extern int *data_020d9d10[5];

extern int func_0209b914(int x);
extern int func_0202d9c4(UnkStruct_02025d2c_2 *self);
extern int func_0209bc40(int x);
extern int func_0209bcc4(int x, int *idx);
extern int func_0209b8d0(int x);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern void func_0202da38(UnkStruct_02025d2c_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);

void func_02025d2c(UnkStruct_02025d2c_2 *self, UnkStruct_02025d2c_3 *out)
{
    // DECLS
    Cfg cfg;
    int idx;
    int a;
    int b;
    // ENDDECLS

    cfg = data_020d9308;
    a = func_0209b914(self->unk_164);
    b = func_0209bc40(func_0202d9c4(self));
    idx = 0;
    func_0209bcc4(func_0202d9c4(self), &idx);
    if (a < func_0209b8d0(b)) {
        if (idx < 5) {
            cfg.unk_00 = data_020d9d10[idx][a];
        }
    }
    if (cfg.unk_00 != 0) {
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                      cfg.unk_00, cfg.unk_04, 0, 0);
    }
    out->p = self->unk_104;
    out->b = self->unk_122;
}
