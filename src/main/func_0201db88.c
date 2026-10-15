/* func_0201db88 @ 0x0201db88, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201db88 {
    char pad_00[0x830];
    int value;
};

struct UnkStruct_0201db88_2 {
    char pad_00[0x100];
    struct UnkStruct_0201db88 *inner;
    char buf[0x1e];
    unsigned char flag;
};

struct UnkStruct_0201db88_3 {
    char *ptr;
    unsigned char byte;
};

struct Global {
    int word;
    unsigned char byte;
};

extern struct Global data_020c8d18;
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(struct UnkStruct_0201db88_2 *, char *, unsigned char *, int, int, int, int, int, int selected);

void func_0201db88(struct UnkStruct_0201db88_2 *self, struct UnkStruct_0201db88_3 *out)
{
    func_0202da38(self, self->buf, &self->flag, 0x1e, func_020036e8((unsigned char *) func_0208150c(self->inner->value)),
                  data_020c8d18.word, 1, 3, data_020c8d18.byte);
    out->ptr = self->buf;
    out->byte = self->flag;
}
