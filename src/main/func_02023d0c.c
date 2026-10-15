/* func_02023d0c @ 0x02023d0c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02023d0c {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02023d0c;

typedef struct UnkStruct_02023d0c_2 {
    char pad_00[0x100];
    UnkStruct_02023d0c *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02023d0c_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02023d0c_3;

extern int data_020c8c20;

extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0200368c(char *a, int n, int g, int v);
extern int func_0202d9c4(UnkStruct_02023d0c_2 *self);
extern int func_0209bc40(int x);

void func_02023d0c(UnkStruct_02023d0c_2 *self, UnkStruct_02023d0c_3 *out)
{
    func_0200368c(self->unk_104, 0x1e, data_020c8c20, func_020036e8(func_0208150c(self->unk_100->unk_830)));
    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0xe:
            self->unk_122 = 0xb;
            break;
        case 0x10:
            self->unk_122 = 0xd;
            break;
        default:
            self->unk_122 = 0xe;
            break;
    }
    out->p = self->unk_104;
    out->b = self->unk_122;
}
