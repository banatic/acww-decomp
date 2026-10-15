/* func_0201e56c @ 0x0201e56c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201e56c {
    unsigned char pad_00[0x100];
    unsigned char *unk_100;
    unsigned char buf[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0201e56c_2 {
    void *ptr;
    unsigned char unk_04;
};

extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int data_020c8b50;
extern int func_0202da38(struct UnkStruct_0201e56c *, unsigned char *, unsigned char *, int, int, int, int, int, int);

void func_0201e56c(struct UnkStruct_0201e56c *self, struct UnkStruct_0201e56c_2 *out)
{
    int v1;
    int v2;

    v1 = func_020036e8((unsigned char *) func_0208150c(*(int *) (self->unk_100 + 0x830)));
    v2 = data_020c8b50;
    func_0202da38(self, self->buf, &self->unk_122, 0x1e, v1, v2, 1, 0x12, 3);
    out->ptr = self->buf;
    out->unk_04 = self->unk_122;
}
