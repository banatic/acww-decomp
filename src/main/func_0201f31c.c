/* func_0201f31c @ 0x0201f31c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x830];
    int unk_830;
} PtrStruct;

typedef struct {
    char pad_00[0x100];
    PtrStruct *p;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_0201f31c;

typedef struct {
    void *ptr;
    unsigned char flag;
} UnkStruct_0201f31c_2;

extern struct {
    int field0;
    unsigned char field4;
} data_020c8ba0;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_0201f31c *, char *, unsigned char *, int, int, int, int, int, int);

void func_0201f31c(UnkStruct_0201f31c *self, UnkStruct_0201f31c_2 *out)
{
    int val = func_020036e8(func_0208150c(self->p->unk_830));
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, val, data_020c8ba0.field0, 1, 10, data_020c8ba0.field4);
    out->ptr = self->unk_104;
    out->flag = self->unk_122;
}
