/* func_0201fd78 @ 0x0201fd78, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);

struct UnkStruct_0201fd78 {
    char pad_00[0x830];
    int value;
};

struct In {
    char pad_00[0x100];
    struct UnkStruct_0201fd78 *ptr;
    char buffer[0x1e];
    unsigned char flag;
};

struct UnkStruct_0201fd78_2 {
    char *buf;
    unsigned char flag;
};

extern int func_0202da38(struct In *self, char *buf, unsigned char *flag, int size, int v0, int v1, int v2, int v3, int v4);

extern struct {
    int word;
    unsigned char byte;
} data_020c8ce8;

void func_0201fd78(struct In *self, struct UnkStruct_0201fd78_2 *out)
{
    int v0, v1, v2, v3, v4;

    v0 = func_020036e8(func_0208150c(self->ptr->value));
    v1 = data_020c8ce8.word;
    v2 = 1;
    v3 = 14;
    v4 = data_020c8ce8.byte;

    func_0202da38(self, self->buffer, &self->flag, 30, v0, v1, v2, v3, v4);

    out->buf = self->buffer;
    out->flag = self->flag;
}
