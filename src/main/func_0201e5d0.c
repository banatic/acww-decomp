/* func_0201e5d0 @ 0x0201e5d0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_0201e5d0_2;

typedef struct {
    char pad_00[0x830];
    int unk_830;
} Field100Type;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobalData;
extern GlobalData data_020c8b50;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201e5d0;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

void func_0201e5d0(UnkStruct_0201e5d0_2 *self, UnkStruct_0201e5d0 *out)
{
    int local0;
    local0 = func_020036e8(func_0208150c(((Field100Type *) self->unk_100)->unk_830));
    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, local0, data_020c8b50.unk_00, 1, 0x10, data_020c8b50.unk_04);
    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}
