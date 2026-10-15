/* func_020231fc @ 0x020231fc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020231fc_2 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_020231fc {
    char pad_00[0x100];
    struct UnkStruct_020231fc_2 *inner;
    char buffer[30];
    unsigned char byte;
};

struct Global {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020231fc_3 {
    void *ptr;
    unsigned char byte;
};

extern struct Global data_020c8a28;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(struct UnkStruct_020231fc *, char *, unsigned char *, int, int base, int offset, int scale,
                         int multiplier, int selected);

void func_020231fc(struct UnkStruct_020231fc *p, struct UnkStruct_020231fc_3 *out)
{
    struct {
        int a;
        int b;
        int c;
        int d;
        int e;
    } local;

    local.a = func_020036e8(func_0208150c(p->inner->unk_830));
    local.b = data_020c8a28.unk_00;
    local.c = data_020c8a28.unk_04;
    local.d = 0;
    local.e = 0;

    func_0202da38(p, p->buffer, &p->byte, 30, local.a, local.b, local.c, local.d, local.e);
    out->ptr = p->buffer;
    out->byte = p->byte;
}
