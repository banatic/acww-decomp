/* func_0202b354 @ 0x0202b354, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0202b354_2 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202b354_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_0202b354_3 {
    char pad_00[0x100];
    UnkStruct_0202b354_2 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[1];
    unsigned short unk_124;
    char pad_126[0x19c - 0x126];
    unsigned short unk_19C;
    unsigned char unk_19E;
} UnkStruct_0202b354_3;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short unk_06;
} UnkStruct_0202b354;

extern Cfg data_020c8a30;

extern int func_0207f1c8(int x);
extern int func_0209b5ec(void *);
extern int func_0209c330(int x);
extern void func_0202b52c(UnkStruct_0202b354 *t, int x);
extern void func_0207de14(unsigned short *p, int x);
extern void func_0202d694(unsigned short *p);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(UnkStruct_0202b354_3 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);

int func_0202b354(UnkStruct_0202b354_3 *self)
{
    // DECLS
    UnkStruct_0202b354 tmp;
    int inner;
    // ENDDECLS

    inner = self->unk_100->unk_830;
    func_0202b52c(&tmp, func_0209c330((func_0209b5ec((void *) func_0207f1c8(inner)))));
    self->unk_124 = tmp.unk_00;
    if (self->unk_124 == 0xfff1) {
        goto fail;
    }
    func_0207de14(&tmp.unk_02, inner);
    self->unk_19C = tmp.unk_02;
    if (self->unk_19C != 0xfff1) {
        self->unk_19E = 1;
    } else {
        func_0202d694(&tmp.unk_04);
        self->unk_19C = tmp.unk_04;
        self->unk_19E = 0;
    }
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(inner)), data_020c8a30.unk_00,
                  data_020c8a30.unk_04, 0, 0);
    return 1;
fail:
    return 0;
}
