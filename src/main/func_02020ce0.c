/* func_02020ce0 @ 0x02020ce0, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02020ce0 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02020ce0;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02020ce0_2 {
    char pad_00[0x100];
    UnkStruct_02020ce0 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02020ce0_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02020ce0_3;

extern Cfg data_020c8a88;
extern int data_020ccf94;
extern int data_021e5a2c;

extern int func_020644cc(int x);
extern int func_02073d90(int x);
extern int func_0207f1c8(int x);
extern int func_0209b5ec(int x);
extern int func_0207f0c0(int x);
extern void func_0209c214(int x);
extern int func_0208150c(int x);
extern void func_0207c460(int *g, int x);
extern int func_020036e8(int x);
extern void func_0202da38(UnkStruct_02020ce0_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);

void func_02020ce0(UnkStruct_02020ce0_2 *self, UnkStruct_02020ce0_3 *out)
{
    // DECLS
    int mode;
    int h;
    // ENDDECLS

    if (func_020644cc(3) == 0 && func_02073d90(data_020ccf94) == 0) {
        int inner = self->unk_100->unk_830;
        h = func_0209b5ec(func_0207f1c8(inner));
        if (func_0207f0c0(inner) == 0) {
            func_0209c214(h);
            func_0207c460(&data_021e5a2c, func_0208150c(inner));
        }
        mode = 3;
    } else {
        mode = 2;
    }
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                  data_020c8a88.unk_00, data_020c8a88.unk_04, mode, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
}
