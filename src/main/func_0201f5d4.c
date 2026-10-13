/* func_0201f5d4 @ 0x0201f5d4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SubA {
    char pad_00[0x830];
    void *unk_830;
} SubA;

typedef struct UnkStruct_0201f5d4 {
    char pad_00[0x100];
    SubA *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
} UnkStruct_0201f5d4;

typedef struct UnkStruct_0201f5d4_2 {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201f5d4_2;

typedef struct GlobalT {
    int unk_00;
    unsigned char unk_04;
} GlobalT;

extern GlobalT data_020c8bd8;

extern void func_0208150c(void *arg);
extern int func_020036e8(void);
extern void func_0202da38(void *self, void *dst, void *src, int size, int a5, int a6, int a7, int a8, int a9);

void func_0201f5d4(UnkStruct_0201f5d4 *self, UnkStruct_0201f5d4_2 *out)
{
    int v1, v2, v3, v4, v5;

    func_0208150c(self->unk_100->unk_830);
    v1 = func_020036e8();
    v2 = data_020c8bd8.unk_00;
    v3 = 1;
    v4 = 10;
    v5 = data_020c8bd8.unk_04;

    func_0202da38(self, &self->unk_104, &self->unk_122, 30, v1, v2, v3, v4, v5);

    out->ptr = &self->unk_104;
    out->byte = self->unk_122;
}
