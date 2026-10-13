/* func_02023ca8 @ 0x02023ca8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *);
extern int func_020036e8(int);
extern void func_0202da38(void *, char *, unsigned char *, int, int, int, int, int, int);

struct UnkStruct_02023ca8 {
    char pad_00[0x830];
    void *arg;
};

struct UnkStruct_02023ca8_2 {
    char pad_00[0x100];
    struct UnkStruct_02023ca8 *inner;
    char buffer[30];
    unsigned char unk_122;
};

struct GlobalCtx {
    int word;
    unsigned char byte;
};

struct UnkStruct_02023ca8_3 {
    void *ptr;
    unsigned char byte;
};

extern struct GlobalCtx data_020c8cd8;

void func_02023ca8(struct UnkStruct_02023ca8_2 *self, struct UnkStruct_02023ca8_3 *out)
{
    int a, b, c;

    a = func_020036e8(func_0208150c(self->inner->arg));
    b = data_020c8cd8.word;
    c = data_020c8cd8.byte;

    func_0202da38(self, self->buffer, &self->unk_122, 0x1e, a, b, c, 0, 0);

    out->ptr = self->buffer;
    out->byte = self->unk_122;
}
