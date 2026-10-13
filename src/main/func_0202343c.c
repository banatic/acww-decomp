/* func_0202343c @ 0x0202343c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

struct UnkStruct_0202343c {
    unsigned char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0202343c_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_0202343c *inner;
    char emb[30];
    unsigned char flag;
};

struct Output {
    void *ptr;
    unsigned char flag;
};

struct GlobalData {
    int word;
    unsigned char byte;
};

extern struct GlobalData data_020c8bb0;

void func_0202343c(struct UnkStruct_0202343c_2 *self, struct Output *out)
{
    int x;
    x = func_020036e8(func_0208150c(self->inner->unk_830));
    func_0202da38(self, &self->emb, &self->flag, 30, x, data_020c8bb0.word, data_020c8bb0.byte, 0, 0);
    out->ptr = &self->emb;
    out->flag = self->flag;
}
