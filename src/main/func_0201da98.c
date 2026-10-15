/* func_0201da98 @ 0x0201da98, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(void *a0, void *a1, void *a2, int a3, int a4, int a5, int a6, int a7, int a8);

struct UnkStruct_0201da98 {
    char pad_00[0x830];
    int value;
};
struct DataC {
    int unk_00;
    unsigned char unk_04;
};
struct Pair {
    int a;
    int b;
};
struct UnkStruct_0201da98_2 {
    char pad_00[0xc8];
    int unk_C8;
    int unk_CC;
    char pad_D0[0x100 - 0xd0];
    struct UnkStruct_0201da98 *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x105];
    unsigned char unk_122;
    char pad_123[0x12c - 0x123];
    int unk_12C;
    char pad_130[0x13c - 0x130];
    unsigned char unk_13C;
};
struct UnkStruct_0201da98_3 {
    void *ptr;
    unsigned char byte;
};

extern struct DataC data_020c89f8;
extern struct Pair data_020d8e50;

void func_0201da98(struct UnkStruct_0201da98_2 *self, struct UnkStruct_0201da98_3 *out)
{
    int a, b, c, d, e;
    a = func_020036e8(func_0208150c(self->unk_100->value));
    b = data_020c89f8.unk_00;
    c = data_020c89f8.unk_04;
    d = 0;
    e = 0;
    func_0202da38(self, &self->unk_104, &self->unk_122, 30, a, b, c, d, e);
    out->ptr = &self->unk_104;
    out->byte = self->unk_122;
    if (self->unk_12C == 0) {
        self->unk_13C = 1;
    }
    *(struct Pair *) ((char *) self + 0xc8) = data_020d8e50;
}
