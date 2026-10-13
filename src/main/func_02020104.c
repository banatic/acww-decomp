/* func_02020104 @ 0x02020104, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02020104_2 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02020104 {
    char pad_00[0x100];
    struct UnkStruct_02020104_2 *inner;
    char buffer[30];
    unsigned char byte;
};

struct Global {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_02020104_3 {
    void *ptr;
    unsigned char byte;
};

extern struct Global data_020c8ce8;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(struct UnkStruct_02020104 *, char *, unsigned char *, int);

void func_02020104(struct UnkStruct_02020104 *p, struct UnkStruct_02020104_3 *out)
{
    volatile struct {
        int a;
        int b;
        int c;
        int d;
        int e;
    } local;

    local.a = func_020036e8(func_0208150c(p->inner->unk_830));
    local.b = data_020c8ce8.unk_00;
    local.c = data_020c8ce8.unk_04;
    local.d = 0;
    local.e = 0;

    func_0202da38(p, p->buffer, &p->byte, 30);
    out->ptr = p->buffer;
    out->byte = p->byte;
}
